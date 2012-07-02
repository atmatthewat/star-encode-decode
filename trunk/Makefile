
star_test:	star_test.c star_decode.o star_encode.o 
		cc -Wall -g -o star_test star_test.c star_decode.o star_encode.o
		./star_test


star_decode.o:	star_decode.c star_decode.h star_common.c star_common.h
		cc -Wall -c star_decode.c

star_encode.o:	star_encode.c star_encode.h star_common.c star_common.h
		cc -Wall -c star_encode.c

clean:
	rm -f star_decode.o star_encode.o star_test
	
