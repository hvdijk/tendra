/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


#include "config.h"
#include "object.h"
#include "hash.h"
#include "name.h"
#include "type.h"
#include "utility.h"


/*
    IS A FILE NEEDED IN THE MAKEFILE?

    This routine tests whether a file with information i is needed in the
    makefile for the given api.
*/

static boolean need_info
    PROTO_N ( ( i, api ) )
    PROTO_T ( info *i X char *api )
{
    if ( restrict_depth && !streq ( api, i->api ) ) return ( 0 ) ;
    return ( i->implemented && i->tokens && i->src ) ;
}


/*
    PRINT A MAKEFILE

    This routine prints a makefile to build a TDF library for the API api
    from the list of files f.  There are two forms of the output, indicated
    by whole.
*/

void print_makefile
    PROTO_N ( ( api, f, whole ) )
    PROTO_T ( char *api X hash_elem *f X int whole )
{
    char *nm ;
    FILE *output ;
    hash_elem *e ;
    char *api2 = hack_name ( api, "_Aa0" ) ;
    int li = output_incl_len ;
    int ls = output_src_len ;

    /* Open output file */
    nm = ( whole ? MAKEFILE_API : MAKEFILE ) ;
    nm = string_printf ( nm, output_src_dir, api, api2 ) ;
    if ( verbose > 1 ) error ( ERR_INFO, "Creating %s ...", nm ) ;
    create_dir ( nm ) ;
    output = fopen ( nm, "w" ) ;
    if ( output == null ) {
	error ( ERR_SERIOUS, "Can't open output file, %s", nm ) ;
	return ;
    }

    /* Print file header */
    IGNORE fprintf ( output, "# AUTOMATICALLY GENERATED BY %s %s\n",
		     progname, progvers ) ;
    IGNORE fprintf ( output, "# MAKEFILE FOR %s API\n\n", api ) ;
    if ( whole ) {
	IGNORE fputs ( "TCC=tcc# Version of tcc\n", output ) ;
	IGNORE fprintf ( output, "LIB=%s.tl# TDF library\n", api2 ) ;
	IGNORE fputs ( "IMPL=/usr/include# API implementation directory\n",
		       output ) ;
	IGNORE fputs ( "WORK=.# Work directory\n\n", output ) ;
	IGNORE fprintf ( output, "INCL=%s# API header directory\n",
			 output_incl_dir ) ;
	IGNORE fprintf ( output, "SRC=%s# API auxiliary directory\n",
			 output_src_dir ) ;
	IGNORE fputs ( "PRE_FLAGS=\n", output ) ;
	IGNORE fprintf ( output, "INCL_FLAGS=-I${IMPL} -I${INCL}/%s%s\n",
		         api, OUTPUT_SUFFIX ) ;
	IGNORE fputs ( "POST_FLAGS=\n", output ) ;
	IGNORE fputs ( "TDI=${TCC} -D", output ) ;
	IGNORE fputs ( BUILDING_MACRO, output ) ;
	IGNORE fputs ( " ${PRE_FLAGS} ${INCL_FLAGS}", output ) ;
	IGNORE fputs ( " ${POST_FLAGS} -Fj\n", output ) ;
	IGNORE fputs ( "TDP=${TCC} -Ytdp ${INCL_FLAGS} -Fj\n", output ) ;
	IGNORE fputs ( "TNC=${TCC} -Ytnc -Fj\n", output ) ;
	IGNORE fputs ( "TLIB=${TCC} -Ymakelib\n\n", output ) ;
    }
    IGNORE fputs ( "SHELL=/bin/sh\n\n", output ) ;

    /* Print the list of files */
    IGNORE fputs ( "JFILES=", output ) ;
    for ( e = f ; e != null ; e = e->next ) {
	info *i = e->obj->u.u_info ;
	if ( need_info ( i, api ) ) {
	    int m ;
	    char *a = i->api ;
	    if ( strneq ( a, "shared/", 7 ) ) a += 7 ;
	    a = hack_name ( a, "_Aa0" ) ;
	    IGNORE sprintf ( buffer, "%s/%s", a, basename ( i->src ) ) ;
	    m = ( int ) strlen ( buffer ) - 1 ;
	    buffer [m] = 'j' ;
	    IGNORE fprintf ( output, "\\\n ${WORK}/%s", buffer ) ;
	}
    }
    IGNORE fputs ( "\n\nall : ${LIB}\n", output ) ;
    IGNORE fputs ( "\t@echo all done\n\n", output ) ;
    IGNORE fputs ( "${LIB} : ${JFILES}\n", output ) ;
    IGNORE fputs ( "\t@rm -f ${LIB}\n", output ) ;
    IGNORE fputs ( "\t${TLIB} -o ${LIB} ${JFILES}\n\n", output ) ;

    /* Print the construction for each file */
    for ( e = f ; e != null ; e = e->next ) {
	info *i = e->obj->u.u_info ;
	if ( need_info ( i, api ) ) {
	    int m ;
	    char *a = i->api ;
	    if ( strneq ( a, "shared/", 7 ) ) a += 7 ;
	    a = hack_name ( a, "_Aa0" ) ;
	    IGNORE sprintf ( buffer, "%s/%s", a, basename ( i->src ) ) ;
	    m = ( int ) strlen ( buffer ) - 1 ;
	    buffer [m] = 'j' ;
	    IGNORE fprintf ( output, "${WORK}/%s : ${SRC}/%s",
			     buffer, i->src + ls ) ;
	    if ( whole && i->incl ) {
		IGNORE fprintf ( output, "\\\n ${INCL}/%s ${IMPL}/%s",
				 i->incl + li, i->file ) ;
	    }
	    if ( whole ) {
		IGNORE fprintf ( output, "\n\t@ test -d ${WORK}/%s", a ) ;
		IGNORE fprintf ( output, " || mkdir ${WORK}/%s", a ) ;
	    }
	    if ( i->method == null ) {
		IGNORE fputs ( "\n\t${TDI} ", output ) ;
		if ( !whole ) {
		    IGNORE fprintf ( output, "-f${STARTUP}/%s.h ", a ) ;
		}
	    } else {
		IGNORE fprintf ( output, "\n\t${%s} ", i->method ) ;
	    }
	    IGNORE fprintf ( output, "-o ${WORK}/%s ${SRC}/%s\n\n",
			     buffer, i->src + ls ) ;
	}
    }

    /* End of makefile */
    IGNORE fputs ( "clean :\n\trm -f ${JFILES}\n\n", output ) ;
    IGNORE fputs ( "clobber : clean\n\trm -f ${LIB}\n", output ) ;
    IGNORE fclose ( output ) ;
    return ;
}
