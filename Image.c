/*-------------------------------------------------------------
 *          UNIFAL – Universidade Federal de Alfenas.          
 *            BACHARELADO EM CIENCIA DA COMPUTACAO.            
 * Trabalho..: Afinamento homotópico          
 * Disciplina: PROCESSAMENTO DE IMAGENS                        
 * Professor.: Luiz Eduardo da Silva                           
 * Aluno.....: Reuel Ramos Ribeiro
 *
 * Data......: 06/06/2016                                      
 *-------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Image.h"

int read_pgm(Image *image, char * filePath) {

    FILE *fp;

    fp = fopen(filePath, "r");
    if (!fp)
        return 1;

    char * line = NULL;
    size_t len = 0;
    ssize_t lineSize;

    //image format
    getline(&line, &len, fp);
    strcpy(line, image->format);

    //Comment
    getline(&line, &len, fp);

    //Dimensions
    getline(&line, &len, fp);
    int width, height;
    sscanf(line, "%d %d", &width, &height);
    //    printf("Width is: %d and height is: %d\n", width, height);

    image->width = width;
    image->height = height;

    //Color shades
    getline(&line, &len, fp);
    int colorShades;
    sscanf(line, "%d", &colorShades);
    //    printf("The file contains %d color shades\n", colorShades);

    image->color_shades = colorShades;

    image->image = malloc(sizeof (int *) * height);

    for (int i = 0; i < height; i++) {
        image->image[i] = malloc(sizeof (int) * width);
    }

    int value;
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            fscanf(fp, "%d", &value);
            image->image[i][j] = value;
            printf("%3d\n", image->image[i][j]);
        }
    }
    
    fclose(fp);
    if (line)
        free(line);
    return 0;
}

