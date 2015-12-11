/**************************************************************************/
/**************************************************************************/
/* Name ........ : stegano.h                                              */
/* Role ........ : Mini library to embed a file into a PGM file with      */
/*                 Hamming code.                                          */
/*                                                                        */
/* Author ...... : Morgan Barbier <morgan.barbier@ensicaen.fr>            */
/* Version ..... : V1.0 2013-01-20                                        */
/* Licence ..... : CC                                                     */
/**************************************************************************/
/**************************************************************************/
#ifndef __STEGANO_H__
#define __STEGANO_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "vector.h"
#include "matrix.h"
#include "hamming_code.h"
#include "file.h"
#include "PGM.h"


/**************************************************************************/
/**************************************************************************/
/* Function which sets 'v' as the Least Significant Bits of 'img'.        */
/**************************************************************************/
/**************************************************************************/
void stegano_extract_LSB(vector *v, const pgm* img);

/**************************************************************************/
/**************************************************************************/
/* Function which modifies 'img' such that the LSB becomes 'v'.           */
/**************************************************************************/
/**************************************************************************/
void stegano_insert_LSB(pgm* img, const vector* v);

/**************************************************************************/
/**************************************************************************/
/* Function which set 'x' as the stego vector of cover vector 'y' and     */
/* message 'm' with the help of Hamming code 'C'.                         */
/**************************************************************************/
/**************************************************************************/
void stegano_embed_part(vector* x, const vector* y, const vector* m, const hcode* C);

/**************************************************************************/
/**************************************************************************/
/* Function which sets 'm' as the embedded message of the stego vector    */
/* 'y' with the help of Hamming code 'C'.                                 */
/**************************************************************************/
/**************************************************************************/
void stegano_extract_part(vector* m, const vector* y, const hcode* C);

/**************************************************************************/
/**************************************************************************/
/* Function which sets 'x' as all stego vectors of cover vectors 'y' and  */
/* messages 'm' with the help of Hamming code 'C'.                        */
/**************************************************************************/
/**************************************************************************/
void stegano_embed(vector* x, const vector* y, const vector* m, const hcode* C);

/**************************************************************************/
/**************************************************************************/
/* Function with sets 'm' as all embedded messages of the stego vectors   */
/* 'x' with the help of Hamming code C.                                   */
/**************************************************************************/
/**************************************************************************/
void stegano_extract(vector* m, const vector* x, const hcode* C);

/**************************************************************************/
/**************************************************************************/
/* Function which sets 'pgm' as the stego image of all messages 'm' with  */
/* the help of 'C'.                                                       */
/**************************************************************************/
/**************************************************************************/
void stegano_embed_into_PGM(pgm* img, const vector* m, const hcode* C);

/**************************************************************************/
/**************************************************************************/
/* Function which sets 'm' as the embedded messages of 'img' with the     */
/* help of Hamming code 'C'.                                              */
/**************************************************************************/
/**************************************************************************/
void stegano_extract_from_PGM(vector* m, const pgm* img, const hcode* C);

/**************************************************************************/
/**************************************************************************/
/* Function which embeds the file called 'message' in the pgm file called */
/* 'file_in' into pgm file called 'file_out' with the help of Hamming     */
/* code 'C'.                                                              */
/**************************************************************************/
/**************************************************************************/
void stegano_embed_file(char* file_out, const char* message, const char* file_in, const hcode* C);

/**************************************************************************/
/**************************************************************************/
/* Function which prints into 'file_out' the embedded messages into       */
/* 'file_in' with the help of Hamming code 'C'.                           */
/**************************************************************************/
/**************************************************************************/
void stegano_extract_file(char* file_out, const char* file_in, const hcode* C);

uint* stegano_gen_permut(uint size);
void stegano_permut_free(uint** v);
void stegano_permut_vector(vector *vec, uint* permut_tab);
void stegano_inv_permut_vector(vector *vec, uint* permut_tab);

#endif /*  __STEGANO_H__ */
