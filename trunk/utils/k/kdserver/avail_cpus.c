/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to QNX 
 * Software Systems before you may reproduce, modify or distribute this software, 
 * or any work that includes all or part of this software.   Free development 
 * licenses are available for evaluation and non-commercial purposes.  For more 
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *  
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/ 
 * for other information.
 * $
 */




#include "kdserver.h"

// The avail_cpus.gh include file is automatically generated by the
// makefiles and contains a list of all available CPUS (identified
// by a source filename starting with "cpu_").

#undef CPU
#define CPU(c)	extern struct cpuinfo	cpu_##c;
#include "avail_cpus.gh"

#undef CPU
#define CPU(c)	&cpu_##c,

struct cpuinfo *available_cpus[] = {
#include "avail_cpus.gh"	
	NULL
};
