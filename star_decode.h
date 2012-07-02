
/*-
 * star_decode.h
 *  header for star_decode.c
 *
 * Author: Matthew Kaufman (matthew@eeph.com)
 *
 * Copyright (c) 2012  Matthew Kaufman  All rights reserved.
 * 
 *  This file is part of Matthew Kaufman's STAR Encoder/Decoder Library
 *
 *  The STAR Encoder/Decoder Library is free software; you can
 *  redistribute it and/or modify it under the terms of version 2 of
 *  the GNU General Public License as published by the Free Software
 *  Foundation.
 *
 *  If you cannot comply with the terms of this license, contact
 *  the author for alternative license arrangements or do not use
 *  or redistribute this software.
 *
 *  The STAR Encoder/Decoder Library is distributed in the hope
 *  that it will be useful, but WITHOUT ANY WARRANTY; without even the
 *  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *  PURPOSE.  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this software; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301
 *  USA.
 *
 *  or see http://www.gnu.org/copyleft/gpl.html
 *
-*/

#ifndef __STAR_DECODE_H__
#define __STAR_DECODE_H__

#include "star_types.h"

#define NDEC 4
#define THINCR (TWOPI / 8)

typedef struct {
	star_float_t sampleRate;
	star_u32_t phsr[NDEC];
	star_int_t phstate[NDEC];
	star_int_t lastbit[NDEC];
	star_int_t thisbit[NDEC];
	star_int_t rbit[NDEC];
	star_float_t theta[NDEC];
	star_float_t accum[NDEC];
	star_u32_t bitsr[NDEC];
	star_int_t bitstate[NDEC];
	star_u32_t bits0[NDEC];
	star_u32_t bits1[NDEC];
	star_u32_t bits2[NDEC];
	star_int_t bitcount[NDEC];
	star_u32_t lastBits0;
	star_int_t valid;
} star_decoder_t;

star_decoder_t * star_decoder_new(int sampleRate);

int star_decoder_process_samples(star_decoder_t *decoder, star_sample_t *samples, int sampleCount);  // 8 bit version

int star_decoder_get(star_decoder_t *decoder, star_format format, int *unitID, int *tag, int *status, int *message);

#endif
