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
#include "Image.h"

#define TRUE 1
#define FALSE 0

int mask_rotations_fit(Image *Im, int mask[3][3], int centerLine, int centerColumn) {

    for(int i = -1; i < 2; i++){
        for(int j = -1; j < 2; j++){
            if (mask[centerLine + i][centerColumn + j] == 1){
                if (Im->image[centerLine + i][centerColumn + j] != 1){
                    return FALSE;
                }
            } else if (mask[centerLine + i][centerColumn + j] == 0){
                if (Im->image[centerLine + i][centerColumn + j] != 0){
                    return FALSE;
                }
            }
        }
    }
    
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

    read_pgm(pgm_image, "./moi.pgm");

    threashold_image(pgm_image, pbm_image, pgm_image->color_shades / 3);

    save_pgm(pbm_image, "./moi.pbm");

    int M1[3][3] = {
        {2, 0, 0},
        {1, 1, 1},
        {2, 1, 2}
    };
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

