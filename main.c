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
    Image * new_image = malloc(sizeof(Image));
    
    read_pgm(pgm_image, "./moi.pgm");
    
    threashold_image(pgm_image, new_image, 5);
    
    save_pgm(new_image, "./moi.pbm");
    
    free(new_image);
    free(pgm_image);
    
    return (EXIT_SUCCESS);
}

