# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


$FILENAME = "stdlib.h.ts" ;

+USE "c/c89", "stddef.h.ts", "size_t" ;

+IFNDEF __DONT_INLINE_ALLOCA
+FUNC void *alloca | "~alloca" ( size_t ) ;
+ELSE
+FUNC (extern) void *alloca.1 ( size_t ) ;
+ENDIF
