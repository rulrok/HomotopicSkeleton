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
    
    read_pgm(pgm_image, "./moi.pgm");
    
    free(pgm_image);
    
    return (EXIT_SUCCESS);
}

