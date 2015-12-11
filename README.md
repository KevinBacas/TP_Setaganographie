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
