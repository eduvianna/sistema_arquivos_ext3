#include "sistemaArquivos.h"

/* void criaSistemaArquivos()
{
    //arq = fopen('fs.bin', "wb+");

    //inicializaArquivo(arq);
    //criaDiretorioRaiz();
//}*/

void inicializaArquivo(char *buffer, char *tamBloco, char *qtdBloco, char *qtdInode)
{
    char *aux;
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

    for (i = 0; i < i_qtdInode; i++)
    {
        if (i == 0)
        {
            criaNodo(&fp, &node[i], 1, 1, "/", 0, 0, 0, 0, 0);
        }
        else
        {
            criaNodo(&fp, &node[i], 0, 0, "", 0, 0, 0, 0, 0);
        }
    }

    //Inicializa indice do inode (dir / indice = 0)
    fwrite(&init, sizeof(char), 1, fp);

    //Inicializa vetor de blocos
    // for (i = 0; i < tamVetorBlocos; i++)
    //{
    //fwrite(&init, sizeof(char), 1, fp);
    //}

    //Fecha Arquivo
    fclose(fp);
}

void criaNodo(FILE **fp, INODE *node, int isUsed, int isDir, char *name, int size, int directBlock0, int directBlock1, int directBlock2, int directBlock3)
{
    bzero(node->NAME, sizeof(char[10]));
    node->IS_USED = isUsed;
    node->IS_DIR = isDir;
    strcpy(node->NAME, name);
    node->SIZE = size;
    node->DIRECT_BLOCKS[0] = directBlock0;
    node->DIRECT_BLOCKS[1] = directBlock1;
    node->DIRECT_BLOCKS[2] = directBlock2;
    node->DIRECT_BLOCKS[3] = directBlock3;
    fwrite(node, sizeof(node), 1, *fp);
}

void editaNodo(FILE **fp, INODE *node, int isUsed, int isDir, char *name, int size, int directBlock0, int directBlock1, int directBlock2, int directBlock3)
{
    node->IS_USED = isUsed;
    node->IS_DIR = isDir;
    strcpy(node->NAME, name);
    node->SIZE = size;
    node->DIRECT_BLOCKS[0] = directBlock0;
    node->DIRECT_BLOCKS[1] = directBlock1;
    node->DIRECT_BLOCKS[2] = directBlock2;
    node->DIRECT_BLOCKS[3] = directBlock3;
    fwrite(node, sizeof(node), 1, *fp);
}

/*void criaDiretorioRaiz()
{
    //fclose(arq);
    //arq = fopen('fs.bin', "wb+");
}

void criaNodoVazio(FILE *arq){
    INODE nodo;
    nodo.IS_USED = 0;
    nodo.IS_DIR = 0;
    strcpy(nodo.NAME, "new");
    nodo.SIZE = 0;
    nodo.DIRECT_BLOCKS;
    nodo.INDIRECT_BLOCKS;
    nodo.DOUBLE_INDIRECT_BLOCKS;
    fwrite(&nodo, sizeof(nodo), 1, arq);
};*/