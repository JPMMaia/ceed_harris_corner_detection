#ifndef IO_H_
#define IO_H_

#include <stdio.h>
#include <stdlib.h>

int input_dsp (void *dest, int words, int data_type, FILE * input_fp);
void output_dsp (void * src, int words, int data_type, FILE * output_fp);

#endif
