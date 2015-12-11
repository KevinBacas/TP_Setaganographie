#include "vector.h"



void vector_binary_to_dec(uint *r, const vector *v)
{
  uint i = 0;
  
  *r = 0;
  for(; i<v->size; ++i)
    {
      (*r) += (v->v[i] << i);
    }
}



void vector_dec_to_bin(vector *r, const int v)
{
  uint 
    i   = 0,
    tmp = v;

  for(; i<r->size; ++i)
    {
      r->v[i] = tmp % 2;
      tmp /= 2;
    }
  
  if(tmp != 0)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Vector is not large enought for the binary decomposition.", ERR_MATH);
    }
}


uint vector_is_equal_tab(const vector* v, const uint* tab)
{
  uint i = 0;
  
  for(; i<v->size; ++i)
    {
      if(v->v[i] != tab[i])
	{
	  return(1);
	}
    }

  return(0);
}


uint vector_are_equal(const vector* a, const vector* b)
{
  if(a->size != b->size)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Vector comparaison not the same size.", ERR_MATH);
    }

  return(vector_is_equal_tab(a, b->v));
}


uint vector_is_zero(const vector *v)
{
  uint i = 0;

  for(; i<v->size; ++i)
    {
      if (v->v[i] != 0)
	{
	  return(1);
	}
    }

  return(0);
}



void vector_malloc(vector** r, const uint size)
{
  if((*r = malloc(sizeof(vector))) == NULL)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Vector allocation impossible.", ERR_ALLOC);
    }

  if(((*r)->v = malloc(size*sizeof(uint))) == NULL)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Vector data allocation impossible.", ERR_ALLOC);
    }

  (*r)->size = size;
}

void vector_calloc(vector** r, const uint size)
{
  
  if((*r = malloc(sizeof(vector))) == NULL)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Vector allocation impossible.", ERR_ALLOC);
    }

  if(((*r)->v = calloc(size, sizeof(uint))) == NULL)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Vector data allocation impossible.", ERR_ALLOC);
    }

  (*r)->size = size;
}


void vector_free(vector **r)
{
  free((*r)->v);
  free(*r);
  *r = NULL;
}

void vector_fprint(FILE* out, const vector* v)
{
  uint i = 1;

  fprintf(out, "[%u", v->v[0]);
  for(; i<v->size; ++i)
    {
      fprintf(out, " %u", v->v[i]);
    }
  fprintf(out, "]\n");
}


void vector_print(const vector* v)
{
  vector_fprint(stdout, v);
}

void vector_get_size(uint* r, const vector* v)
{
  *r = v->size;
}

void vector_get_element(uint* r, const vector* v, const uint i)
{
  if(v->size <= i)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Undefined element.", ERR_MATH);
    }

  *r = v->v[i];
}


void vector_set_element(vector* v, const uint e, const uint i)
{
  if(v->size <= i)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Undefined element.", ERR_MATH);
    }

  v->v[i] = e;
}


void vector_xor(vector* r, const vector* v1, const vector* v2)
{
  uint i = 0;

  if(r->size != v1->size)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Result vector has not the good size.", ERR_MATH);
    }
  if(v1->size != v2->size)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "XOR of two different vector sizes.", ERR_MATH);
    }

  for(; i<r->size; ++i)
    {
      r->v[i] = v1->v[i] ^ v2->v[i];
    }
}

void vector_subvector(vector* r, const vector* v, const uint index)
{
  uint i = 0;

  if (index+r->size > v->size)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Result vector has not the good size.", ERR_MATH);
    }

  for(; i<r->size; ++i)
    {
      r->v[i] = v->v[i+index];
    }
}



void vector_subvectors(vector** r, const vector* v, const uint size)
{
  uint 
    i  = 0,
    it = v->size / size;

  /*
  if (v->size % size != 0)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Cannot cut the whole vector in subvector.", ERR_MATH);
    }
  */

  for(; i<it; ++i)
    {
      vector_subvector(r[i], v, i*size);
    }
}
