/*-
 * star_test.c
 *  functional test for star_encode.c, star_decode.c
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

#include <stdio.h>
#include <stdlib.h>

#include "star_types.h"
#include "star_common.h"
#include "star_decode.h"
#include "star_encode.h"

#define SAMPLERATE 16000.0

int main(int argc, char **argv)
{
	star_encoder_t *encoder;
	star_decoder_t *decoder;
	star_sample_t buffer[1024];

	encoder = star_encoder_new(SAMPLERATE);
	if(!encoder)
	{
		fprintf(stderr, "failed to create encoder\n");
	}

	decoder = star_decoder_new(SAMPLERATE);
	if(!decoder)
	{
		fprintf(stderr,"failed to create decoder\n");
		return 0;
	}

	star_encoder_set(encoder, star_format_1_16383, 1234, 0, 0, 1);

	while(star_encoder_get_samples(encoder, buffer, sizeof(buffer)/sizeof(star_sample_t)) > 0)
	{
		if(star_decoder_process_samples(decoder, buffer, sizeof(buffer)/sizeof(star_sample_t)))
		{
			int unitID, tag, status, message;

			star_decoder_get(decoder, star_format_1_16383, &unitID, &tag, &status, &message);
			
			printf("Unit ID %d  -- Tag %x -- Status %x -- Message %x\n",unitID, tag, status, message);
		}
	}

	// test encoder max unit ID range, min unit ID range
	// test format to format match
	// test callback version of decode as well

	return 0;
}

