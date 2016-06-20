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
#include <string.h>
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
void print_matrix(int lines, int columns, int *M, int num, ...) {

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
    printf("Matrix[%d][%d]\n", (int) lines, (int) columns);
    for (int i = startLine; i < endLine; i++) {
        for (int j = startColumn; j < endColumn; j++) {
            printf("%d,", M[i * columns + j]);
        }
        printf("\n");
    }
    printf("\n");
}

void rotate_square_matrix(size_t dim, int M[dim][dim], int O[dim][dim]) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            O[j][2 - i] = M[i][j];
        }
    }
}

int mask_fit(Image *Im, int mask[3][3], int x, int y) {

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (mask[x + i][y + j] == 1) {
                if (Im->image[(x + i) * Im->columns + (y + j)] != 1) {
                    return FALSE;
                }
            } else if (mask[x + i][y + j] == 0) {
                if (Im->image[(x + i) * Im->columns + (y + j)] != 0) {
                    return FALSE;
                }
            }
        }
    }

    return TRUE;

}

int mask_rotations_fit(Image *Im, int x, int y, int rot1[3][3], int rot2[3][3], int rot3[3][3], int rot4[3][3]) {

    return (mask_fit(Im, rot1, x, y) ||
            mask_fit(Im, rot2, x, y) ||
            mask_fit(Im, rot3, x, y) ||
            mask_fit(Im, rot4, x, y));

}

Image * erode_image(Image *Im, int SE1[3][3], int SE2[3][3]) {

    Image * Out = malloc(sizeof (Image));
    copy_image(Im, Out);

    Image * Aux = malloc(sizeof (Image));
    copy_image(Im, Aux);

    //Prepare the other rotations for the structuring element
    int SE1r2[3][3];
    rotate_square_matrix(3, SE1, SE1r2);
    int SE1r3[3][3];
    rotate_square_matrix(3, SE1r2, SE1r3);
    int SE1r4[3][3];
    rotate_square_matrix(3, SE1r3, SE1r4);

    //Prepare the other rotations for the other structuring element
    int SE2r2[3][3];
    rotate_square_matrix(3, SE2, SE2r2);
    int SE2r3[3][3];
    rotate_square_matrix(3, SE2r2, SE2r3);
    int SE2r4[3][3];
    rotate_square_matrix(3, SE2r3, SE2r4);

    int changed;
    int steps = 1;
    while (TRUE) {
        changed = FALSE;

        //Ignore the border, thus i = j = 1 up to dimensions - 1
        for (int i = 1; i < Aux->lines - 1; i++) {
            for (int j = 1; j < Aux->columns - 1; j++) {
                //Apply rotations to the point aux[i][j]
                if (mask_rotations_fit(Aux, i, j, SE1, SE1r2, SE1r3, SE1r4)) {
                    //If match, update out[i][j] & set changed = 1
                    Out->image[i * Out->columns + j] = 1;
                    changed = TRUE;
                } else {
                    Out->image[i * Out->columns + j] = 0;
                }

            }
        }

        //        printf("\n");
        //        print_matrix(Out->lines, Out->columns, Out->image, 0);
        char out_filename[80];
        sprintf(out_filename, "./out.%d.pbm", steps);
        save_pgm(Out, out_filename);

        if (!changed) {
            return Out;
        }
        steps++;

        Image * switchPtr = Aux;
        Aux = Out;
        Out = switchPtr;

    }

    return Out;
}

/*
 * 
 */
int main(int argc, char** argv) {

    Image * pgm_image = malloc(sizeof (Image));
    Image * pbm_image = malloc(sizeof (Image));

    read_pgm(pgm_image, "./moi.pgm");

    threshold_image(pgm_image, pbm_image, pgm_image->color_shades / 3);
    //
    //    save_pgm(pbm_image, "./moi.pbm");

    int M1[3][3] = {
        {2, 0, 0},
        {1, 1, 1},
        {2, 1, 2}
    };

    int M2[3][3] = {
        {2, 0, 0},
        {1, 1, 1},
        {2, 1, 2}
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

