/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#define __SID_SPLIT
#line 177 "syntax.act"


/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/check.h>

#include "config.h"
#include "c_types.h"
#include "ctype_ops.h"
#include "exp_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "nspace_ops.h"
#include "type_ops.h"
#include "error.h"
#include "catalog.h"
#include "option.h"
#include "access.h"
#include "allocate.h"
#include "assign.h"
#include "basetype.h"
#include "cast.h"
#include "chktype.h"
#include "class.h"
#include "constant.h"
#include "construct.h"
#include "convert.h"
#include "declare.h"
#include "derive.h"
#include "dump.h"
#include "exception.h"
#include "expression.h"
#include "function.h"
#include "hash.h"
#include "identifier.h"
#include "initialise.h"
#include "inttype.h"
#include "label.h"
#include "lex.h"
#include "literal.h"
#include "member.h"
#include "namespace.h"
#include "parse.h"
#include "pragma.h"
#include "predict.h"
#include "preproc.h"
#include "redeclare.h"
#include "rewrite.h"
#include "statement.h"
#include "symbols.h"
#include "template.h"
#include "tokdef.h"
#include "token.h"
#include "typeid.h"
#include "variable.h"


/*
    These are the aliases for the compound types used in the parser.
*/

typedef LIST ( EXP ) SID_LIST_EXP ;
typedef LIST ( TYPE ) SID_LIST_TYPE ;


/*
    The function declarations are included at this point so that the
    type definitions are in scope.
*/

#include "syntax.h"


#line 97 "syntax9.c"

void
ZR1141(TYPE ZI1139, TYPE *ZO1140)
{
	TYPE ZI1140;

ZL2_1141:;
	switch (CURRENT_TERMINAL) {
	case 65: case 66: case 332:
		{
			TYPE ZIq;
			TYPE ZIt;

			ZRabstract_Hdeclarator_Htail (&ZIq);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_build */
			{
#line 1386 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1139) ) ? (ZIq) : inject_pre_type ( (ZI1139), (ZIq), 0 ) ) ;
#line 121 "syntax9.c"
			}
			/* END OF ACTION: type_build */
			/* BEGINNING OF INLINE: 1141 */
			ZI1139 = ZIt;
			goto ZL2_1141;
			/* END OF INLINE: 1141 */
		}
		UNREACHED;
	default:
		{
			ZI1140 = ZI1139;
		}
		break;
	case 355:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZO1140 = ZI1140;
}

void
ZR887(BASE_TYPE *ZIb1, TYPE *ZIt1, CV_SPEC *ZIcv1, BASE_TYPE *ZObt, TYPE *ZOt, CV_SPEC *ZOcv)
{
	BASE_TYPE ZIbt;
	TYPE ZIt;
	CV_SPEC ZIcv;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		TYPE ZIs;
		BASE_TYPE ZI1392;
		TYPE ZI1393;
		CV_SPEC ZI1394;
		BASE_TYPE ZIb2;
		TYPE ZIt2;
		CV_SPEC ZIcv2;

		/* BEGINNING OF ACTION: is_type_specifier */
		{
#line 2113 "syntax.act"

    /* Resolve type-specifiers from other declarators */
    (ZI0) = predict_tspec ( 0 ) ;
#line 171 "syntax9.c"
		}
		/* END OF ACTION: is_type_specifier */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF ACTION: type_none */
		{
#line 1265 "syntax.act"

    (ZIs) = NULL_type ;
#line 181 "syntax9.c"
		}
		/* END OF ACTION: type_none */
		ZRtype_Hspecifier (ZIs, &ZI1392, &ZI1393, &ZI1394);
		ZR887 (&ZI1392, &ZI1393, &ZI1394, &ZIb2, &ZIt2, &ZIcv2);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: btype_join */
		{
#line 1244 "syntax.act"

    if ( (*ZIb1) & (ZIb2) ) {
	(ZIbt) = join_pre_types ( (*ZIb1), (ZIb2) ) ;
    } else {
	(ZIbt) = ( (*ZIb1) | (ZIb2) ) ;
    }
#line 199 "syntax9.c"
		}
		/* END OF ACTION: btype_join */
		/* BEGINNING OF ACTION: type_join */
		{
#line 1299 "syntax.act"

    /* Join two partial types */
    if ( IS_NULL_type ( (*ZIt1) ) ) {
	(ZIt) = (ZIt2) ;
    } else if ( IS_NULL_type ( (ZIt2) ) ) {
	(ZIt) = (*ZIt1) ;
    } else {
	report ( crt_loc, ERR_dcl_type_simple_many ( (*ZIt1), (ZIt2) ) ) ;
	(ZIt) = (ZIt2) ;
    }
#line 215 "syntax9.c"
		}
		/* END OF ACTION: type_join */
		/* BEGINNING OF ACTION: cv_join */
		{
#line 1214 "syntax.act"

    CV_SPEC c = ( (*ZIcv1) & (ZIcv2) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZIcv) = ( (*ZIcv1) | (ZIcv2) ) ;
#line 225 "syntax9.c"
		}
		/* END OF ACTION: cv_join */
		goto ZL0;
	}
	UNREACHED;
ZL2:;
	switch (CURRENT_TERMINAL) {
	default:
		{
			ZIbt = *ZIb1;
			ZIt = *ZIt1;
			ZIcv = *ZIcv1;
		}
		break;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZObt = ZIbt;
	*ZOt = ZIt;
	*ZOcv = ZIcv;
}

void
ZRmultiplicative_Hexpression(EXP *ZO1233)
{
	EXP ZI1233;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		EXP ZIe;

		ZRpm_Hexpression (&ZIe);
		ZR1234 (ZIe, &ZI1233);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZO1233 = ZI1233;
}

void
ZR1396(NAMESPACE *ZI1395, IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	switch (CURRENT_TERMINAL) {
	case 1: case 3: case 5: case 6:
	case 141: case 147:
		{
			int ZIq;
			IDENTIFIER ZIuid;

			ZRtemplate_Hopt (*ZI1395, &ZIq);
			ZRnested_Hid (*ZI1395, &ZIuid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: namespace_templ */
			{
#line 508 "syntax.act"

    (ZIid) = check_id ( (*ZI1395), (ZIuid), (ZIq) ) ;
    last_namespace = (*ZI1395) ;
#line 301 "syntax9.c"
			}
			/* END OF ACTION: namespace_templ */
		}
		break;
	case 43:
		{
			IDENTIFIER ZIid1;
			BASE_TYPE ZIbt1;
			QUALIFIER ZIi;
			int ZIb;
			IDENTIFIER ZIid2;
			BASE_TYPE ZIbt2;
			IDENTIFIER ZIuid;

			/* BEGINNING OF ACTION: namespace_type */
			{
#line 513 "syntax.act"

    (ZIid1) = DEREF_id ( nspace_name ( (*ZI1395) ) ) ;
#line 321 "syntax9.c"
			}
			/* END OF ACTION: namespace_type */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1241 "syntax.act"
 (ZIbt1) = btype_none ; 
#line 328 "syntax9.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: qual_get */
			{
#line 525 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 337 "syntax9.c"
			}
			/* END OF ACTION: qual_get */
			/* BEGINNING OF INLINE: compl */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 43:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: compl */
			ZRpseudo_Hdestr_Hsuffix (&ZIid2, &ZIbt2);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: qual_set */
			{
#line 530 "syntax.act"

    crt_id_qualifier = (ZIi) ;
    crt_templ_qualifier = (ZIb) ;
#line 364 "syntax9.c"
			}
			/* END OF ACTION: qual_set */
			/* BEGINNING OF ACTION: pseudo_destructor */
			{
#line 444 "syntax.act"

    (ZIuid) = make_pseudo_destr ( (ZIid1), (ZIbt1), (ZIid2), (ZIbt2) ) ;
#line 372 "syntax9.c"
			}
			/* END OF ACTION: pseudo_destructor */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 491 "syntax.act"

    (ZIid) = check_id ( (*ZI1395), (ZIuid), 0 ) ;
    last_namespace = (*ZI1395) ;
#line 381 "syntax9.c"
			}
			/* END OF ACTION: namespace_id */
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOid = ZIid;
}

void
ZR1269(NAMESPACE *ZIns, EXP *ZO1241)
{
	EXP ZI1241;

	switch (CURRENT_TERMINAL) {
	case 2: case 7:
		{
			IDENTIFIER ZItid;
			IDENTIFIER ZIid;
			TYPE ZI1267;
			BASE_TYPE ZIbt;
			CV_SPEC ZIcv;
			TYPE ZIt;
			SID_LIST_EXP ZIp;
			EXP ZIe;

			/* BEGINNING OF INLINE: any-type-name */
			{
				switch (CURRENT_TERMINAL) {
				case 7:
					{
						/* BEGINNING OF EXTRACT: template-type */
						{
#line 236 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZItid = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 430 "syntax9.c"
						}
						/* END OF EXTRACT: template-type */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 210 "syntax.act"

    ZItid = crt_token->pp_data.id.use ;
#line 443 "syntax9.c"
						}
						/* END OF EXTRACT: type-name */
						ADVANCE_LEXER;
					}
					break;
				default:
					goto ZL1;
				}
			}
			/* END OF INLINE: any-type-name */
			/* BEGINNING OF ACTION: namespace_full */
			{
#line 487 "syntax.act"

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZIns) ;
#line 460 "syntax9.c"
			}
			/* END OF ACTION: namespace_full */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 491 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZItid), 0 ) ;
    last_namespace = (*ZIns) ;
#line 469 "syntax9.c"
			}
			/* END OF ACTION: namespace_id */
			/* BEGINNING OF ACTION: type_name */
			{
#line 1274 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI1267) ) ;
    COPY_id ( type_name ( (ZI1267) ), (ZIid) ) ;
    have_type_specifier = 1 ;
#line 479 "syntax9.c"
			}
			/* END OF ACTION: type_name */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1241 "syntax.act"
 (ZIbt) = btype_none ; 
#line 486 "syntax9.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1209 "syntax.act"
 (ZIcv) = cv_none ; 
#line 493 "syntax9.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1310 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1267), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 502 "syntax9.c"
			}
			/* END OF ACTION: type_complete */
			switch (CURRENT_TERMINAL) {
			case 65:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRexpression_Hlist_Hopt (&ZIp);
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			case 355:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_func_cast */
			{
#line 669 "syntax.act"

    (ZIe) = make_func_cast_exp ( (ZIt), (ZIp) ) ;
#line 528 "syntax9.c"
			}
			/* END OF ACTION: exp_func_cast */
			ZR1242 (ZIe, &ZI1241);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 1: case 3: case 5: case 6:
	case 141: case 147:
		{
			int ZIq;
			IDENTIFIER ZIuid;
			IDENTIFIER ZIid;
			EXP ZIe;

			ZRtemplate_Hopt (*ZIns, &ZIq);
			ZRnested_Hid (*ZIns, &ZIuid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: namespace_full */
			{
#line 487 "syntax.act"

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZIns) ;
#line 558 "syntax9.c"
			}
			/* END OF ACTION: namespace_full */
			/* BEGINNING OF ACTION: namespace_templ */
			{
#line 508 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZIuid), (ZIq) ) ;
    last_namespace = (*ZIns) ;
#line 567 "syntax9.c"
			}
			/* END OF ACTION: namespace_templ */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 673 "syntax.act"

    (ZIe) = make_id_exp ( (ZIid) ) ;
#line 575 "syntax9.c"
			}
			/* END OF ACTION: exp_identifier */
			ZR1242 (ZIe, &ZI1241);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZO1241 = ZI1241;
}

/* BEGINNING OF TRAILER */

#line 2166 "syntax.act"

#line 602 "syntax9.c"

/* END OF FILE */
