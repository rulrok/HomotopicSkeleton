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

Image * erode_image(Image *image, int arr1[3][3], int arr2[3][3]){
    Image * out = malloc (sizeof(Image));
    
    return out;
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

