#include "PGM.h"

void PGM_create(pgm** r, const char* filename)
{
  FILE* img;
  uint
    width,
    height,
    i = 0,
    j,
    format;
  
  char tmp[100];


  if((*r = malloc(sizeof(pgm))) == NULL)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Allocation for image data impossible.", ERR_ALLOC);
    }

  file_open(&img, filename, "r");
  
  fscanf(img, "P%u\n", &format);
  if(format != 2)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Format not identified!", ERR_FORMAT);
    }

  fgets(tmp, 100, img);

  fscanf(img, "%u", &width);
  fscanf(img, "%u", &height);

  fscanf(img, "%u", &((*r)->grayscale));
  matrix_malloc(&((*r)->img), height, width);
  
  for(; i<height; ++i)
    {
      for(j=0; j<width; ++j)
	{
	  fscanf(img, "%u",&((*r)->img->data[i][j]));
	}
    }
  file_close(&img);
}


void PGM_destroy(pgm** p)
{
  matrix_free(&((*p)->img));
  free(*p);
  *p = NULL;
}

void PGM_fprint(FILE* out,const pgm* p)
{
  uint
    i = 0,
    j;

  fprintf(out, "P2\n");
  fprintf(out, "# M. Barbier - C program\n");
  fprintf(out, "%u %u\n", p->img->nb_col, p->img->nb_row);
  fprintf(out, "%u\n", p->grayscale);

  for(; i<p->img->nb_row; ++i)
    {
      fprintf(out, "%u", p->img->data[i][0]);
      for(j=1; j<p->img->nb_col; ++j)
	{
	  fprintf(out, " %u", p->img->data[i][j]);
	}
      fprintf(out, "\n");
    }
}


void PGM_get_width(uint *r, const pgm* img)
{
  *r = img->img->nb_col;
}


void PGM_get_height(uint *r, const pgm* img)
{
  *r = img->img->nb_row;
}

void PGM_diff(const pgm* p1, const pgm* p2, pgm** p_out)
{
  uint
    w_p1,
    h_p1,
    w_p2,
    h_p2,
    i,
    j;

  if((*p_out = malloc(sizeof(pgm))) == NULL)
  {
    error_print(__FILE__, __LINE__, __FUNCTION__,
    "Allocation for image data impossible.", ERR_ALLOC);
  }
  (*p_out)->grayscale = p1->grayscale;

  PGM_get_width(&w_p1, p1);
  PGM_get_height(&h_p1, p1);
  PGM_get_width(&w_p2, p2);
  PGM_get_height(&h_p2, p2);
  if(w_p1 == w_p2 && h_p1 == h_p2) {
    matrix_malloc(&((*p_out)->img), h_p1, w_p1);

    for (i = 0; i < w_p1; ++i) {
      for (j = 0; j < h_p1; ++j) {
        if((p2->img->data[i][j] - p1->img->data[i][j]) != 0) {
          (*p_out)->img->data[i][j] = (*p_out)->grayscale;
        }
      }
    }
  }
}
