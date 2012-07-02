
/*-
 * star_common.c
 *  common functions for star_encode.c, star_decode.c
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

#include "star_types.h"
#include "star_common.h"

#ifndef _STAR_COMMON_C_
#define _STAR_COMMON_C_

static star_u32_t _star_crc(star_u32_t input)
{
	star_u32_t crcsr;
	star_int_t bit;
	star_u32_t cur;
	star_int_t inv;
	
	crcsr = 0x2a;
	for(bit = 6; bit<(21+6); bit++)
	{
		cur = (input >> (32-bit)) & 0x01;
		inv = cur ^ (0x01 & (crcsr >> 5));
		crcsr <<= 1;
		if(inv)
			crcsr ^= 0x2f;
	}
		
	return crcsr & 0x3f;
}

#endif
