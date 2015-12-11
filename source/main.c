#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "error.h"
#include "file.h"
#include "vector.h"
#include "matrix.h"
#include "hamming_code.h"
#include "PGM.h"
#include "stegano.h"


int main(void)
{
  
  char
    img_ori[]     = "images/lena.pgm",
    img_stegano[] = "images/lena_stegano.pgm",
    img_diff[]    = "images/lena_diff.pgm",
    txt_ori[]     = "images/test.txt",
    txt_ext[]     = "images/extraction.txt";
  hcode *C;

  pgm
    *ori,
    *stego,
    *diff;

  uint
    i, 
    j,
    w,
    h;

  FILE*
    diff_file;
 
  printf("Creating the Hamming code: ");
  HCode_create(&C, 8);

  printf("OK\n");


  printf("Embed '%s' into '%s' which produces '%s': ", txt_ori, img_ori, img_stegano);
  stegano_embed_file(img_stegano, txt_ori, img_ori, C);

  printf("OK\n");


  printf("Extract '%s' into '%s': ", img_stegano, txt_ext);
  stegano_extract_file(txt_ext, img_stegano, C);

  printf("OK\n");


  printf("Making the difference between %s and %s: ", img_ori, img_stegano);
  PGM_create(&ori, img_ori);
  PGM_create(&stego, img_stegano);
  file_open(&diff_file, img_diff, "w");
  PGM_diff(ori, stego, &diff);
  PGM_fprint(diff_file, diff);

  printf("OK\n");

  printf("Free the memory: ");
  HCode_free(&C);
  PGM_destroy(&ori);
  PGM_destroy(&stego);
  PGM_destroy(&diff);
  file_close(&diff_file);

  printf("OK\n");

  return(0);
}
