/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LOCAL_CPU_H
#define LOCAL_CPU_H

enum cpu {
	CPU_COMMON,
	CPU_POWERPC,
	CPU_RS6000
};

extern enum cpu cpu;

#endif

