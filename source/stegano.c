#include "stegano.h"
#include "file.h"

void stegano_extract_LSB(vector *v, const pgm* img)
{
  uint
    width, 
    height,
    size,
    i = 0,
    j,
    k = 0;

  PGM_get_width(&width, img);
  PGM_get_height(&height, img);
  size = width*height;
  if(v->size < size)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Vector size not large enought for LSB extraction.", ERR_MATH);
    }
     
  for(; i<height; ++i)
    {
      for(j=0; j<width; ++j, ++k)
	{
	  vector_set_element(v, img->img->data[i][j] & 1, k);
	}
    }
}


void stegano_insert_LSB(pgm* img, const vector* v)
{
  uint
    width, 
    height,
    size,
    i = 0,
    j,
    k = 0,
    elt;

  PGM_get_width(&width, img);
  PGM_get_height(&height, img);
  size = width*height;
  if(v->size < size)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Vector size larger than image for LSB insertion.", ERR_MATH);
    }
     
  for(; i<height; ++i)
    {
      for(j=0; j<width; ++j, ++k)
	{
	  vector_get_element(&elt, v, k);
	  if((((img->img->data[i][j]) & 1) == 1 )
	     &&
	     (elt == 0))
	    {
	      img->img->data[i][j]--;
	    }
	  else if((((img->img->data[i][j]) & 1) == 0)
		  &&
		  (elt == 1))
	    {
	      img->img->data[i][j]++;	      
	    }
	}
    }
}


void stegano_embed_part(vector* x, const vector* y, const vector* m, const hcode* C)
{
  vector 
    *yp,
    *v,
    *c;

  if(x->size != C->n)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Stego vector has not the good size.", ERR_MATH);
    }
  if(y->size != C->n)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Cover vector has not the good size.", ERR_MATH);
    }
  if(m->size != C->m)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Message vector has not the good size.", ERR_MATH);
    }


  vector_malloc(&yp, C->n);
  vector_malloc(&v, C->n);
  vector_malloc(&c, C->n);

  HCode_get_coset_leader(yp, m, C);
  vector_xor(v, yp, y);
  HCode_decode(c, v, C);
  vector_xor(x, c, yp);

  vector_free(&yp);
  vector_free(&v);
  vector_free(&c);
}


void stegano_extract_part(vector* m, const vector* y, const hcode* C)
{
  HCode_syndrome(m, y, C);
}



void stegano_embed(vector* x, const vector* y, const vector* m, const hcode* C)
{
  vector 
    **y_tab,
    **m_tab,
    *temp;

  uint
    i,
    size_ytab = y->size / C->n,
    size_mtab = m->size / C->m;


  if(x->size != y->size)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "The stego vector has a different size of cover.", ERR_MATH);
    }
  if(size_mtab > size_ytab)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Not enough data to embed message.", ERR_MATH);
    }
  if((y_tab = malloc(size_ytab * sizeof(vector*))) == NULL)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Impossible to allocate the block cover.", ERR_ALLOC);
    }
  if((m_tab = malloc(size_mtab * sizeof(vector*))) == NULL)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Impossible to allocate the block message.", ERR_ALLOC);
    }

  
  vector_malloc(&temp, C->n);

  for(i=0; i<size_ytab; i++)
    {
      vector_malloc(&(y_tab[i]), C->n);
    }  
  for(i=0; i<size_mtab; i++)
    {
      vector_malloc(&(m_tab[i]), C->m);
    }
  

  vector_subvectors(y_tab, y, C->n);

  vector_subvectors(m_tab, m, C->m);

  for(i=0; i<size_mtab; i++)
    {
      stegano_embed_part(temp, y_tab[i], m_tab[i], C);
      memcpy(&(x->v[i*C->n]), temp->v, C->n*sizeof(uint));
    }  


  for(i=0; i<size_mtab; i++)
    {
      vector_free(&(m_tab[i]));
    }  
  for(i=0; i<size_ytab; i++)
    {
      vector_free(&(y_tab[i]));
    }
  vector_free(&temp);
  free(y_tab);
  free(m_tab);
}



void stegano_extract(vector* m, const vector* x, const hcode* C)
{
  uint 
    i,
    nb_block = x->size / C->n;

  vector
    **x_tab,
    *temp;

  if((m->size % C->m) != 0)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "The message vector has not the good size.", ERR_MATH);
    }
  if(nb_block > (m->size / C->m))
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "The message vector cannot cointains the whole message.", ERR_MATH);
    }
  if((x_tab = malloc(nb_block*sizeof(vector*))) == NULL)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Impossible to allocate the temporary memory.", ERR_ALLOC);      
    }
  
  for(i=0; i<nb_block; ++i)
    {
      vector_malloc(&(x_tab[i]), C->n);
    }

  vector_subvectors(x_tab, x, C->n);
  vector_malloc(&temp, C->m);

  for(i=0; i<nb_block; ++i)
    {
      stegano_extract_part(temp, x_tab[i], C);
      memcpy(&(m->v[i*(temp->size)]), temp->v, sizeof(uint)*(temp->size));
    }

  vector_free(&temp);
  for(i=0; i<nb_block; ++i)
    {
      vector_free(&(x_tab[i]));
    }
  free(x_tab);
}


void stegano_embed_into_PGM(pgm* img, const vector* m, const hcode* C)
{
  uint
    width = 0,
    height = 0,
    size = 0;

  vector
    *LSB = NULL,
    *stego = NULL;

  PGM_get_width(&width, img);
  PGM_get_height(&height, img);
  size = height*width;

  vector_malloc(&LSB, size);
  vector_calloc(&stego, size);


  stegano_extract_LSB(LSB, img);
  memcpy(stego->v, LSB->v, size*sizeof(uint));
  stegano_embed(stego, LSB, m, C);

  stegano_insert_LSB(img, stego);

  vector_free(&LSB);
  vector_free(&stego);
}


void stegano_extract_from_PGM(vector* m, const pgm* img, const hcode* C)
{
  uint
    width,
    height,
    size;

  vector
    *LSB;

  PGM_get_width(&width, img);
  PGM_get_height(&height, img);
  size = height*width;
  
  if(size > m->size)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Message vector not enough large to contain.", ERR_MATH);
    }

  vector_malloc(&LSB, m->size);

  stegano_extract_LSB(LSB, img);

  stegano_extract(m, LSB, C);

  vector_free(&LSB);
}


void stegano_embed_file(char* file_out, const char* message, const char* file_in, const hcode* C)
{
  FILE
    *F_mess = NULL,
    *F_FO   = NULL;
  
  pgm* img = NULL;

  unsigned long int size = 0;
  
  uint i = 0;


  vector 
    *temp = NULL,
    *m = NULL;
  
  char c = 0;

  file_open(&F_mess, message, "r");
  PGM_create(&img, file_in);
  file_open(&F_FO, file_out, "w");

  size = get_size(F_mess);
  vector_malloc(&m, 8*sizeof(char)*(size+1));
  vector_malloc(&temp, 8*sizeof(char));

  c = fgetc(F_mess);
  while(c != EOF)
    {
      vector_dec_to_bin(temp, c);
      memcpy(&(m->v[(temp->size)*i]), temp->v, sizeof(uint)*temp->size);
      c = fgetc(F_mess);
      ++i;
    }
  vector_dec_to_bin(temp, 0);
  memcpy(&(m->v[(temp->size)*i]), temp->v, sizeof(uint)*temp->size);

  stegano_embed_into_PGM(img, m, C);

  PGM_fprint(F_FO, img);


  vector_free(&temp);
  vector_free(&m);
  file_close(&F_mess);
  PGM_destroy(&img);
  file_close(&F_FO);  
}


void stegano_extract_file(char* file_out, const char* file_in, const hcode* C)
{
  FILE *F_out;
  
  pgm* img;

  vector
    *m,
    *temp;

  uint
    width,
    height,
    size,
    i = 1;

  uint c = 1;


  file_open(&F_out, file_out, "w");
  PGM_create(&img, file_in);

  PGM_get_width(&width, img);
  PGM_get_height(&height, img);
  size = height*width;

  vector_malloc(&m, size);
  vector_malloc(&temp, 8*sizeof(char));
  
  stegano_extract_from_PGM(m, img, C);

  vector_subvector(temp, m, 0);
  vector_binary_to_dec(&c,temp);
  while(c != 0)
    {
      fputc(c, F_out);
      vector_subvector(temp, m, i*temp->size);
      vector_binary_to_dec(&c,temp);
      ++i;
    }

  vector_free(&m);
  vector_free(&temp);
  PGM_destroy(&img);
  file_close(&F_out);
}
