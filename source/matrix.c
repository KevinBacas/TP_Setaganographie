#include "matrix.h"


void matrix_malloc(matrix** r, const uint nbr, const uint nbc)
{
  uint i = 0;

  if (NULL == (*r = malloc(sizeof(matrix))))
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Matrix allocation impossible.", ERR_ALLOC);
    }
  
  if (((*r)->data = malloc(nbr*sizeof(uint*))) == NULL)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Matrix allocation impossible.", ERR_ALLOC);
    }
  
  for(; i<nbr; ++i)
    {
      if (((*r)->data[i] = malloc(nbc*sizeof(uint))) == NULL)
	{
	  error_print(__FILE__, __LINE__, __FUNCTION__,
		      "Matrix allocation impossible.", ERR_ALLOC);
	}
    }

  (*r)->nb_row = nbr;
  (*r)->nb_col = nbc;
}



void matrix_calloc(matrix** r, const uint nbr, const uint nbc)
{
  uint i = 0;

  if (NULL == (*r = malloc(sizeof(matrix))))
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Matrix allocation impossible.", ERR_ALLOC);
    }
  
  if (((*r)->data = malloc(nbr*sizeof(uint*))) == NULL)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Matrix allocation impossible.", ERR_ALLOC);
    }
  
  for(; i<nbr; ++i)
    {
      if (((*r)->data[i] = calloc(nbc, sizeof(uint))) == NULL)
	{
	  error_print(__FILE__, __LINE__, __FUNCTION__,
		      "Matrix allocation impossible.", ERR_ALLOC);
	}
    }

  (*r)->nb_row = nbr;
  (*r)->nb_col = nbc;
}


void matrix_free(matrix** m)
{
  uint i = 0;

  for(; i<(*m)->nb_row; ++i)
    {
      free((*m)->data[i]);
    }
  free((*m)->data);
  free((*m));
  *m = NULL;
}

void matrix_fprint(FILE *out, const matrix* m)
{
  uint 
    i = 0,
    j;

  for(; i<m->nb_row; ++i)
    {
      fprintf(out, "|");
      for(j=0; j<m->nb_col-1; ++j)
	{
	  fprintf(out, "%d,\t",m->data[i][j]);
	}
      fprintf(out, "%d|\n",m->data[i][m->nb_col-1]);      
    }
}

void matrix_print(const matrix* m)
{
  matrix_fprint(stdout, m);
}


void matrix_mult(matrix *r, const matrix *m1, const matrix *m2)
{
  uint
    i = 0,
    j,
    k;

  if (m1->nb_col != m2->nb_row)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Matrix multiplication: the number of columns of m1 must to be equal to the number of rows of m2.", ERR_MATH);
    }
  if (r->nb_col != m2->nb_col)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Matrix multiplication: the number of columns of the result is incoherent.", ERR_MATH);
    }
  if (r->nb_row != m1->nb_row)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Matrix multiplication: the number of rows of the result is incoherent.", ERR_MATH);
    }

  for(; i<r->nb_row; ++i)
    {
      for(j=0; j<r->nb_col; ++j)
	{
	  r->data[i][j] = 0;
	  for(k=0; k<m1->nb_col; ++k)
	    {
	      r->data[i][j] ^= m1->data[i][k] & m2->data[k][j];
	    }
	}      
    }
}


void matrix_transpose(matrix *r, const matrix *m)
{
  uint
    i = 0,
    j;

  if ((r->nb_row != m->nb_col) && (m->nb_row != r->nb_col))
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Matrix transposition: size problem.", ERR_MATH);
    }

  for(; i<m->nb_row; ++i)
    {
      for(j=0; j<m->nb_col; ++j)
	{
	  r->data[j][i] = m->data[i][j];
	}
    }
}


void matrix_set_row(matrix *r, const uint* row, const uint size_r, const uint row_i)
{
  uint j = 0;

  if (size_r > r->nb_col)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Matrix set row : data shorter than needed.", ERR_MATH);
    }

  for(; j<r->nb_col; ++j)
    {
      r->data[row_i][j] = row[j];
    }
}


void matrix_vector_mult(vector* r, const vector* v, const matrix* m)
{
  uint
    i = 0,
    j;

  /*  printf("%d %d\n", r->size, m->nb_col);*/

  if(r->size != m->nb_col)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Vector resultat has not the appropriate size.", ERR_MATH);
    }
  if(v->size != m->nb_row)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Multiplication vector x matrix impossible by the size.", ERR_MATH);
    }

  for(; i<r->size; ++i)
    {
      r->v[i] = 0;
      for(j=0; j<v->size; ++j)
	{
	  r->v[i] ^= v->v[j] & m->data[j][i];
	}
    }
}
