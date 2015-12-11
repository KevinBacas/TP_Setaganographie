# TP_Setaganographie

## Question 1
```c
printf("Creating the Hamming code: ");
// On créer le code de Hamming
HCode_create(&C, 8);

printf("OK\n");


printf("Embed '%s' into '%s' which produces '%s': ", txt_ori, img_ori, img_stegano);
// On embarque le message contenu dans le fichier "test.txt" dans l'image
stegano_embed_file(img_stegano, txt_ori, img_ori, C);

printf("OK\n");


printf("Extract '%s' into '%s': ", img_stegano, txt_ext);
// On extrait le text de l'image
stegano_extract_file(txt_ext, img_stegano, C);

printf("OK\n");


printf("Free the memory: ");
// On libère le code de Hamming
HCode_free(&C);

printf("OK\n");
```

## Question 2
```shell
diff images/test.txt images/extraction.txt
# Aucune différence n'est notée...
```


## Question 3
```c
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
```

On obtient donc une image avec les pixels modifiés. On observe que les pixels modifiés se  trouvent en haut de l'image à chaque fois. Ce n'est pas très interessant car facilement attaquable. Via une permutation nous alons essayés  de rendre cela plus aléatoire.


## Question 4
```c
uint* stegano_gen_permut(uint size) {
  uint i;
  uint* res;
  srand(time(NULL));
  res = malloc(sizeof(uint) * size);
  for (i = 0; i < size; ++i)
  {
    res[i] = i;
  }

  for(i = 0; i < size; ++i) {
    uint s = rand() & size;
    uint tmp = res[i];
    res[i] = res[s];
    res[s] = tmp;
  }
  return res;
}

void stegano_permut_free(uint** v) {
  free(*v);
}

void stegano_permut_vector(vector *vec, uint* permut_tab) {
  int i;
  uint tmp;
  for (i = 0; i < (int)vec->size; ++i)
  {
    tmp = vec->v[i];
    vec->v[i] = vec->v[permut_tab[i]];
    vec->v[permut_tab[i]] = tmp;
  }
}

void stegano_inv_permut_vector(vector *vec, uint* permut_tab) {
  int i;
  uint tmp;
  for (i = (vec->size-1); i > -1; --i)
  {
    tmp = vec->v[i];
    vec->v[i] = vec->v[permut_tab[i]];
    vec->v[permut_tab[i]] = tmp;
  }
}
```

La permutation ne s'opère que sur les lignes mais pas sur les colones, de ce fait la sortie est différente mais les points se trouvent toujours en haut. Mon problème vient de la compréhension de la fonction `stegano_embed_file`. Il faudrait que je regarde plus de temps le code afin d'insérer la permutation au bon endroit.
