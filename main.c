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
#include <stdarg.h>
#include "Image.h"

#define TRUE 1
#define FALSE 0

/*
 * Print a matrix.
 * This function allows to specify a sub-matrix so only that portion will be printed
 * rows - Dimension in lines of the matrix
 * columns - Dimension in columns of the matrix
 * M - The bidimensional matrix
 * num - The number of following parameters. Must be between 0 and 4 inclusive.
 * startLine - The line which it should start printing
 * startColumn - The columns which it should start printing
 * endLine - The final line to be printed
 * endColumn - The final column to be printed
 */
void print_matrix(size_t lines, size_t columns, int M[lines][columns], int num, ...) {

    va_list list;

    va_start(list, num);

    int startLine = 0;
    int startColumn = 0;
    int endLine = lines;
    int endColumn = columns;

    switch (num) {
        case 1:
            startLine = va_arg(list, int);
            break;
        case 2:
            startLine = va_arg(list, int);
            startColumn = va_arg(list, int);
            break;
        case 3:
            startLine = va_arg(list, int);
            startColumn = va_arg(list, int);
            endLine = va_arg(list, int);
            break;
        case 4:
            startLine = va_arg(list, int);
            startColumn = va_arg(list, int);
            endLine = va_arg(list, int);
            endColumn = va_arg(list, int);
            break;
    }

    va_end(list);

    for (int i = startLine; i < endLine; i++) {
        for (int j = startColumn; j < endColumn; j++) {
            printf("%d,", M[i][j]);
        }
        printf("\n");
    }
}

int mask_fit(Image *Im, int mask[3][3], int centerLine, int centerColumn) {

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (mask[centerLine + i][centerColumn + j] == 1) {
                if (Im->image[centerLine + i][centerColumn + j] != 1) {
                    return FALSE;
                }
            } else if (mask[centerLine + i][centerColumn + j] == 0) {
                if (Im->image[centerLine + i][centerColumn + j] != 0) {
                    return FALSE;
                }
            }
        }
    }

    return TRUE;

}

int mask_rotations_fit(Image *Im, int mask[3][3], int centerLine, int centerColumn) {

    return TRUE;

}

Image * erode_image(Image *Im, int SE1[3][3], int SE2[3][3]) {

    Image * Out = malloc(sizeof (Image));
    copy_image(Im, Out);

    Image * aux = malloc(sizeof (Image));
    initialize_image(aux, Out->height, Out->width);

    int changed;
    while (changed) {
        changed = FALSE;

        //Ignore the border, thus i = j = 1 up to dimensions - 1
        for (int i = 1; i < Im->height - 1; i++) {
            for (int j = 1; j < Im->width - 1; j++) {
                //Apply rotations to the point aux[i][j]
                if (mask_rotations_fit(Im, SE1, i, j)) {
                    //If match, update out[i][j] & set changed = 1
                    Out->image[i][j] = Im->image[i][j];
                    changed = TRUE;
                }

            }
        }


    }

    return Out;
}

/*
 * 
 */
int main(int argc, char** argv) {

    Image * pgm_image = malloc(sizeof (Image));
    Image * pbm_image = malloc(sizeof (Image));

    //    read_pgm(pgm_image, "./moi.pgm");
    //
    //    threashold_image(pgm_image, pbm_image, pgm_image->color_shades / 3);
    //
    //    save_pgm(pbm_image, "./moi.pbm");

    int M1[3][3] = {
        {2, 0, 0},
        {1, 1, 1},
        {2, 1, 2}
    };
    print_matrix(3, 3, M1);

    int M2[3][3] = {
        2, 0, 0,
        1, 1, 1,
        2, 1, 2
    };

    Image * eroded_image = erode_image(pbm_image, M1, M2);

    int L1[3][3] = {
        0, 0, 0,
        2, 1, 2,
        1, 1, 1
    };
    int L2[3][3] = {
        2, 0, 2,
        1, 1, 1,
        2, 1, 2
    };

    free(pbm_image);
    free(pgm_image);

    return (EXIT_SUCCESS);
}

