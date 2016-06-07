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

int read_pgm(Image *image, char * filePath) {

    FILE *f;

    f = fopen(filePath, "r");
    if (!f)
        return 1;
    int c;
    while ((c = getc(f)) != EOF)
        putchar(c);
    
    fclose(f);
    return 0;
}

