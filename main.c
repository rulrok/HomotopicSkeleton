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

/*
 * 
 */
int main(int argc, char** argv) {

    Image * pgm_image = malloc(sizeof(Image));
    Image * pbm_image = malloc(sizeof(Image));
    
    read_pgm(pgm_image, "./moi.pgm");
    
    threashold_image(pgm_image, pbm_image, pgm_image->color_shades/3);
    
    save_pgm(pbm_image, "./moi.pbm");
    
    free(pbm_image);
    free(pgm_image);
    
    return (EXIT_SUCCESS);
}

