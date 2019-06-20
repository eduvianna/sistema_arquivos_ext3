#include "sistemaArquivos.h"

int main(int argc, int argv[])
{
    char buffer[255], *charAux, qtdBloco[10], tamBloco[10], qtdInode[10];
    FILE *fp;

    fgets(buffer, sizeof(buffer), stdin);

    //Cria Arquivo
    if (strncmp(buffer, "init", 4) == 0)
    {
        inicializaArquivo(buffer, tamBloco, qtdBloco, qtdInode);
    }
}
