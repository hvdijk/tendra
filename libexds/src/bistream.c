/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * bistream.c - Binary input stream handling.
 *
 * This file implements the binary input stream facility specified in the file
 * "bistream.h".  See that file for more details.
 */

#include <stdio.h>
#include <stddef.h>

#include <shared/bool.h>
#include <shared/check.h>

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/bistream.h>
#include <exds/cstring.h>

ExceptionT *XX_bistream_read_error = EXCEPTION("error reading from binary stream");

void
bistream_init(BIStreamT *bistream)
{
    bistream->name = NULL;
}

bool
bistream_open(BIStreamT *bistream, const char *name)
{
	if ((bistream->file = fopen(name, "r")) == NULL) {
		return false;
	}

	bistream->bytes = 0;
	bistream->name  = name;
	return true;
}

void
bistream_assign(BIStreamT *to, BIStreamT *from)
{
	to->file  = from->file;
	to->bytes = from->bytes;
	to->name  = from->name;
}

bool
bistream_is_open(BIStreamT *bistream)
{
	return bistream->name != NULL;
}

size_t
bistream_read_chars(BIStreamT *bistream, size_t length, char *chars)
{
	size_t bytes_read = fread(chars, sizeof(char),
		length, bistream->file);

	if ((bytes_read == 0) && (ferror(bistream->file))) {
		char *name = cstring_duplicate(bistream->name);

		THROW_VALUE(XX_bistream_read_error, name);
		UNREACHED;
	}

	bistream->bytes += bytes_read;
	return bytes_read;
}

size_t
bistream_read_bytes(BIStreamT *bistream, size_t length, ByteT *bytes)
{
    size_t bytes_read = fread(bytes, sizeof(ByteT),
					   length, bistream->file);

    if ((bytes_read == 0) && (ferror(bistream->file))) {
		char * name = cstring_duplicate(bistream->name);

		THROW_VALUE(XX_bistream_read_error, name);
		UNREACHED;
    }
    bistream->bytes += bytes_read;
    return bytes_read;
}

bool
bistream_read_byte(BIStreamT *bistream, ByteT *byte_ref)
{
	int byte = fgetc(bistream->file);

	if (byte == EOF) {
		if (ferror(bistream->file)) {
			char *name = cstring_duplicate(bistream->name);

			THROW_VALUE(XX_bistream_read_error, name);
			UNREACHED;
		} else if (feof(bistream->file)) {
			return false;
		}
	}

	bistream->bytes++;
	*byte_ref = (ByteT) byte;
	return true;
}

size_t
bistream_byte(BIStreamT *bistream)
{
	return bistream->bytes;
}

const char *
bistream_name(BIStreamT *bistream)
{
	return bistream->name;
}

void
bistream_rewind(BIStreamT *bistream)
{
	rewind(bistream->file);
}

void
bistream_close(BIStreamT *bistream)
{
	IGNORE fclose(bistream->file);
	bistream_init(bistream);
}
