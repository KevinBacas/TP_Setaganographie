#include "hamming_code.h"

void tool_where_is_row(uint* r, const vector* synd, const hcode* C)
{
  for(*r=0; *r<C->H->nb_row; ++(*r))
    {
      if (vector_is_equal_tab(synd, C->H->data[*r]) == 0)
	{
	  return;
	}
    }
}


void HCode_create(hcode** C, const uint m)
{
  uint i = 1;
  vector  *row;

  vector_malloc(&row, m);

  if ((*C = malloc(sizeof(hcode))) == NULL)
    {
      vector_free(&row);
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Hamming code creation: allocation problem.", ERR_ALLOC);
    }

  (*C)->m = m;
  (*C)->n = (uint)pow(2, m) - 1;
  (*C)->k = (*C)->n - m;

  matrix_malloc(&((*C)->H), (*C)->n, m);
  
  for(; i<=(*C)->n; ++i)
    {
      vector_dec_to_bin(row, i);
      matrix_set_row((*C)->H, row->v, m, i-1);
    }

  vector_free(&row);
}


void HCode_free(hcode** C)
{
  matrix_free(&((*C)->H));
  free(*C);
  *C = NULL;
}


void HCode_fprint(FILE *out, const hcode *C)
{
  fprintf(out, "A binary [%d, %d, 3]-Hamming code with (m=%d) parity-check-matrix:\n", C->n, C->k, C->m);
  matrix_fprint(out, C->H);
}



void HCode_print(const hcode *C)
{
  HCode_fprint(stdout, C);
}


void HCode_syndrome(vector* synd, const vector* y, const hcode *C)
{
  matrix_vector_mult(synd, y, C->H);
}

void HCode_decode(vector* c, const vector* y, const hcode* C)
{
  uint position;
  vector *synd;

  vector_malloc(&synd, C->m);
  memcpy(c->v, y->v, C->n*sizeof(uint));

  HCode_syndrome(synd, y, C);
  if(vector_is_zero(synd) == 0)
    {
      vector_free(&synd);
      return;
    }

  tool_where_is_row(&position, synd, C);
  c->v[position] ^= 1;

  vector_free(&synd);
}


void HCode_get_coset_leader(vector *r, const vector *synd, const hcode *C)
{
  uint position;

  memset(r->v, 0, C->n * sizeof(uint));
  if(vector_is_zero(synd) == 0)
    {
      return;
    }

  tool_where_is_row(&position, synd, C);
  r->v[position] ^= 1;
}
