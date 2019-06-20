#include "sistemaArquivos.h"
#include "inode.h"

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

    node[0].IS_USED = 1;
    node[0].IS_DIR = 1;
    bzero(node[0].NAME, sizeof(char[10]));
    strcpy(node[0].NAME, "/");

    node[0].SIZE = 0;
    node[0].DIRECT_BLOCKS[0] = 0;
    node[0].DIRECT_BLOCKS[1] = 0;
    node[0].DIRECT_BLOCKS[2] = 0;
    node[0].DIRECT_BLOCKS[3] = 0;

    for (i = 0; i < i_qtdInode; i++)
    {

        fwrite(&node[i], 1, sizeof(INODE) * i_qtdInode, fp);
    }
    //Fecha Arquivo
    fclose(fp);
}

/*void criaDiretorioRaiz()
{
    //fclose(arq);
    //arq = fopen('fs.bin', "wb+");
}

void criaNodoVazio(FILE *arq){
    //    INODE nodo;
    //  nodo.IS_USED = 0;
    //nodo.IS_DIR = 0;
    //strcpy(nodo.NAME, "new");
    //nodo.SIZE = 0;
    //nodo.DIRECT_BLOCKS;
    //nodo.INDIRECT_BLOCKS;
    //nodo.DOUBLE_INDIRECT_BLOCKS;
    //fwrite(&nodo, sizeof(nodo), 1, arq);
};*/