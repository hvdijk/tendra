/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
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

#include <stdio.h>
#include <string.h>

#include "error.h"
#include "xalloc.h"

#include "lex.h"
#include "syntax.h"


/*
    INPUT FILE

    This is the file from which the lexical routine read their input.
*/

static FILE *lex_input;


/*
    PENDING BUFFER

    Pending characters are dealt with by means of this buffer.  pending
    is set to the start of the buffer to indicate that there are no
    characters pending, otherwise the pending characters are stored in
    the buffer.  The buffer may need increasing in size if the look-ahead
    required by the lexical analyser increases.
*/

static int pending_buff [12] = { '?' };
static int *pending = pending_buff;


/*
    MAPPINGS AND DECLARATIONS FOR AUTOMATICALLY GENERATED SECTION

    These macros give the mappings between the actions used in the
    automatically generated lexical analyser and the routines defined
    in this file.
*/

static int read_char(void);
static int read_comment(void);
static int read_identifier(int, int);
static int read_string(void);

#define get_comment(A, B)	read_comment()
#define get_identifier(A)	read_identifier((A), 0)
#define get_sid_ident(A, B)	read_identifier((B), 1)
#define get_string(A)		read_string()
#define unknown_token(A)	lex_unknown
#define unread_char(A)	*(++pending) = (A)

static int read_arg_char_nb(int,int) ;

/*
    AUTOMATICALLY GENERATED SECTION

    The main body of the lexical analyser is automatically generated.
*/

#include "lexer.h"


/*
    GET THE NEXT CHARACTER

    This routine reads the next character, either from the pending buffer
    or from the input file.
*/

static int
read_char(void)
{
    int c;
    if (pending != pending_buff) {
	c = *(pending--);
    } else {
	c = fgetc(lex_input);
	if (c == '\n')crt_line_no++;
	if (c == EOF) return(LEX_EOF);
	c &= 0xff;
    }
    return(c);
}


/*
    TOKEN BUFFER

    This buffer is used by read_token to hold the values of identifiers
    and strings.
*/

char token_buff [2000];
static char *token_end = token_buff + sizeof(token_buff);
char *first_comment = NULL;
unsigned int number_buffer;

/*
    READ AN IDENTIFIER

    This routine reads an identifier beginning with a, returning the
    corresponding lexical token.  Keywords are dealt with locally.
    The sid flag indicates whether a sid-style identifier is expected.
*/

static int
read_identifier(int a, int sid)
{
    int c = a, cl;
    int e = (sid ? '-' : 'x');
    char *t = token_buff;
    do {
	*(t++) = (char)c;
	if (t == token_end)error(ERROR_FATAL, "Buffer overflow");
	c = read_char();
	cl = lookup_char(c);
    } while (is_alphanum(cl) || c == e);
    *t = 0;
    unread_char(c);

    /* Deal with keywords */
    if (sid) return(lex_sid_Hidentifier);
    t = token_buff;
#define MAKE_KEYWORD(A, B)\
    if (!strcmp(t,(A))) return(B);
#include "keyword.h"
    return(lex_identifier);
}


/*
    READ A STRING

    This routine reads a string.  It is entered after the initial
    quote has been read.
*/

static int
read_string(void)
{
    int c;
    int escaped = 0;
    char *t = token_buff;
    while (c = read_char(), (c != '"' || escaped)) {
	if (c == '\n' || c == LEX_EOF) {
	    error(ERROR_SERIOUS, "Unexpected end of string");
	    break;
	}
	*(t++) = (char)c;
	if (t == token_end)error(ERROR_FATAL, "Buffer overflow");
	if (escaped) {
	    escaped = 0;
	} else {
	    if (c == '\\')escaped = 1;
	}
    }
    *t = 0;
    return(lex_string);
}


/*
    READ A COMMENT

    This routine reads a C style comment, returning the lexical token
    immediately following.  It is entered after the first two characters
    have been read.
*/

static int
read_comment(void)
{
    int state = 0;
    char *t = token_buff;
    *(t++) = '/';
    *(t++) = '*';
    while (state != 2) {
	int c = read_char();
	if (c == LEX_EOF) {
	    error(ERROR_SERIOUS, "End of file in comment");
	    return(lex_eof);
	}
	if (c == '*') {
	    state = 1;
	} else if (state == 1 && c == '/') {
	    state = 2;
	} else {
	    state = 0;
	}
	*(t++) = (char)c;
	if (t == token_end)t = token_buff + 2;
    }
    *t = 0;
    if (first_comment == NULL)first_comment = xstrcpy(token_buff);
    return(read_token());
}

/*
  Char to integer. There is probably a standard way to do this
 */

static short chartoint (int c) {
  switch (c) {
  case '0':
    return 0;
  case '1':
    return 1;
  case '2':
    return 2;
  case '3':
    return 3;
  case '4':
    return 4;
  case '5':
    return 5;
  case '6':
    return 6;
  case '7':
    return 7;
  case '8':
    return 8;
  case '9':
    return 9;
  }
}

/*
  Arg TOKEN number
 */
static int read_arg_char_nb(int c0, int c1)  
{
  int c;
  number_buffer=chartoint(c1);
  while(isdigit(c=lexi_readchar())){
    number_buffer*=10;
    number_buffer+=chartoint(c);
  }
  lexi_push(c);
  return lex_arg_Hchar_Hnb;
}

/*
    CURRENT TOKEN

    These variables are used by the parser to hold the current and former
    lexical tokens.
*/

int crt_lex_token;
int saved_lex_token;


/*
    PROCESS FILE

    This routine processes the input file nm.
*/

void
process_file(char *nm,lexer_parse_tree* top_level)
{
    crt_line_no = 1;
    if (nm == NULL || !strcmp(nm, "-")) {
	crt_file_name = "<stdin>";
	lex_input = stdin;
	nm = NULL;
    } else {
	crt_file_name = nm;
	lex_input = fopen(nm, "r");
	if (lex_input == NULL) {
	    error(ERROR_SERIOUS, "Can't open input file, '%s'", nm);
	    return;
	}
    }
    ADVANCE_LEXER;
    read_lex(top_level->global_zone);
    if (nm)fclose(lex_input);
    return;
}
