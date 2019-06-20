#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include "inode.h"

#define LEN_INODE sizeof(INODE)
#define N_INODES 2
#define N_BLOCKS 10
#define N_BYTES 5

//unsigned char file_iterator[N_BLOCKS] = {0};

//typedef struct BLOCK
//{
//  unsigned char block_data[N_BYTES];
//} DATA_BLOCK;

// Funções sistema de arquivos
//void criaDiretorioRaiz();
//void criaSistemaArquivos();
void inicializaArquivo(char *buffer, char *tamBloco, char *qtdBloco, char *qtdInode);
void criaNodo(FILE **fp, INODE *node, int isUsed, int isDir, char *name, int size, int directBlock0, int directBlock1, int directBlock2, int directBlock3);
void editaNodo(FILE **fp, INODE *node, int isUsed, int isDir, char *name, int size, int directBlock0, int directBlock1, int directBlock2, int directBlock3);

//void adicionarArquivo(char *comando, FILE *fp);
//void adicionarDiretorio(char *comando, FILE *fp);
