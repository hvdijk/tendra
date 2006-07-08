/*
 * Copyright (c) 2002-2006 The TenDRA Project <http://www.tendra.org/>.
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


/*** name-table.c --- Name table ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the name table routines used by the TDF linker.
 *
 *** Change Log:
 * $Log: name-table.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:19  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/09/22  08:39:29  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 * Fixed some problems in "name-key.c" (no real problems, but rewritten to
 * reduce the warnings that were output by "tcc" and "gcc").
 * Fixed bug CR95_354.tld-common-id-problem (library capsules could be loaded
 * more than once).
 *
 * Revision 1.2  1994/12/12  11:46:42  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:36  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#include "name-table.h"
#include "shape-entry.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

NameTableP
name_table_create(void)
{
    NameTableP table = ALLOCATE(NameTableT);
    unsigned   i;

    for (i = 0; i < NAME_TABLE_SIZE; i++) {
	table->contents[i] = NIL(NameEntryP);
    }
    return(table);
}

void
name_table_add_rename(NameTableP table,			       NameKeyP   from, 
			       NameKeyP   to)
{
    unsigned    to_hash_value = (name_key_hash_value(to)% NAME_TABLE_SIZE);
    NameEntryP *to_entryp     = & (table->contents[to_hash_value]);
    unsigned    hash_value    = (name_key_hash_value(from)% NAME_TABLE_SIZE);
    NameEntryP *from_entryp   = & (table->contents[hash_value]);
    NameEntryP  to_entry;
    NameEntryP  from_entry;

    while ((to_entry = *to_entryp) != NIL(NameEntryP)) {
	if (name_key_equal(to, name_entry_key(to_entry))) {
	    goto found;
	}
	to_entryp = name_entry_next_ref(to_entry);
    }
    to_entry   = name_entry_create_place(to);
    *to_entryp = to_entry;
  found:
    while ((from_entry = *from_entryp) != NIL(NameEntryP)) {
	if (name_key_equal(from, name_entry_key(from_entry))) {
	    name_entry_make_indirect(from_entry, to_entry);
	    return;
	}
	from_entryp = name_entry_next_ref(from_entry);
    }
    from_entry   = name_entry_create_indirect(from, to_entry);
    *from_entryp = from_entry;
}

void
name_table_resolve_renames(NameTableP table,				    NStringP   shape, 
				    BoolT      report)
{
    unsigned i;

    for (i = 0; i < NAME_TABLE_SIZE; i++) {
	NameEntryP entry = (table->contents[i]);

	while (entry) {
	   (void)name_entry_resolve_renames(entry, shape, report);
	    entry = name_entry_next(entry);
	}
    }
}

NameEntryP
name_table_add(NameTableP  table,			NameKeyP    key, 
			ShapeEntryP shape_entry)
{
    unsigned    hash_value = (name_key_hash_value(key)% NAME_TABLE_SIZE);
    NameEntryP *entryp     = & (table->contents[hash_value]);
    NameEntryP  entry;

    while ((entry = *entryp) != NIL(NameEntryP)) {
	if (name_key_equal(key, name_entry_key(entry))) {
	    if (name_entry_is_indirect(entry)) {
		entry = name_entry_get_indirect(entry);
	    }
	    if (name_entry_is_place(entry)) {
		name_entry_make_direct(entry, shape_entry);
	    }
	    return(entry);
	}
	entryp = name_entry_next_ref(entry);
    }
    entry   = name_entry_create_direct(key, shape_entry);
    *entryp = entry;
    return(entry);
}

NameEntryP
name_table_get(NameTableP table,			NameKeyP   key)
{
    unsigned   hash_value = (name_key_hash_value(key)% NAME_TABLE_SIZE);
    NameEntryP entry      = table->contents[hash_value];

    while (entry) {
	if (name_key_equal(key, name_entry_key(entry))) {
	    if (name_entry_is_indirect(entry)) {
		entry = name_entry_get_indirect(entry);
	    }
	    if (name_entry_is_place(entry)) {
		return(NIL(NameEntryP));
	    }
	    return(entry);
	}
	entry = name_entry_next(entry);
    }
    return(NIL(NameEntryP));
}

void
name_table_iter(NameTableP table, void(*proc)(NameEntryP, GenericP),
		GenericP closure)
{
    unsigned i;

    for (i = 0; i < NAME_TABLE_SIZE; i++) {
	NameEntryP entry = (table->contents[i]);

	while (entry) {
	    if (name_entry_is_direct(entry)) {
		(*proc)(entry, closure);
	    }
	    entry = name_entry_next(entry);
	}
    }
}

void
name_table_deallocate(NameTableP table)
{
    unsigned i;

    for (i = 0; i < NAME_TABLE_SIZE; i++) {
	NameEntryP entry = (table->contents[i]);

	while (entry) {
	    entry = name_entry_deallocate(entry);
	}
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
