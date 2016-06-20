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
    fprintf(fp, "# Processed on Netbeans\n");

    //Dimensions
    fprintf(fp, "%d %d\n", image->columns, image->lines);

    //Color shades
    if (strcmp(image->format, "P1"))
        fprintf(fp, "%d\n", image->color_shades);

    //Image
    for (int i = 0; i < image->lines; i++) {
        for (int j = 0; j < image->columns; j++) {
            fprintf(fp, "%d ", image->image[i * image->columns + j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);

    return 0;
}

int read_pgm(Image *image, char * filePath) {

    FILE *fp;

    fp = fopen(filePath, "r");
    if (!fp)
        return 1;

    char * line = NULL;
    size_t len = 0;

    //image format
    getline(&line, &len, fp);
    sscanf(line, "%s", image->format);

    //Comment
    getline(&line, &len, fp);

    //Dimensions
    getline(&line, &len, fp);
    int width, height;
    sscanf(line, "%d %d", &width, &height);
    //    printf("Width is: %d and height is: %d\n", width, height);

    image->columns = width;
    image->lines = height;

    //Color shades
    int colorShades;
    if (!strcmp(image->format, "P1")) {
        colorShades = 2;
    } else {
        getline(&line, &len, fp);
        sscanf(line, "%d", &colorShades);
    }

    image->color_shades = colorShades;
    initialize_image(image, height, width);

    int value;
    for (int i = 0; i < image->lines; i++) {
        for (int j = 0; j < image->columns; j++) {
            fscanf(fp, "%d", &value);
            image->image[i * image->columns + j] = value;
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
    out->lines = in->lines;
    out->columns = in->columns;

    initialize_image(out, in->lines, in->columns);

    for (int i = 0; i < in->lines; i++) {
        for (int j = 0; j < in->columns; j++) {
            out->image[i * out->columns + j] = in->image[i * in->columns + j];
        }
    }

}

void initialize_image(Image *I, int height, int width) {

    I->columns = width;
    I->lines = height;
    I->image = malloc(sizeof (int *) * height * width);
}

int pgm_to_pbm(Image *I, Image *O, int threshold) {

    if (threshold > I->color_shades) {
        return 0;
    }

    initialize_image(O, I->lines, I->columns);
    strcpy(O->format, "P1");
    O->color_shades = 2;

    for (int i = 0; i < I->lines; i++)
        for (int j = 0; j < I->columns; j++)
            O->image[i * O->columns + j] = (int) (I->image[i * I->columns + j] > threshold) ? 0 : 1;

    return 1;
}