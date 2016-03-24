/*
   Corinna G. Lee
   6 Jun 94: Modified for GNU C version of DSP programs:
 	1. "float" data type converted into "double" data type
	    so that math library functions can be used
	2. add data_type=3 to read/write binary data
   13 Jun 94: Make file pointers static variables to allow multiple calls
	to same I/O routine.  Note: files are not explicitly closed.

   Mark G. Stoodley
   17 Apr 96: caused input_dsp to return an integer that is non-zero if data
		was read from the file
*/

#include "IO.h"

int input_dsp (dest, words, data_type, input_fp)
void *dest;
int  words;
int  data_type;
FILE *input_fp;
{
  int		i;
  double	*float_ptr;
  int		*int_ptr;
  unsigned	*unsigned_ptr;
  errno_t err = 0;
  errno_t err_s = 0;

  if (input_fp==NULL && (err = fopen_s(&input_fp,"input.dsp", "r")) != 0) {
    printf ("** Error: cannot open input.dsp.\n");
    exit(1);
  }

  if (words <= 0) {
    printf ("** Error: trying to read a negative or zero number of words.\n");
    exit (1);
  }

  switch (data_type) {
    case 0:
      float_ptr = (double *) dest;
      for (i = 0; i < words; i++)
        err_s = fscanf_s (input_fp, "%lf", &float_ptr[i],sizeof(&float_ptr[i]));
      break;
    case 1:
      int_ptr = (int *) dest;
      for (i = 0; i < words; i++)
        err_s = fscanf_s (input_fp, "%d", &int_ptr[i],sizeof(&int_ptr[i]));
      break;
    case 2:
      unsigned_ptr = (unsigned *) dest;
      for (i = 0; i < words; i++)
        err_s = fscanf_s (input_fp, "%u", &unsigned_ptr[i],sizeof(&unsigned_ptr[i]));
      break;
    case 3:
      err_s = fread( (char *) dest, 1, words, input_fp);
      break;
    default:
      printf ("** Error: trying to use an undefined data type. \n");
      exit(1);
      break;
  }

  return err_s;
}


void output_dsp (src, words, data_type, output_fp)
void *src;
int  words;
int  data_type;
FILE * output_fp;
{
  int i;
  double *float_ptr;
  int *int_ptr;
  unsigned *unsigned_ptr;
  errno_t err = 0;
  errno_t err_s = 0;

  if (output_fp==NULL && (err = fopen_s (&output_fp,"output.dsp", "w")) != 0) {
    printf ("** Error: cannot open output.dsp.\n");
    exit(1);
  }

  if (words <= 0) {
    printf ("** Error: trying to write a negative or zero number of words.\n");
    exit (1);
  }

  switch (data_type) {
    case 0:
      float_ptr = (double *) src;
      for (i = 0; i < words; i++)
        fprintf (output_fp, "%lf\n", float_ptr[i]);
      break;
    case 1:
      int_ptr = (int *) src;
      for (i = 0; i < words; i++)
        fprintf (output_fp, "%d\n", int_ptr[i]);
      break;
    case 2:
      unsigned_ptr = (unsigned *) src;
      for (i = 0; i < words; i++)
        fprintf (output_fp, "%u\n", unsigned_ptr[i]);
      break;
    case 3:
      fwrite( (char *) src, 1, words, output_fp);
      break;
    default:
      printf ("** Error: trying to use an undefined data type. \n");
      exit(1);
      break;
  }

}
