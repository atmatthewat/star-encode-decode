/*-
 * star_encode.h
 *  header for star_encode.c
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

#ifndef __STAR_ENCODE_H__
#define __STAR_ENCODE_H__

#define PREAMBLE_ZERO_BITS 4
#define PREAMBLE_SYNC_BITS 16
#define POSTAMBLE_ZERO_BITS 16



typedef struct {
	star_float_t sampleRate;
	star_u32_t bits0;
	star_u32_t bits1;
	star_u32_t bits2;
	star_int_t state;
	star_float_t theta;
	star_int_t cycleCount;
	star_u32_t encBits;
	star_int_t bitcount;
	star_int_t tphase;
	star_int_t lastbit;
} star_encoder_t;

star_encoder_t *star_encoder_new(int sampleRate);

int star_encoder_set(star_encoder_t *encoder, star_format format, int unitID, int tag, int status, int message);

int star_encoder_get_samples(star_encoder_t *encoder, star_sample_t *buffer, int bufferLength);

#endif
