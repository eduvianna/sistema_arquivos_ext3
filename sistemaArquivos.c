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
    char fileNameAux[100], fileName[10], content[10], dir[10];
    char *aux, *aux2, *saveptr1, *saveptr2;
    unsigned char bufferFile[255];
    FILE *fp;
    INODE node;
    int i = 0, j, bar = 0, sizeFile;
    unsigned char vectorInitFile[3];
    aux = strtok_r(buffer, " ", &saveptr1);
    while (aux != NULL)
    {

        aux = strtok_r(NULL, " ", &saveptr1);
        if (i == 0)
        {
            fp = fopen(aux, "r+b");
            sizeFile = fread(bufferFile, sizeof(unsigned char), 255, fp);
        }

        if (i == 1)
        {
            strcpy(fileNameAux, aux);
            while (fileNameAux[j] != ' ')
            {
                if (fileNameAux[j] == '/')
                {
                    bar++;
                }
                j++;
            }
            if (bar == 1)
            {
                aux2 = strtok_r(aux, "/", &saveptr2);
                strcpy(dir, "/");
                strcpy(fileName, aux2);
            }
            else
            {
                aux2 = strtok_r(aux, "/", &saveptr2);
                strcpy(dir, "/");
                j = 0;
                while (aux2 != NULL)
                {
                    if (j < bar)
                    {
                        //adicionadir(dir);
                    }
                    else
                    {
                        strcpy(fileName, aux2);
                    }
                    j++;
                }
            }
        }

        if (i == 2)
        {
            strcpy(content, aux);
        }

        i++;
    }
    // Recebe vetor de configuracao do sistema de arquivo
    fseek(fp, 0, SEEK_SET);
    fread(vectorInitFile, sizeof(unsigned char), 3, fp);

    int tamMapaBits = (int)ceil(vectorInitFile[1] / 8.0);
    int qtdBlocosNecessarios = (int)ceil(strlen(content) / vectorInitFile[0]);
    unsigned char mapaBits[2];
    // Recebe vetor Mapa de Bits
    fseek(fp, 0, SEEK_CUR);
    fread(mapaBits, sizeof(unsigned char), 1, fp);

    unsigned int *p;
    int pChar, l = 0;
    long int pos;
    fseek(fp, 3, SEEK_SET);
    int liberado = 1;
    int posMapaBits[3] = {0, 0, 0};
    int k = 0;

    for (i = 0; i < tamMapaBits; i++)
    {
        pos = ftell(fp);
        fread(mapaBits, sizeof(unsigned char), 1, fp);
        p = int_to_bin(*mapaBits);
        for (j = 0; j < 7; j++)
        {
            if (p[j] == 0 && qtdBlocosNecessarios != 0)
            {
                p[j] = 1;
                posMapaBits[k] = j + l;
                qtdBlocosNecessarios--;
                k++;
            }
            else if (p[j] == 1 && qtdBlocosNecessarios != 0)
            {
            }
            else
            {
                liberado = 0;
                break;
            }
        }
        l++;
        pChar = bin_to_int(p);
        fseek(fp, pos, SEEK_SET);
        fwrite(&pChar, sizeof(char), 1, fp);
        fseek(fp, 1, SEEK_CUR);
    }

    if (liberado == 0)
    {
        unsigned char isUsed[2], sizeDir[2], blocoFree[2], isDir[2], dirCheck[10], dirAux[2];
        int iSizeDir;

        // Atualizar Inodes
        fseek(fp, 3 + tamMapaBits, SEEK_SET);
        for (i = 0; i < (int)vectorInitFile[2]; i++)
        {
            pos = ftell(fp);
            fread(isUsed, sizeof(unsigned char), 1, fp);
            if (*isUsed == 0)
            {
                fseek(fp, pos, SEEK_SET);
                iSizeDir = strlen(content) - 1;
                criaNodo(&fp, &node, 1, 0, fileName, iSizeDir, posMapaBits[0], posMapaBits[1], posMapaBits[2]);
                fseek(fp, 15 + tamMapaBits, SEEK_SET);

                //Alterar Tamanho do inode pai
                fseek(fp, 4 + tamMapaBits, SEEK_SET);
                for (j = 0; j < (int)vectorInitFile[2]; j++)
                {
                    pos = ftell(fp);
                    fread(isDir, sizeof(unsigned char), 1, fp);
                    if ((int)*isDir == 1)
                    {
                        k = 0;
                        do
                        {
                            fread(dirAux, sizeof(unsigned char), 1, fp);
                            strcat(dirCheck, dirAux);
                            k++;
                        } while (*dirAux != 0);

                        if (strcmp(dir, dirCheck) == 0)
                        {
                            fseek(fp, pos + 10, SEEK_CUR);

                            pos = ftell(fp);
                            fread(sizeDir, sizeof(unsigned char), 1, fp);
                            iSizeDir = (int)*sizeDir + 1;
                            fseek(fp, pos, SEEK_SET);
                            fwrite(&iSizeDir, sizeof(char), 1, fp);
                            break;
                        }
                    }
                }

                // Adicionar Content no vetor de blocos
                l = 0;
                for (j = 0; j < 3; j++)
                {
                    fseek(fp, -((int)vectorInitFile[0] * (int)vectorInitFile[1]) + posMapaBits[j] * 2, SEEK_END);

                    for (k = 0; k < (int)vectorInitFile[0]; k++)
                    {
                        pos = ftell(fp);
                        fread(blocoFree, sizeof(unsigned char), 1, fp);
                        if ((int)*blocoFree == 0 && (l < strlen(content) - 1))
                        {
                            fseek(fp, pos, SEEK_SET);
                            fwrite(&content[l], sizeof(char), 1, fp);
                            l++;
                        }
                    }
                    if (l >= strlen(content) - 1)
                    {
                        break;
                    }
                }

                break;
            }
            else
            {
                fseek(fp, 3 + tamMapaBits + (22 * i), SEEK_SET);
            }
        }
    }

    fclose(fp);
}

unsigned int *int_to_bin(unsigned int k)
{
    int i;
    unsigned int *bin = malloc(sizeof(int) * 8);
    int binAux[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    for (i = 0; i < 8; i++)
    {
        bin[i] = 0;
    }
    i = 7;
    while (k > 0)
    {

        if ((k % 2) == 0)
        {
            binAux[i] = 0;
        }
        else
        {
            binAux[i] = 1;
        }

        k /= 2;
        i--;
    }

    for (i = 0; i < 8; i++)
    {
        bin[i] = binAux[7 - i];
    }

    return bin;
}

int bin_to_int(unsigned int binArray[])
{

    int i = 0;
    int total = 0;
    for (i = 0; i < 8; i++)
    {
        if (binArray[i] == 1)
        {
            total += pow(2, i);
        }
    }
    return total;
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
