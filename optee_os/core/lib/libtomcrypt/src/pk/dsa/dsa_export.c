/*
 * Copyright (c) 2001-2007, Tom St Denis
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/* LibTomCrypt, modular cryptographic library -- Tom St Denis
 *
 * LibTomCrypt is a library that provides various cryptographic
 * algorithms in a highly modular and flexible manner.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tomstdenis@gmail.com, http://libtom.org
 */
#include "tomcrypt.h"

/**
   @file dsa_export.c
   DSA implementation, export key, Tom St Denis
*/

#ifdef LTC_MDSA

/**
  Export a DSA key to a binary packet
  @param out    [out] Where to store the packet
  @param outlen [in/out] The max size and resulting size of the packet
  @param type   The type of key to export (PK_PRIVATE or PK_PUBLIC)
  @param key    The key to export
  @return CRYPT_OK if successful
*/
int dsa_export(unsigned char *out, unsigned long *outlen, int type, dsa_key *key)
{
   unsigned char flags[1];

   LTC_ARGCHK(out    != NULL);
   LTC_ARGCHK(outlen != NULL);
   LTC_ARGCHK(key    != NULL);

   /* can we store the static header?  */
   if (type == PK_PRIVATE && key->type != PK_PRIVATE) {
      return CRYPT_PK_TYPE_MISMATCH;
   }

   if (type != PK_PUBLIC && type != PK_PRIVATE) {
      return CRYPT_INVALID_ARG;
   }

   flags[0] = (type != PK_PUBLIC) ? 1 : 0;

   if (type == PK_PRIVATE) {
      return der_encode_sequence_multi(out, outlen,
                                 LTC_ASN1_BIT_STRING,   1UL, flags,
                                 LTC_ASN1_INTEGER,      1UL, key->g,
                                 LTC_ASN1_INTEGER,      1UL, key->p,
                                 LTC_ASN1_INTEGER,      1UL, key->q,
                                 LTC_ASN1_INTEGER,      1UL, key->y,
                                 LTC_ASN1_INTEGER,      1UL, key->x,
                                 LTC_ASN1_EOL,          0UL, NULL);
   } else {
      return der_encode_sequence_multi(out, outlen,
                                 LTC_ASN1_BIT_STRING,   1UL, flags,
                                 LTC_ASN1_INTEGER,      1UL, key->g,
                                 LTC_ASN1_INTEGER,      1UL, key->p,
                                 LTC_ASN1_INTEGER,      1UL, key->q,
                                 LTC_ASN1_INTEGER,      1UL, key->y,
                                 LTC_ASN1_EOL,          0UL, NULL);
   }
}

#endif


/* $Source: /cvs/libtom/libtomcrypt/src/pk/dsa/dsa_export.c,v $ */
/* $Revision: 1.10 $ */
/* $Date: 2007/05/12 14:32:35 $ */
