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


/* AUTOMATICALLY GENERATED BY %ZX VERSION %ZV FROM TDF %VA.%VB */

#include "config.h"
#include "common_types.h"
#include "basicread.h"
#include "ecodes.h"
#include "externs.h"
#include "messages_r.h"
#include "main_reads.h"
#include "check.h"


/* REPORT AN ERROR */

static void decode_error
    PROTO_N ( ( s ) )
    PROTO_T ( char *s )
{
    failer ( s ) ;
    exit ( EXIT_FAILURE ) ;
}
@use all
@special exp
@special nat computed_nat
@special signed_nat computed_signed_nat
@special tagdef make_var_tagdef
@special tagdef common_tagdef
@loop sort
@if !sort.builtin


/* DECODE %ST */

%SN d_%SN
    PROTO_Z ()
{
@if sort.basic
@if sort.extends
    int code = get_big_code ( %SB ) ;
@else
    int code = getcode ( %SB ) ;
@endif
    switch ( code ) {
@loop sort.cons
	case e_%CN : {
@if cons.params
@loop cons.param
	    %PSN p%PE ;
@end
@loop cons.param
@if param.align
	    to_boundary () ;
@endif
@if param.break
@if param.first
	    start_%CN () ;
@else
	    start_%CN (%
@loop param.prev
 p%PE,%
@end
%b ) ;
@endif
@endif
@if param.sort.special
@if cons.cond
	    p%PE = hold_const_check ( d_%PSN () ) ;
@else
@if cons.special
	    p%PE = hold_const_check ( d_%PSN () ) ;
@else
	    p%PE = hold_check ( d_%PSN () ) ;
@endif
@endif
@else
	    p%PE = d_%PSN () ;
@endif
@end
	    return ( f_%CN (%
@loop cons.param
 p%PE,%
@end
%b ) ) ;
@else
@if sort.special
	    return ( f_%CN () ) ;
@else
	    return ( f_%CN ) ;
@endif
@endif
	}
@end
    }
    decode_error ( ILLEGAL_CODE_%SN ) ;
    return ( f_dummy_%SN ) ;
@else
@if sort.dummy
@loop sort.cons
@loop cons.param
    %PSN p%PE ;
@end
@loop cons.param
@if param.align
    to_boundary () ;
@endif
@if param.break
    start_%CN (%
@loop param.prev
 p%PE,%
@end
%b ) ;
@endif
@if param.sort.special
    p%PE = hold_check ( d_%PSN () ) ;
@else
    p%PE = d_%PSN () ;
@endif
@end
    return ( f_%CN (%
@loop cons.param
 p%PE,%
@end
%b ) ) ;
@end
@else
@if sort.option
    if ( getcode ( 1 ) ) {
	%SSN e ;
@if sort.sub.special
	e = hold_check ( d_%SSN () ) ;
@else
	e = d_%SSN () ;
@endif
	return ( yes_%SN ( e ) ) ;
    }
    return ( no_%SN ) ;
@else
    int i, n ;
    %SN temp ;
@if sort.list
    IGNORE getcode ( 1 ) ;
@endif
    n = small_dtdfint () ;
    temp = new_%SN ( n ) ;
    for ( i = 0 ; i < n; i++ ) {
	%SSN e ;
@if sort.sub.special
	e = hold_check ( d_%SSN () ) ;
@else
	e = d_%SSN () ;
@endif
	temp = add_%SN ( temp, e, i ) ;
    }
    return ( temp ) ;
@endif
@endif
@endif
}
@endif
@end
