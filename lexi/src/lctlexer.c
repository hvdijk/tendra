
/*
 * Automatically generated by lexi version 2.0
 * Copyright terms for the input source also apply to this generated code.
 */

#include "lctlexer.h"



	#include "lctlexer.h"
	#include "lctsyntax.h"
	#include <shared/error.h>

	typedef int ZTTERMINAL;

	int crt_lct_token;
	int saved_lct_token;

	char lct_tokbuf[2000];
	static char *lct_token_end = lct_tokbuf + sizeof lct_tokbuf;
	static char *lct_token_current;

	NStringT lct_token_nstring;

	struct lexi_lct_state lct_lexer_state;

	static int
	lexi_lct_getchar(struct lexi_lct_state *state)
	{
		int c;

		c = fgetc(state->input);

		if (c == EOF) {
			return LEXI_EOF;
		}

		if (c == '\n') {
			crt_line_no++;
		}

		return c;
	}

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

int lexi_lct_readchar(struct lexi_lct_state *state) {
	if (state->buffer_index) {
		return lexi_lct_pop(state);
	}

	return lexi_lct_getchar(state);
}
void lexi_lct_push(struct lexi_lct_state *state, const int c) {
	assert(state);
	assert((size_t) state->buffer_index < sizeof state->buffer / sizeof *state->buffer);
	state->buffer[state->buffer_index++] = c;
}

int lexi_lct_pop(struct lexi_lct_state *state) {
	assert(state);
	assert(state->buffer_index > 0);
	return state->buffer[--state->buffer_index];
}

void lexi_lct_flush(struct lexi_lct_state *state) {
	state->buffer_index = 0;
}


/* LOOKUP TABLE */

typedef uint8_t lookup_type;
static lookup_type lookup_tab[] = {
	   0,    0,    0,    0,    0,    0,    0,    0,    0,  0x1,  0x1,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,  0x1,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	 0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,    0,    0, 
	   0,    0,    0,    0,    0,  0x6,  0x6,  0x6,  0x6,  0x6,  0x6,  0x6, 
	 0x6,  0x6,  0x6,  0x6,  0x6,  0x6,  0x6,  0x6,  0x6,  0x6,  0x6,  0x6, 
	 0x6,  0x6,  0x6,  0x6,  0x6,  0x6,  0x6,    0,    0,    0,    0,  0x6, 
	   0,  0x6,  0x6,  0x6,  0x6,  0x6,  0x6,  0x6,  0x6,  0x6,  0x6,  0x6, 
	 0x6,  0x6,  0x6,  0x6,  0x6,  0x6,  0x6,  0x6,  0x6,  0x6,  0x6,  0x6, 
	 0x6,  0x6,  0x6,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0
};

bool lexi_lct_group(enum lexi_lct_groups group, int c) {
	if (c == LEXI_EOF) {
		return 0;
	}
	return lookup_tab[c] & group;
}


#include <string.h>
int lexi_lct_keyword(const char *ident, int notfound) {
	if (0 == strcmp(ident, "ACTION")) return lct_lex_kw_Haction;
	if (0 == strcmp(ident, "ARGUMENT")) return lct_lex_kw_Hargument;
	if (0 == strcmp(ident, "HEADERS")) return lct_lex_kw_Hheader;
	if (0 == strcmp(ident, "TRAILERS")) return lct_lex_kw_Htrailer;
	return notfound;
}
/* PRE-PASS ANALYSERS */

void lexi_lct_init(struct lexi_lct_state *state, FILE_P_lct input) {
	state->zone = lexi_lct_read_token;
	state->buffer_index = 0;
	state->input = input;
}
/* ZONES PASS ANALYSER PROTOTYPES*/

static int lexi_lct_read_token_code_ref(struct lexi_lct_state *state);
static int lexi_lct_read_token_code_ident(struct lexi_lct_state *state);
static int lexi_lct_read_token_code(struct lexi_lct_state *state);
static void lexi_lct_read_token_linecomment(struct lexi_lct_state *state);
static void lexi_lct_read_token_comment(struct lexi_lct_state *state);
static int lexi_lct_read_token_ident(struct lexi_lct_state *state);
/* MAIN PASS ANALYSERS */


/* MAIN PASS ANALYSER for code_ref */
static int
lexi_lct_read_token_code_ref(struct lexi_lct_state *state)
{
	start: {
		int c0 = lexi_lct_readchar(state);
		if (!lexi_lct_group(lexi_lct_group_alnum, c0)) {
			lexi_lct_push(state, c0);
			/* ACTION <fini_tokbuf> */
			{

	if (lct_token_current == lct_token_end) {
		error(ERROR_FATAL, "Buffer overflow: trailing 0");
		*(lct_token_end - 1) = 0;
	} else {
		*lct_token_current++ = 0;
	}
			}
			/* END ACTION <fini_tokbuf> */
			return lct_lex_code_Href;
		}

		/* DEFAULT */
		/* ACTION <push_tokbuf> */
		{

	if (lct_token_current == lct_token_end - 1) {
		error(ERROR_FATAL, "Buffer overflow");
	} else {
		*lct_token_current++ = c0;
	}
		}
		/* END ACTION <push_tokbuf> */
		goto start; /* DEFAULT */
	}
}

/* MAIN PASS ANALYSER for code_ident */
static int
lexi_lct_read_token_code_ident(struct lexi_lct_state *state)
{
	start: {
		int c0 = lexi_lct_readchar(state);
		if (!lexi_lct_group(lexi_lct_group_alnum, c0)) {
			lexi_lct_push(state, c0);
			/* ACTION <fini_tokbuf> */
			{

	if (lct_token_current == lct_token_end) {
		error(ERROR_FATAL, "Buffer overflow: trailing 0");
		*(lct_token_end - 1) = 0;
	} else {
		*lct_token_current++ = 0;
	}
			}
			/* END ACTION <fini_tokbuf> */
			return lct_lex_code_Hident;
		}

		/* DEFAULT */
		/* ACTION <push_tokbuf> */
		{

	if (lct_token_current == lct_token_end - 1) {
		error(ERROR_FATAL, "Buffer overflow");
	} else {
		*lct_token_current++ = c0;
	}
		}
		/* END ACTION <push_tokbuf> */
		goto start; /* DEFAULT */
	}
}

/* MAIN PASS ANALYSER for code */
static int
lexi_lct_read_token_code(struct lexi_lct_state *state)
{
	start: {
		int c0 = lexi_lct_readchar(state);
		switch (c0) {
		case LEXI_EOF: {
				return lct_lex_code_Heof;
			}

		case '@': {
				int c1 = lexi_lct_readchar(state);
				switch (c1) {
				case '@': {
						return lct_lex_code_Hat;
					}

				case '&': {
						int c2 = lexi_lct_readchar(state);
						if (lexi_lct_group(lexi_lct_group_alpha, c2)) {
							/* ACTION <init_tokbuf> */
							{

	lct_token_current=lct_tokbuf;
							}
							/* END ACTION <init_tokbuf> */
							/* ACTION <push_tokbuf> */
							{

	if (lct_token_current == lct_token_end - 1) {
		error(ERROR_FATAL, "Buffer overflow");
	} else {
		*lct_token_current++ = c2;
	}
							}
							/* END ACTION <push_tokbuf> */
							return lexi_lct_read_token_code_ref(state);
						}
						lexi_lct_push(state, c2);
					}
					break;

				case '}': {
						state->zone = lexi_lct_read_token;
						return lct_lex_code_Hend;
					}

				}
				if (lexi_lct_group(lexi_lct_group_alpha, c1)) {
					/* ACTION <init_tokbuf> */
					{

	lct_token_current=lct_tokbuf;
					}
					/* END ACTION <init_tokbuf> */
					/* ACTION <push_tokbuf> */
					{

	if (lct_token_current == lct_token_end - 1) {
		error(ERROR_FATAL, "Buffer overflow");
	} else {
		*lct_token_current++ = c1;
	}
					}
					/* END ACTION <push_tokbuf> */
					return lexi_lct_read_token_code_ident(state);
				}
				lexi_lct_push(state, c1);
				return lct_lex_lone_Hcode_Hat;
			}

		}

		/* DEFAULT */
		/* ACTION <code_string> */
		{
			ZTTERMINAL ZT1;

	DStringT dstring;
	int c;

	dstring_init(&dstring);

	c = c0;

	do {
		dstring_append_char(&dstring, c);
		c = lexi_lct_readchar(&lct_lexer_state);
	} while(c != '@' && c != LEXI_EOF);

	lexi_lct_push(&lct_lexer_state, c);

	dstring_to_nstring(&dstring, &lct_token_nstring);
	dstring_destroy(&dstring);

	ZT1 = lct_lex_code_Hstring;
			return ZT1;
		}
		/* END ACTION <code_string> */
		goto start; /* DEFAULT */
	}
}

/* MAIN PASS ANALYSER for linecomment */
static void
lexi_lct_read_token_linecomment(struct lexi_lct_state *state)
{
	start: {
		int c0 = lexi_lct_readchar(state);
		if (c0 == '\n') {
			return;
		}

		/* DEFAULT */
		goto start; /* DEFAULT */
	}
}

/* MAIN PASS ANALYSER for comment */
static void
lexi_lct_read_token_comment(struct lexi_lct_state *state)
{
	start: {
		int c0 = lexi_lct_readchar(state);
		if (c0 == '*') {
			int c1 = lexi_lct_readchar(state);
			if (c1 == '/') {
				return;
			}
			lexi_lct_push(state, c1);
		}

		/* DEFAULT */
		goto start; /* DEFAULT */
	}
}

/* MAIN PASS ANALYSER for ident */
static int
lexi_lct_read_token_ident(struct lexi_lct_state *state)
{
	start: {
		int c0 = lexi_lct_readchar(state);
		if (!lexi_lct_group(lexi_lct_group_alnum, c0)) {
			lexi_lct_push(state, c0);
			/* ACTION <fini_tokbuf> */
			{

	if (lct_token_current == lct_token_end) {
		error(ERROR_FATAL, "Buffer overflow: trailing 0");
		*(lct_token_end - 1) = 0;
	} else {
		*lct_token_current++ = 0;
	}
			}
			/* END ACTION <fini_tokbuf> */
			/* ACTION <keyword> */
			{
				ZTTERMINAL ZT1;

	ZT1 = lexi_lct_keyword(lct_tokbuf, lct_lex_ident);
				return ZT1;
			}
			/* END ACTION <keyword> */
		}

		/* DEFAULT */
		/* ACTION <push_tokbuf> */
		{

	if (lct_token_current == lct_token_end - 1) {
		error(ERROR_FATAL, "Buffer overflow");
	} else {
		*lct_token_current++ = c0;
	}
		}
		/* END ACTION <push_tokbuf> */
		goto start; /* DEFAULT */
	}
}

/* MAIN PASS ANALYSER for the global zone */
int
lexi_lct_read_token(struct lexi_lct_state *state)
{
	if (state->zone != lexi_lct_read_token)
		return state->zone(state);
	start: {
		int c0 = lexi_lct_readchar(state);
		if (lexi_lct_group(lexi_lct_group_white, c0)) goto start;
		switch (c0) {
		case '@': {
				int c1 = lexi_lct_readchar(state);
				if (c1 == '{') {
					state->zone = lexi_lct_read_token_code;
					return lct_lex_code_Hstart;
				}
				lexi_lct_push(state, c1);
			}
			break;

		case '/': {
				int c1 = lexi_lct_readchar(state);
				switch (c1) {
				case '/': {
						lexi_lct_read_token_linecomment(state);
						goto start;	/* pure function */
					}

				case '*': {
						lexi_lct_read_token_comment(state);
						goto start;	/* pure function */
					}

				}
				lexi_lct_push(state, c1);
			}
			break;

		case LEXI_EOF: {
				return lct_lex_eof;
			}

		case '-': {
				int c1 = lexi_lct_readchar(state);
				if (c1 == '>') {
					return lct_lex_arrow;
				}
				lexi_lct_push(state, c1);
			}
			break;

		case ',': {
				return lct_lex_comma;
			}

		case ':': {
				return lct_lex_colon;
			}

		case ';': {
				return lct_lex_semicolon;
			}

		case '&': {
				return lct_lex_ref;
			}

		case '=': {
				return lct_lex_define;
			}

		case ')': {
				return lct_lex_close;
			}

		case '(': {
				return lct_lex_open;
			}

		}
		if (lexi_lct_group(lexi_lct_group_alpha, c0)) {
			/* ACTION <init_tokbuf> */
			{

	lct_token_current=lct_tokbuf;
			}
			/* END ACTION <init_tokbuf> */
			/* ACTION <push_tokbuf> */
			{

	if (lct_token_current == lct_token_end - 1) {
		error(ERROR_FATAL, "Buffer overflow");
	} else {
		*lct_token_current++ = c0;
	}
			}
			/* END ACTION <push_tokbuf> */
			return lexi_lct_read_token_ident(state);
		}

		/* DEFAULT */
		return lct_lex_unknown;
	}
}


