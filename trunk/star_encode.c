
/*-
 * star_encode.c
 *  implementation of a 1600 Hz carrier, 400 bps PSK encoder
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

#include <stdlib.h> // malloc

#include "star_common.c"
#include "star_encode.h"

#if defined(STAR_SAMPLE_FORMAT_U8)

static star_sample_t _sintable[] = {
      127, 130, 133, 136, 139, 142, 145, 148, 151, 154, 157, 160, 163, 166, 169, 172,
	  175, 178, 180, 183, 186, 189, 191, 194, 196, 199, 201, 204, 206, 209, 211, 213,
	  215, 218, 220, 222, 224, 226, 227, 229, 231, 233, 234, 236, 237, 239, 240, 241,
	  242, 244, 245, 246, 247, 247, 248, 249, 250, 250, 251, 251, 251, 252, 252, 252,
	  252, 252, 252, 252, 251, 251, 251, 250, 250, 249, 248, 247, 247, 246, 245, 244,
	  242, 241, 240, 239, 237, 236, 234, 233, 231, 229, 227, 226, 224, 222, 220, 218,
	  215, 213, 211, 209, 206, 204, 201, 199, 196, 194, 191, 189, 186, 183, 180, 178,
	  175, 172, 169, 166, 163, 160, 157, 154, 151, 148, 145, 142, 139, 136, 133, 130,
	  127, 124, 121, 118, 115, 112, 109, 106, 103, 100,  97,  94,  91,  88,  85,  82,
	  79,  76,  74,  71,  68,  65,  63,  60,  58,  55,  53,  50, 48,  45,  43,  41,
	  39,  36,  34,  32,  30,  28,  27,  25, 23,  21,  20,  18,  17,  15,  14,  13,
	  12,  10,   9,   8, 7,   7,   6,   5,   4,   4,   3,   3,   3,   2,   2,   2,
	  2,   2,   2,   2,   3,   3,   3,   4,   4,   5,   6,   7, 7,   8,   9,  10,
	  12,  13,  14,  15,  17,  18,  20,  21, 23,  25,  27,  28,  30,  32,  34,  36,
	  39,  41,  43,  45, 48,  50,  53,  55,  58,  60,  63,  65,  68,  71,  74,  76,
	  79,  82,  85,  88,  91,  94,  97, 100, 103, 106, 109, 112, 115, 118, 121, 124 };

#elif defined(STAR_SAMPLE_FORMAT_U16)

static star_sample_t _sintable[] = {
	32768, 33552, 34337, 35120, 35902, 36682, 37460, 38235,
	39007, 39775, 40538, 41297, 42051, 42799, 43542, 44277,
	45006, 45728, 46441, 47147, 47843, 48531, 49209, 49877,
	50535, 51182, 51819, 52443, 53056, 53657, 54245, 54820,
	55381, 55930, 56464, 56984, 57489, 57980, 58455, 58915,
	59359, 59787, 60199, 60594, 60972, 61334, 61678, 62005,
	62314, 62606, 62879, 63134, 63371, 63590, 63790, 63971,
	64134, 64278, 64402, 64508, 64595, 64662, 64710, 64739,
	64749, 64739, 64710, 64662, 64595, 64508, 64402, 64278,
	64134, 63971, 63790, 63590, 63371, 63134, 62879, 62606,
	62314, 62005, 61678, 61334, 60972, 60594, 60199, 59787,
	59359, 58915, 58455, 57980, 57489, 56984, 56464, 55930,
	55381, 54820, 54245, 53657, 53056, 52443, 51819, 51182,
	50535, 49877, 49209, 48531, 47843, 47147, 46441, 45728,
	45006, 44277, 43542, 42799, 42051, 41297, 40538, 39775,
	39007, 38235, 37460, 36682, 35902, 35120, 34337, 33552,
	32768, 31983, 31198, 30415, 29633, 28853, 28075, 27300,
	26528, 25760, 24997, 24238, 23484, 22736, 21993, 21258,
	20529, 19807, 19094, 18388, 17692, 17004, 16326, 15658,
	15000, 14353, 13716, 13092, 12479, 11878, 11290, 10715,
	10154,  9605,  9071,  8551,  8046,  7555,  7080,  6620,
 	6176,  5748,  5336,  4941,  4563,  4201,  3857,  3530,
 	3221,  2929,  2656,  2401,  2164,  1945,  1745,  1564,
 	1401,  1257,  1133,  1027,   940,   873,   825,   796,
  	787,   796,   825,   873,   940,  1027,  1133,  1257,
 	1401,  1564,  1745,  1945,  2164,  2401,  2656,  2929,
 	3221,  3530,  3857,  4201,  4563,  4941,  5336,  5748,
 	6176,  6620,  7080,  7555,  8046,  8551,  9071,  9605,
	10154, 10715, 11290, 11878, 12479, 13092, 13716, 14353,
	15000, 15658, 16326, 17004, 17692, 18388, 19094, 19807,
	20529, 21258, 21993, 22736, 23484, 24238, 24997, 25760,
	26528, 27300, 28075, 28853, 29633, 30415, 31198, 31983 };

#elif defined(STAR_SAMPLE_FORMAT_S16)

static star_sample_t _sintable[] = {
	     0,    784,   1569,   2352,   3134,   3914,   4692,   5467, 
	  6239,   7007,   7770,   8529,   9283,  10031,  10774,  11509, 
	 12238,  12960,  13673,  14379,  15075,  15763,  16441,  17109, 
	 17767,  18414,  19051,  19675,  20288,  20889,  21477,  22052, 
	 22613,  23162,  23696,  24216,  24721,  25212,  25687,  26147, 
	 26591,  27019,  27431,  27826,  28204,  28566,  28910,  29237, 
	 29546,  29838,  30111,  30366,  30603,  30822,  31022,  31203, 
	 31366,  31510,  31634,  31740,  31827,  31894,  31942,  31971, 
	 31981,  31971,  31942,  31894,  31827,  31740,  31634,  31510, 
	 31366,  31203,  31022,  30822,  30603,  30366,  30111,  29838, 
	 29546,  29237,  28910,  28566,  28204,  27826,  27431,  27019, 
	 26591,  26147,  25687,  25212,  24721,  24216,  23696,  23162, 
	 22613,  22052,  21477,  20889,  20288,  19675,  19051,  18414, 
	 17767,  17109,  16441,  15763,  15075,  14379,  13673,  12960, 
	 12238,  11509,  10774,  10031,   9283,   8529,   7770,   7007,
	  6239,   5467,   4692,   3914,   3134,   2352,   1569,    784,
	     0,   -784,  -1569,  -2352,  -3134,  -3914,  -4692,  -5467,
	 -6239,  -7007,  -7770,  -8529,  -9283, -10031, -10774, -11509,
	-12238, -12960, -13673, -14379, -15075, -15763, -16441, -17109,
	-17767, -18414, -19051, -19675, -20288, -20889, -21477, -22052,
	-22613, -23162, -23696, -24216, -24721, -25212, -25687, -26147,
	-26591, -27019, -27431, -27826, -28204, -28566, -28910, -29237,
	-29546, -29838, -30111, -30366, -30603, -30822, -31022, -31203,
	-31366, -31510, -31634, -31740, -31827, -31894, -31942, -31971,
	-31981, -31971, -31942, -31894, -31827, -31740, -31634, -31510,
	-31366, -31203, -31022, -30822, -30603, -30366, -30111, -29838,
	-29546, -29237, -28910, -28566, -28204, -27826, -27431, -27019,
	-26591, -26147, -25687, -25212, -24721, -24216, -23696, -23162,
	-22613, -22052, -21477, -20889, -20288, -19675, -19051, -18414,
	-17767, -17109, -16441, -15763, -15075, -14379, -13673, -12960,
	-12238, -11509, -10774, -10031,  -9283,  -8529,  -7770,  -7007,
	 -6239,  -5467,  -4692,  -3914,  -3134,  -2352,  -1569,   -784 };

#elif defined(STAR_SAMPLE_FORMAT_FLOAT)

static star_sample_t _sintable[] = {
	 0.000000,  0.024541,  0.049068,  0.073565,  0.098017,  0.122411,  0.146730,  0.170962,
	 0.195090,  0.219101,  0.242980,  0.266713,  0.290285,  0.313682,  0.336890,  0.359895,
	 0.382683,  0.405241,  0.427555,  0.449611,  0.471397,  0.492898,  0.514103,  0.534998,
	 0.555570,  0.575808,  0.595699,  0.615232,  0.634393,  0.653173,  0.671559,  0.689541,
	 0.707107,  0.724247,  0.740951,  0.757209,  0.773010,  0.788346,  0.803208,  0.817585,
	 0.831470,  0.844854,  0.857729,  0.870087,  0.881921,  0.893224,  0.903989,  0.914210,
	 0.923880,  0.932993,  0.941544,  0.949528,  0.956940,  0.963776,  0.970031,  0.975702,
	 0.980785,  0.985278,  0.989177,  0.992480,  0.995185,  0.997290,  0.998795,  0.999699,
	 1.000000,  0.999699,  0.998795,  0.997290,  0.995185,  0.992480,  0.989177,  0.985278,
	 0.980785,  0.975702,  0.970031,  0.963776,  0.956940,  0.949528,  0.941544,  0.932993,
	 0.923880,  0.914210,  0.903989,  0.893224,  0.881921,  0.870087,  0.857729,  0.844854,
	 0.831470,  0.817585,  0.803208,  0.788346,  0.773010,  0.757209,  0.740951,  0.724247,
	 0.707107,  0.689541,  0.671559,  0.653173,  0.634393,  0.615232,  0.595699,  0.575808,
	 0.555570,  0.534998,  0.514103,  0.492898,  0.471397,  0.449611,  0.427555,  0.405241,
	 0.382683,  0.359895,  0.336890,  0.313682,  0.290285,  0.266713,  0.242980,  0.219101,
	 0.195090,  0.170962,  0.146730,  0.122411,  0.098017,  0.073565,  0.049068,  0.024541,
	 0.000000, -0.024541, -0.049068, -0.073565, -0.098017, -0.122411, -0.146730, -0.170962,
	-0.195090, -0.219101, -0.242980, -0.266713, -0.290285, -0.313682, -0.336890, -0.359895,
	-0.382683, -0.405241, -0.427555, -0.449611, -0.471397, -0.492898, -0.514103, -0.534998,
	-0.555570, -0.575808, -0.595699, -0.615232, -0.634393, -0.653173, -0.671559, -0.689541,
	-0.707107, -0.724247, -0.740951, -0.757209, -0.773010, -0.788346, -0.803208, -0.817585,
	-0.831470, -0.844854, -0.857729, -0.870087, -0.881921, -0.893224, -0.903989, -0.914210,
	-0.923880, -0.932993, -0.941544, -0.949528, -0.956940, -0.963776, -0.970031, -0.975702,
	-0.980785, -0.985278, -0.989177, -0.992480, -0.995185, -0.997290, -0.998795, -0.999699,
	-1.000000, -0.999699, -0.998795, -0.997290, -0.995185, -0.992480, -0.989177, -0.985278,
	-0.980785, -0.975702, -0.970031, -0.963776, -0.956940, -0.949528, -0.941544, -0.932993,
	-0.923880, -0.914210, -0.903989, -0.893224, -0.881921, -0.870087, -0.857729, -0.844854,
	-0.831470, -0.817585, -0.803208, -0.788346, -0.773010, -0.757209, -0.740951, -0.724247,
	-0.707107, -0.689541, -0.671559, -0.653173, -0.634393, -0.615232, -0.595699, -0.575808,
	-0.555570, -0.534998, -0.514103, -0.492898, -0.471397, -0.449611, -0.427555, -0.405241,
	-0.382683, -0.359895, -0.336890, -0.313682, -0.290285, -0.266713, -0.242980, -0.219101,
	-0.195090, -0.170962, -0.146730, -0.122411, -0.098017, -0.073565, -0.049068, -0.024541 };
#else
#error "no known sample format defined"
#endif


static void _mod_load(star_encoder_t *enc, star_u32_t bits, star_int_t bitcount)
{
	enc->encBits = bits;
	enc->bitcount = bitcount;
	enc->cycleCount = 4;
}

static void _mod(star_encoder_t *enc)
{
	star_int_t thisbit;

	if(enc->cycleCount)
		return;

	enc->cycleCount = 4;
	enc->bitcount--;

	thisbit = (enc->encBits >> enc->bitcount) & 0x01;

	if(thisbit != enc->lastbit)
	{
		enc->lastbit = thisbit;
		enc->tphase = !(enc->tphase);
	}
}

static void _start(star_encoder_t *enc)
{
	enc->theta = 0.0;
	_mod_load(enc, 0x00000000, PREAMBLE_ZERO_BITS);
	enc->state = 1;
	enc->tphase = 0;
	enc->lastbit = 0;
}

static star_sample_t _next_sample(star_encoder_t *enc)
{
	star_sample_t value;
	star_int_t ofs;

	if(enc->theta > TWOPI)
	{
		enc->theta -= TWOPI;
		enc->cycleCount--;
	}

	switch(enc->state)
	{
	case 0:
		return 0.0;
	case 1:
		_mod(enc);
		if(!enc->bitcount)
		{
			enc->state = 2;
			_mod_load(enc, 0x55555555, PREAMBLE_SYNC_BITS);
		}
		break;
	case 2:
		_mod(enc);
		if(!enc->bitcount)
		{
			enc->state = 3;
			_mod_load(enc, enc->bits0, 32);
		}
		break;
	case 3:
		_mod(enc);
		if(!enc->bitcount)
		{
			enc->state = 4;
			_mod_load(enc, enc->bits1, 32);
		}
		break;
	case 4:
		_mod(enc);
		if(!enc->bitcount)
		{
			enc->state = 5;
			_mod_load(enc, enc->bits2 >> 16, 16);
		}
		break;
	case 5:
		_mod(enc);
		if(!enc->bitcount)
		{
			enc->state = 6;
			_mod_load(enc, 0x00000000, POSTAMBLE_ZERO_BITS);
		}
	case 6:
		_mod(enc);
		if(!enc->bitcount)
		{
			enc->state = 0;
		}
		break;
	}

	ofs = (star_int_t)(enc->theta * (256.0 / TWOPI));
	if(enc->tphase)
		ofs += 128;
	ofs %= 256;
	value = _sintable[ofs];
	enc->theta += (TWOPI * 1600.0) / enc->sampleRate;

	return value; 
}

// public API

star_encoder_t *star_encoder_new(int sampleRate)
{
	star_encoder_t *enc;

	enc = malloc(sizeof(star_encoder_t));
	if(enc)
	{
		enc->sampleRate = (star_float_t)sampleRate;
		enc->state = 0;
		enc->theta = 0.0;
		enc->cycleCount = 0;
	}
	return enc;
}

int star_encoder_set(star_encoder_t *encoder, star_format format, int unitID, int tag, int status, int message)
{
	star_u32_t crc;

	if(!encoder)
		return -1;

	if(unitID < 0)
		return -1;

	switch(format)
	{
	case star_format_1:	// t1, t2, and s1 do not contribute to unit ID - original format, IDs to 2047
		if(unitID > 2047)
			return -1;
		break;

	case star_format_1_4095: // t1 = 2048, t2 used for mobile/portable, s1 ignored
		if(unitID > 4095)
			return -1;
		tag &= 0x01;
		if(unitID & 0x0800)
			tag |= 0x02;
		break;

	case star_format_1_16383:  // t1 = 8192, t2 = 4096, s1 = 2048 used to allow unit IDs to 16383 -- most typical
		if(unitID > 16383)
			return -1;
		tag = 0;
		status &= 0x07;

		if(unitID & 0x0800)
			status |= 0x08;
		if(unitID & 0x1000)
			tag |= 0x01;
		if(unitID & 0x2000)
			tag |= 0x02;
		break;

	case star_format_sys:	// t1,t2 used for system ID, s1 = 2048
		if(unitID > 4095)
			return -1;
		status &= 0x07;
		if(unitID & 0x0800)
			status |= 0x08;
		break;

	case star_format_2:  // t1 = 4096, t2 = mobile/portable, s1 = 2048
		if(unitID > 8191)
			return -1;	
		tag &= 0x01;
		status &= 0x07;

		if(unitID & 0x0800)
			status |= 0x08;

		if(unitID & 0x1000)
			tag |= 0x02;
		break;

	case star_format_3:  // t1 = 4096, t2 = 8192, s1 = 2048
		if(unitID > 16383)
			return -1;
		tag = 0;
		status &= 0x07;

		if(unitID & 0x0800)
			status |= 0x08;
		if(unitID & 0x1000)
			tag |= 0x02;
		if(unitID & 0x2000)
			tag |= 0x01;
		break;

	case star_format_4:  // t1 = 4096, t2 = 2048, s1 = 8192
		if(unitID > 16383)
			return -1;
		tag = 0;
		status &= 0x07;

		if(unitID & 0x0800)
			tag |= 0x01;
		if(unitID & 0x1000)
			tag |= 0x02;
		if(unitID & 0x2000)
			status |= 0x08;
		break;

	default:
		return -1;
	}

	encoder->bits0 = 0x70000000;
	encoder->bits0 |= (unitID & 0x07ff) << 16;
	encoder->bits0 |= (tag & 0x03) << 14;
	encoder->bits0 |= (status & 0x0f) << 10;
	encoder->bits0 |= (message & 0x0f) << 6;

	crc = _star_crc(encoder->bits0);
	encoder->bits0 |= crc;
	encoder->bits1 = encoder->bits0 ^ 0x1fff0000;
	encoder->bits2 = encoder->bits0 & 0xffff0000;
	_start(encoder);

	return 0;
}

int star_encoder_get_samples(star_encoder_t *encoder, star_sample_t *buffer, int bufferLength)
{
	star_int_t i;

	if(!encoder)
		return -1;


	for(i=0; encoder->state && i<bufferLength; i++)
		buffer[i] = _next_sample(encoder);

	return i;
}

