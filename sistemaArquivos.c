#include "sistemaArquivos.h"
#include "inode.h"

void criaSistemaArquivos()
{
    arq = fopen('fs.bin', "wb+");

    inicializaArquivo(arq);
    //criaDiretorioRaiz();
}

void inicializaArquivo(FILE *arq)
{
    fclose(arq);
    arq = fopen('fs.bin', "wb+");
    fwrite(&file_iterator, sizeof(file_iterator), 1, arq);

    for (int i = 0; i < N_INODES; i++)
        criaNodoVazio(arq);

    for (int i = 0; i < N_BLOCKS; i++)
        fwrite(&file_iterator, sizeof(file_iterator), 1, arq);
}

void criaDiretorioRaiz()
{
    fclose(arq);
    arq = fopen('fs.bin', "wb+");
}

void criaNodoVazio(FILE *arq)
{
    INODE nodo;
    nodo.IS_USED = 0;
    nodo.IS_DIR = 0;
    strcpy(nodo.NAME, "new");
    nodo.SIZE = 0;
    nodo.DIRECT_BLOCKS;
    nodo.INDIRECT_BLOCKS;
    nodo.DOUBLE_INDIRECT_BLOCKS;
    fwrite(&nodo, sizeof(nodo), 1, arq);
};