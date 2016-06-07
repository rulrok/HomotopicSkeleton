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

#ifndef IMAGE
#define IMAGE

#ifdef __cplusplus
extern "C" {
#endif
    
typedef struct  {
    int ** image;
    int width;
    int height;
    int color_shades;
    char format[10];
} Image;

int read_pgm(Image *, char *);

#ifdef __cplusplus
}
#endif

#endif /* IMAGE */
