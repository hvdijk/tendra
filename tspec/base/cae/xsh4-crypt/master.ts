# Copyright 2014, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

# This is the "Encryption" (CRYPT) Feature Group
# of XSH Issue 4, "System Interfaces and Headers",
# which constitutes the C headers part of XPG4.
# Specified by X/Open as part of CAE. Document number C202,
# ISBN: 1-872630-47-2 published July 1992.

$UNIQUE  = 1;
$VERSION = "2.6";
+BASE_API;

$INFO = "X/Open CAE XSH Issue 4 - Encryption";

+IMPLEMENT "cae/xsh4-crypt", "stdlib.h.ts";
+IMPLEMENT "cae/xsh4-crypt", "unistd.h.ts";

