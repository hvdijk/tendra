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

#ifndef EXTERNS_INCLUDED
#define EXTERNS_INCLUDED

@use all
@special exp
@loop sort
@if !sort.builtin

/* CONSTRUCTS FOR %ST */
@if sort.simple
@loop sort.cons
@if cons.params
@loop cons.param
@if param.break
@if param.first
extern void start_%CN PROTO_S ( ( void ) ) ;
@else
extern void start_%CN PROTO_S ( (%
@loop param.prev
 %PSN,%
@end
%b ) ) ;
@endif
@endif
@end
extern %SN f_%CN PROTO_S ( (%
@loop cons.param
 %PSN,%
@end
%b ) ) ;
@else
@if sort.special
extern %SN f_%CN PROTO_S ( ( void ) ) ;
@else
extern %SN f_%CN ;
@endif
@endif
@end
extern %SN f_dummy_%SN ;
@else
@if sort.option
extern %SN yes_%SN PROTO_S ( ( %SSN ) ) ;
extern %SN no_%SN ;
@else
extern %SN new_%SN PROTO_S ( ( int ) ) ;
extern %SN add_%SN PROTO_S ( ( %SN, %SSN, int ) ) ;
@endif
@endif
extern void init_%SN PROTO_S ( ( void ) ) ;
@endif
@end


#endif
