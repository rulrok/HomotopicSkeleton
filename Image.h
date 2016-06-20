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

    typedef struct {
        int * image;
        int columns;
        int lines;
        int color_shades;
        char format[10];
    } Image;

    int save_pgm(Image *, char *);

    int read_pgm(Image *, char *);

    int copy_image(Image *in, Image *out);

    void initialize_image(Image *, int, int);

    int pgm_to_pbm(Image *, Image *, int);

#ifdef __cplusplus
}
#endif

#endif /* IMAGE */
