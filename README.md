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
