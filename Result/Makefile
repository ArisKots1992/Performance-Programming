# I deleted util.c because we eliminate all the functions from there
# Exm No. B084151 
SRC= MD.c control.c
OBJ= $(SRC:.c=.o)
CC= gcc -Ofast -march=bdver1
#CC= pgcc -tp=bulldozer
#CFLAGS= -fprefetch-loop-arrays --param prefetch-latency=310
#CFLAGS=  -Mmovnt -fastsse -Msafeptr=all -Mfprelaxed
#CFLAGS= -pg -Mmovnt -fastsse -Msafeptr=all -Mfprelaxed
# tests : CFLAGS=  -w -Mmovnt -fastsse -Msafeptr=all -Mfprelaxed -Minstrument=functions -Munroll=m:16 -Mfpapprox -Knoieee -Mipa=fast,inline,noarg -Msmartalloc=huge:840 -tp bulldozer  -DSPEC_CPU_LINUX
# tests : CFLAGS= -Mmovnt -fastsse -Msafeptr=all -Mfprelaxed -Minstrument=functions -Munroll=m:16 -Mfpapprox -Knoieee

all: MD

MD: $(OBJ)
	$(CC) $(CFLAGS)  -o $@  $(OBJ) -lm


output.dat: MD input.data
	./MD


clean:
	rm -f MD $(OBJ)

$(OBJ) : coord.h Makefile
