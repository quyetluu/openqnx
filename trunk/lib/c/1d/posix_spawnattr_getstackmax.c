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

#include <unistd.h>		// determines whether _POSIX_SPAWN is defined or not
#ifdef _POSIX_SPAWN

#include "posix_spawnattr.h"

/*
 * =============================================================================
 * 
 * 				The following are QNX posix_spawnattr_t extensions
 * 
 * =============================================================================
*/

/*******************************************************************************
 * get/setstackmax
 * 
 * Retrieve/specify the maximum stack size for a spawned process which uses the
 * 'posix_spawnattr_t' object pointed to by <attrp>
 * 
 * Note that this setting only takes effect if the POSIX_SPAWN_SETSTACKMAX flag
 * is set. A value of 0 or an unset POSIX_SPAWN_SETSTACKMAX flag indicates no
 * maximum.
 * The default value can be retrieved with a call to posix_spawnattr_getstackmax()
 * using an initialized 'posix_spawnattr_t' object.
 * 
 * Returns:
 * 		EOK on success
 * 		EINVAL if there are any parameter errors
 * 
*/
int posix_spawnattr_getstackmax(const posix_spawnattr_t *_Restrict attrp, uint32_t *_Restrict size_p)
{
	if (!valid_attrp(attrp) || (size_p == NULL)) {
		return EINVAL;
	} else {
		_posix_spawnattr_t *_attrp = GET_ATTRP(attrp);
		*size_p = (_attrp == NULL) ? _default_posix_spawnattr_t.stack.max : _attrp->stack.max;
		return EOK;
	}
}


#endif	/* _POSIX_SPAWN */

