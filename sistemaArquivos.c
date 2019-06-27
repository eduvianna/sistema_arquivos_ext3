#include "sistemaArquivos.h"

void inicializaArquivo(char *buffer)
{
    char *aux, tamBloco[5], qtdBloco[5], qtdInode[5];
    FILE *fp;
    int i = 0, tamMapaBits, tamVetorBlocos;

    aux = strtok(buffer, " ");
    while (aux != NULL)
    {

        aux = strtok(NULL, " ");
        if (i == 0)
        {
            fp = fopen(aux, "wb+");
        }

        if (i == 1)
        {
            strcpy(tamBloco, aux);
        }

        if (i == 2)
        {
            strcpy(qtdBloco, aux);
        }

        if (i == 3)
        {
            strcpy(qtdInode, aux);
        }
        i++;
    }
    //Converte os valores recebidos de qtdBloco, tamBloco e qtdInode em inteiros
    int i_qtdBloco = atoi(qtdBloco);
    int i_tamBloco = atoi(tamBloco);
    int i_qtdInode = atoi(qtdInode);
    int init = 0;
    tamMapaBits = (int)ceil(i_qtdBloco / 8.0);
    tamVetorBlocos = i_tamBloco * i_qtdBloco;

    //Inicializa o arquivo
    fwrite(&i_tamBloco, sizeof(char), 1, fp);
    fwrite(&i_qtdBloco, sizeof(char), 1, fp);
    fwrite(&i_qtdInode, sizeof(char), 1, fp);

    //Inicializa Mapa de Bits
    for (i = 0; i < tamMapaBits; i++)
    {
        if (i == 0)
        {
            init = 1;
            fwrite(&init, sizeof(char), 1, fp);
            init = 0;
        }
        else
        {
            fwrite(&init, sizeof(char), 1, fp);
        }
    }

    //Inicializa vetor de inodes
    INODE node[i_qtdInode];
    int j;

    for (i = 0; i < i_qtdInode; i++)
    {
        if (i == 0)
        {
            criaNodo(&fp, &node[i], 1, 1, "/", 0, 0, 0, 0);
        }
        else
        {
            criaNodo(&fp, &node[i], 0, 0, "", 0, 0, 0, 0);
        }
    }

    //Inicializa indice do inode (dir / indice = 0)
    fwrite(&init, sizeof(char), 1, fp);

    //Inicializa vetor de blocos

    for (j = 0; j < tamVetorBlocos; j++)
    {
        fwrite(&init, sizeof(char), 1, fp);
    }

    //Fecha Arquivo
    fclose(fp);
}

// Função que adicionar arquivo
void adicionaArquivo(char *buffer)
{
    char *aux, *aux2, fileName[10], content[10];
    char *saveptr1, *saveptr2;
    unsigned char bufferFile[255];
    FILE *fp;
    INODE node;
    int i = 0, sizeFile;

    aux = strtok_r(buffer, " ", &saveptr1);
    while (aux != NULL)
    {

        aux = strtok_r(NULL, " ", &saveptr1);
        if (i == 0)
        {
            fp = fopen(aux, "ab+");
            sizeFile = fread(bufferFile, sizeof(unsigned char), 255, fp);
        }

        if (i == 1)
        {
            aux2 = strtok_r(aux, "/", &saveptr2);
            strcpy(fileName, aux2);
        }

        if (i == 2)
        {
            strcpy(content, aux);
            criaNodo(&fp, &node, 1, 0, fileName, 0, 0, 0, 0);
        }

        i++;
    }

    for (i = 2; i < (sizeFile / sizeof(unsigned char)); i++)
    {
        printf("%x ", bufferFile[i]);
    }

    fclose(fp);
}

// Função que cria ou edita nodos
void criaNodo(FILE **fp, INODE *node, int isUsed, int isDir, char *name, int size, int directBlock0, int directBlock1, int directBlock2)
{
    bzero(node->NAME, sizeof(char[10]));
    node->IS_USED = isUsed;
    node->IS_DIR = isDir;
    strcpy(node->NAME, name);
    node->SIZE = size;
    node->DIRECT_BLOCKS[0] = directBlock0;
    node->DIRECT_BLOCKS[1] = directBlock1;
    node->DIRECT_BLOCKS[2] = directBlock2;
    node->INDIRECT_BLOCKS[0] = 0;
    node->INDIRECT_BLOCKS[1] = 0;
    node->INDIRECT_BLOCKS[2] = 0;
    node->DOUBLE_INDIRECT_BLOCKS[0] = 0;
    node->DOUBLE_INDIRECT_BLOCKS[1] = 0;
    node->DOUBLE_INDIRECT_BLOCKS[2] = 0;
    fwrite(node, sizeof(INODE), 1, *fp);
}
