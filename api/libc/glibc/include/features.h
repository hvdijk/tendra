/* $Id$ */

#ifndef __HACKED_LIBC_FEATURES_H
#define __HACKED_LIBC_FEATURES_H

#if defined(_GLIBC2_14) || defined(_GLIBC2_15) || defined(_GLIBC2_17)
#pragma TenDRA begin
#pragma TenDRA unknown directive allow /* for #warning */
#endif

#include_next <features.h>

#if defined(_GLIBC2_14) || defined(_GLIBC2_15) || defined(_GLIBC2_17)
#pragma TenDRA end
#endif

#endif
