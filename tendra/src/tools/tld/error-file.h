/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


/**** error-file.h --- Error file parsing routines.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 ***=== INTRODUCTION =========================================================
 *
 * This file specifies the interface to an error description file parsing
 * facility.  This facility extends the error reporting facility specified in
 * the file "error.h" so that error messages may be redefined by the contents
 * of a file.
 *
 ***=== FUNCTIONS ============================================================
 *
 *
 ** Function:	void			error_file_parse
 *			PROTO_S ((CStringP name, BoolT must_open))
 ** Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function parses the error file with the specified name.  If must_open
 * is true, then an error will be reported if the file cannot be opened.
 * Otherwise, the function will just return silently.
 *
 * The format of the file is a sequence of sections.  Sections may appear in
 * any order, and may be repeated.  There are three section types: '%prefix%',
 * '%errors%', and '%strings%'.  The prefix section contains a single string,
 * which is to be used as the error message prefix.  The error and string
 * sections contain a sequence of name and string pairs, where the name names
 * the error or string being redefined, and the string specifies the new
 * contents.  A name is a sequence of characters contained in single quotes,
 * and a string is a sequence of characters contained in double quotes.  In
 * both, the backslash character can be used to escape characters in a similar
 * manner to C.  An example follows:
 *
 *	%prefix% "new error prefix"
 *	%error%
 *		'error message 1' "new error message 1 message"
 *	%string%
 *		'string 1' "new string 1 text"
 *
 * In addition, the '#' character can be used as a comment to end of line
 * character.  Such comments are ignored.
 *
 **** Change log:*/

/****************************************************************************/

#ifndef H_ERROR_FILE
#define H_ERROR_FILE

#include "os-interface.h"
#include "cstring.h"
#include "istream.h"

/*--------------------------------------------------------------------------*/

extern void			error_file_parse(CStringP, BoolT);

#endif /* !defined (H_ERROR_FILE) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../generated")
 * end:
 **/
