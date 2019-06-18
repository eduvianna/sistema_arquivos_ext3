#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LEN_INODE sizeof(INODE)
#define N_INODES 2
#define N_BLOCKS 10
#define N_BYTES 5

FILE *arq;

unsigned char file_iterator[N_BLOCKS] = {0};

typedef struct BLOCK
{
    unsigned char block_data[N_BYTES];
} DATA_BLOCK;

// Funções sistema de arquivos
void criaDiretorioRaiz();
void criaSistemaArquivos();
void inicializaArquivo(arq);
void criaNodoVazio(FILE *arq);

void adicionarArquivo(char *comando, FILE *fp);
void adicionarDiretorio(char *comando, FILE *fp);
