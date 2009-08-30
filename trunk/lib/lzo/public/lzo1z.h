/*
 * $QNXtpLicenseC:
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




/* lzo1z.h -- public interface of the LZO1Z compression algorithm

   This file is part of the LZO real-time data compression library.

   Copyright (C) 1999 Markus Franz Xaver Johannes Oberhumer
   Copyright (C) 1998 Markus Franz Xaver Johannes Oberhumer
   If not, write to the Free Software Foundation, Inc.,
   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

   Markus F.X.J. Oberhumer
   <markus.oberhumer@jk.uni-linz.ac.at>
   http://wildsau.idv.uni-linz.ac.at/mfx/lzo.html
 */


#ifndef __LZO1Z_H
#define __LZO1Z_H

#ifndef __LZOCONF_H
#include <lzoconf.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


/***********************************************************************
//
************************************************************************/

/* Memory required for the wrkmem parameter.
 * When the required size is 0, you can also pass a NULL pointer.
 */

#define LZO1Z_MEM_COMPRESS      ((lzo_uint32) (16384L * lzo_sizeof_dict_t))
#define LZO1Z_MEM_DECOMPRESS    (0)
#define LZO1Z_MEM_OPTIMIZE      (0)


/* decompression */
LZO_EXTERN(int)
lzo1z_decompress        ( const lzo_byte *src, lzo_uint  src_len,
                                lzo_byte *dst, lzo_uint *dst_len,
                                lzo_voidp wrkmem /* NOT USED */ );

/* safe decompression with overrun testing */
LZO_EXTERN(int)
lzo1z_decompress_safe   ( const lzo_byte *src, lzo_uint  src_len,
                                lzo_byte *dst, lzo_uint *dst_len,
                                lzo_voidp wrkmem /* NOT USED */ );


/***********************************************************************
//
************************************************************************/

#if 0
/* not yet implemented */
LZO_EXTERN(int)
lzo1z_1_compress        ( const lzo_byte *src, lzo_uint  src_len,
                                lzo_byte *dst, lzo_uint *dst_len,
                                lzo_voidp wrkmem );
#endif


/***********************************************************************
// better compression ratio at the cost of more memory and time
************************************************************************/

#define LZO1Z_999_MEM_COMPRESS  ((lzo_uint32) (14 * 16384L * sizeof(short)))

#if !defined(LZO_999_UNSUPPORTED)
LZO_EXTERN(int)
lzo1z_999_compress      ( const lzo_byte *src, lzo_uint  src_len,
                                lzo_byte *dst, lzo_uint *dst_len,
                                lzo_voidp wrkmem );
#endif


/***********************************************************************
//
************************************************************************/

#if !defined(LZO_999_UNSUPPORTED)
LZO_EXTERN(int)
lzo1z_999_compress_dict     ( const lzo_byte *in , lzo_uint  in_len,
                                    lzo_byte *out, lzo_uint *out_len,
                                    lzo_voidp wrkmem,
                              const lzo_byte *dict, lzo_uint dict_len );

LZO_EXTERN(int)
lzo1z_999_compress_level    ( const lzo_byte *in , lzo_uint  in_len,
                                    lzo_byte *out, lzo_uint *out_len,
                                    lzo_voidp wrkmem,
                              const lzo_byte *dict, lzo_uint dict_len,
                                    lzo_progress_callback_t cb,
                                    int compression_level );
#endif

LZO_EXTERN(int)
lzo1z_decompress_dict_safe ( const lzo_byte *in,  lzo_uint  in_len,
                                   lzo_byte *out, lzo_uint *out_len,
                                   lzo_voidp wrkmem /* NOT USED */,
                             const lzo_byte *dict, lzo_uint dict_len );


/***********************************************************************
// optimize a compressed data block
************************************************************************/

#if 0
/* not yet implemented */
LZO_EXTERN(int)
lzo1z_optimize          (       lzo_byte *in , lzo_uint  in_len,
                                lzo_byte *out, lzo_uint *out_len,
                                lzo_voidp wrkmem );
#endif



#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* already included */

