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


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:47 $
$Revision: 1.1.1.1 $
$Log: misc_c.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
***********************************************************************/
#ifndef misc_c_key
#define misc_c_key 1



extern int invariant_to_apply PROTO_S ((exp e));
extern int take_out_of_line PROTO_S ((exp first, exp alt, int in_repeat, double scale));
extern int take_out_by_prob PROTO_S ((exp first, exp alt));
extern int is_maxop PROTO_S ((exp x, exp * t));
extern int is_minop PROTO_S ((exp x, exp * t));
extern int is_tester PROTO_S ((exp e, int eq));

#if condassign_implemented
extern int is_condassign PROTO_S ((exp e, exp * to_test, exp * to_ass));
#endif

#endif
