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


/*
$Log: guard.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:02  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/12/18  13:11:27  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.0  1995/08/25  13:42:58  wfs
 * Preperation for August 25 Glue release
 *
 * Revision 3.4  1995/08/25  11:12:16  wfs
 * *** empty log message ***
 *
 * Revision 3.4  1995/08/25  11:12:16  wfs
 * *** empty log message ***
 *
 * Revision 3.1  95/04/10  16:26:38  16:26:38  wfs (William Simmonds)
 * Apr95 tape version.
 * 
 * Revision 3.0  95/03/30  11:17:17  11:17:17  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 * 
 * Revision 2.0  95/03/15  15:27:05  15:27:05  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 * 
 * Revision 1.1  95/01/11  13:38:59  13:38:59  wfs (William Simmonds)
 * Initial revision
 * 
*/


#ifndef GUARDDECS_INCLUDED
#define GUARDDECS_INCLUDED

#include "procrec.h"
#include "addrtypes.h"

extern space guardreg PROTO_S ( ( int, space ) ) ;
extern space guardfreg PROTO_S ( ( int, space ) ) ;
extern space guard PROTO_S ( ( where, space ) ) ;
extern space needreg PROTO_S ( ( int, space ) ) ;
extern space needfreg PROTO_S ( ( int, space ) ) ;

#endif /* GUARDDECS_INCLUDED */
