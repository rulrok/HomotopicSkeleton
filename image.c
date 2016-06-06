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

struct Image {
    int ** image;
    int width;
    int height;
    int color_shades;
    char format[10];
};

