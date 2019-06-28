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
void inicializaArquivo(char *buffer);
void adicionaArquivo(char *buffer);
void adicionaDiretorio(char *buffer);

unsigned int *int_to_bin(unsigned int k);
int bin_to_int(unsigned int binArray[]);
void criaNodo(FILE **fp, INODE *node, int isUsed, int isDir, char *name, int size, int directBlock0, int directBlock1, int directBlock2);
