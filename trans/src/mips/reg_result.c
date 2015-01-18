/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>

#include <construct/shape.h>
#include <construct/installtypes.h>
#include <construct/reg_result.h>

bool
reg_result(shape sha)
{
  return ( is_floating(name(sha)) ||
    (shape_size(sha) <= 32 && name (sha) != cpdhd && name(sha) != nofhd));

}
