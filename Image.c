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

int save_pgm(Image *image, char * filePath) {
    FILE *fp;

    fp = fopen(filePath, "w");
    if (!fp) {
        return 1;
    }

    //Format
    fprintf(fp, "%s\n", image->format);

    //Comment
    fprintf(fp, "#Binary image\n");

    //Dimensions
    fprintf(fp, "%d %d\n", image->width, image->height);

    //Color shades
    fprintf(fp, "%d\n", image->color_shades);

    //Image
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            fprintf(fp, "%d ", image->image[i*image->width + j]);
        }
        fprintf(fp, "\n");
    }
}

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
    initialize_image(image, height, width);

    int value;
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            fscanf(fp, "%d", &value);
            image->image[i* image->width + j] = value;
        }
    }

    fclose(fp);
    if (line)
        free(line);
    return 0;
}

int copy_image(Image *in, Image *out) {
    strcpy(out->format, in->format);
    out->color_shades = in->color_shades;
    out->height = in->height;
    out->width = in->width;

    initialize_image(out, in->height, in->width);

    for (int i = 0; i < in->height; i++) {
        for (int j = 0; j < in->width; j++) {
            out->image[i * out->width + j] = in->image[i * in->width + j];
        }
    }

}

void initialize_image(Image *I, int height, int width) {

    I->width = width;
    I->height = height;
    I->image = malloc(sizeof (int *) * height * width);
}

int threashold_image(Image *I, Image *O, int threashold) {

    if (threashold > I->color_shades) {
        return 0;
    }

    initialize_image(O, I->height, I->width);
    strcpy(O->format, "P1");
    O->color_shades = 2;

    for (int i = 0; i < I->height; i++)
        for (int j = 0; j < I->width; j++)
            O->image[i* O->width +j] = (int) (I->image[i* I->width +j] > threashold) ? 1 : 0;

    return 1;
}