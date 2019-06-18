#ifndef filesystem_h
#define filesystem_h

typedef struct
{
    int TAM_BLOCO;                      // 0x01 se utilizado, 0x00 se livre
    int QTD_BLOCO;                      // 0x01 se diretorio, 0x00 se arquivo
    int QTD_INODE;                      // nome do arquivo/dir
    int TAM_MAPABITS = (QTD_BLOCO / 8); // tamanho do arquivo/dir em bytes
    int TAM_VETOR_INODES;
    int I_DIRETORIO_RAIZ;
    int TAM_VETOR_BLOCO = TAM_BLOCO * QTD_BLOCO;
} FILESYSTEM;

#endif /* filesystem_h */