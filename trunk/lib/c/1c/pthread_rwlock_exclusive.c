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




#include <errno.h>
#include <pthread.h> 
#include "cpucfg.h"

static void
_exclusive_cancel(void *data) {
	pthread_rwlock_t *l = data;

	// determine who (if anybody) we should wakeup
	if ((--l->__blockedwriters != 0) && (l->__active == 0)) {
		// only wakup a writer
		pthread_cond_signal(&l->__wcond);
	} else if (l->__blockedreaders != 0) {
		// only wakeup readers
		pthread_cond_broadcast(&l->__rcond);
	}

	pthread_mutex_unlock(&l->__lock);
}

static int
_pthread_timedrwlock_exclusive(pthread_rwlock_t* l, int preventblock, const struct timespec *t) {
	int status, id = LIBC_TLS()->__owner;

	if ((status = pthread_mutex_lock(&l->__lock)) == EOK) {

		if (l->__owner == id) {
			status = EDEADLK;
		} else if ((preventblock) && (l->__active != 0)) {
			status = EBUSY;
		} else {
	
			l->__blockedwriters++;
			pthread_cleanup_push(_exclusive_cancel, l);

			while (l->__active != 0) {
				if ((status = (t ?	pthread_cond_timedwait(&l->__wcond, &l->__lock, t) :
									pthread_cond_wait(&l->__wcond, &l->__lock))) != EOK) {
					break;
				}
			}

			pthread_cleanup_pop(0);
			l->__blockedwriters--;

			if (status == EOK) {
				l->__active = -1;
				l->__owner = id;
			}
		}

		pthread_mutex_unlock(&l->__lock);
	}

	return status;
}

/* Only for binary compatibility with 2.0 programs */
int
__pthread_rwlock_exclusive(pthread_rwlock_t *l, int preventblock) {
	return _pthread_timedrwlock_exclusive(l, preventblock, 0);
}

int
(pthread_rwlock_timedwrlock)(pthread_rwlock_t *l, const struct timespec *t) {
	return _pthread_timedrwlock_exclusive(l, 0, t);
}

int
(pthread_rwlock_wrlock)(pthread_rwlock_t *l) {
	return _pthread_timedrwlock_exclusive(l, 0, 0);
}

int
(pthread_rwlock_trywrlock)(pthread_rwlock_t *l) {
	return _pthread_timedrwlock_exclusive(l, 1, 0);
}

__SRCVERSION("pthread_rwlock_exclusive.c $Rev: 153052 $");
