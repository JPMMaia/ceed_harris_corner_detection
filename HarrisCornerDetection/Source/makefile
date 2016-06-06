CC=C:\Xilinx\SDSoC\2016.1\SDK\2016.1\gnu\aarch32\nt\gcc-arm-none-eabi\bin\arm-none-eabi-gcc.exe
CC=gcc
#CFLAGS=-Wall -O3 -mcpu=cortex-a9 -mfloat-abi=hard -mfpu=neon -std=c99 -ftree-vectorize -ftree-vectorizer-verbose=1 -I../../CEED_Harris_SW1_bsp/ps7_cortexa9_0/include
CFLAGS=-Wall -O3 -std=c99 -ftree-vectorize -ftree-vectorizer-verbose=1 -march=native

all:
	$(CC) $(CFLAGS) FileStream.c Harris.c MathUtils.c MatrixFloat.c Vector.c main.c

clean:
	rm *o program
