#include "sistemaArquivos.h"

int main(int argc, int argv[])
{
 char buffer[255], *charAux, nomeArquivo[20], qtdBloco[20], tamBloco[20], qtdInode[20];
    FILE *fp;

    fgets(buffer, sizeof(buffer), stdin);

    //Cria Arquivo
    if (strncmp(buffer, "init", 4) == 0)
    {
        charAux = strtok(buffer, " ");
        int i = 0;
        while (charAux != NULL)
        {

            charAux = strtok(NULL, " ");
            if (i == 0)
            {
                strcpy(nomeArquivo, charAux);
                printf("%s \n", nomeArquivo);
            }
            if (i == 1)
            {
                strcpy(qtdBloco, charAux);
                printf("%s \n", qtdBloco);
            }

            if (i == 2)
            {
                strcpy(tamBloco, charAux);
                printf("%s \n", tamBloco);
            }

            if (i == 3)
            {
                strcpy(qtdInode, charAux);
                printf("%s \n", qtdInode);
            }
            i++;
        }

        fp = fopen(nomeArquivo, "wb+");


    }
}

