
/*
 * Automatically generated by lexi version 2.0
 * Copyright terms for the input source also apply to this generated code.
 */

#ifndef LEXI_GENERATED_HEADER_lexi_lct__INCLUDED
#define LEXI_GENERATED_HEADER_lexi_lct__INCLUDED



	#include <stdio.h>
	#include "lctsyntax.h"

	typedef FILE *FILE_P_lct;

	extern char lct_tokbuf[];
	int curr_lct_token;
	int saved_lct_token;
	struct lct_ast lct_ast;

	struct lexi_lct_state lct_lexer_state;
	NStringT lct_token_nstring;

	#define CURRENT_LCT_TERMINAL curr_lct_token
	#define ADVANCE_LCT_LEXER    curr_lct_token = lexi_lct_read_token(&lct_lexer_state)
	#define SAVE_LCT_LEXER(T)    (saved_lct_token = curr_lct_token, curr_lct_token = (T))
	#define RESTORE_LCT_LEXER    (curr_lct_token = saved_lct_token)

#include <stdbool.h>

/*
 * This struct holds state for the lexer; its representation is
 * private, but present here for ease of allocation.
 */
struct lexi_lct_state {
	int (*zone)(struct lexi_lct_state *);

	/*
	 * Lexi's buffer is a simple stack.
	 */
	int buffer[2];
	int buffer_index;
	FILE_P_lct input;
};

/* Read a character */
int lexi_lct_readchar(struct lexi_lct_state *state);

/* Push a character to lexi's buffer */
void lexi_lct_push(struct lexi_lct_state *state, const int c);

/* Pop a character from lexi's buffer */
int lexi_lct_pop(struct lexi_lct_state *state);

/* Flush lexi's buffer */
void lexi_lct_flush(struct lexi_lct_state *state);

#ifndef LEXI_EOF
#define LEXI_EOF -1
#endif

enum lexi_lct_groups {
	lexi_lct_group_white = 0x1,
	lexi_lct_group_alnum = 0x2,
	lexi_lct_group_alpha = 0x4,
	lexi_lct_code_white = 0,
	lexi_lct_linecomment_white = 0,
	lexi_lct_comment_white = 0,
	lexi_lct_ident_white = 0,
};

/* true if the given character is present in the given group */
bool lexi_lct_group(enum lexi_lct_groups group, int c);

/* Identify a keyword */
int lexi_lct_keyword(const char *ident, int notfound);

/* Identify a token */
int lexi_lct_read_token(struct lexi_lct_state *state);

/* Initialise a lexi_lct_state structure */
void lexi_lct_init(struct lexi_lct_state *state, FILE_P_lct input);


#endif

