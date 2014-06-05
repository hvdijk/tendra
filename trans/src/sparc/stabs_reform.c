/* $Id$ */

/* TODO: interface for diag/ to call mips local stabs */

#include <diag/diag_reform.h>

diag_descriptor *
NEW_DIAG_GLOBAL(diag_descriptor *d)
{
	return d;
}

void
OUTPUT_GLOBALS_TAB(void)
{
	stab_typedefs();
}

void
OUTPUT_DIAG_TAGS(void)
{
	stab_tagdefs();
}

void
INSPECT_FILENAME(filename f)
{
	stab_collect_files(f);
}

