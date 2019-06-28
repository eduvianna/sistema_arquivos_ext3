#include "sistemaArquivos.c"
//#include "sha256.c"
/*
Teste 1
Comando : init fs2-10-5.bin 2 10 5
hash: f771a21963855225af508931d7bd579ebc5e3da2854ffe41b8631a5b183f0e85

Teste 2
Comando : init fs1-10-10.bin 1 10 10
hash: f4edf3234516cabf781abe6fefdb7f0fba07f588d7a5cd651f18a4816591e3f4

Teste 3
Comando : init fs4-32-16.bin 4 32 16
hash: a2712100d14c1094c9a00abd03e72538ea3e040757e402875f7d1fb7356dfee4

Teste 4
Comando : addFile fs-case4.bin /teste.txt abc
hash: aa29b7cf09b6320e6b2051edfd8e40fbb0a871fa8a220a06f4e1e4690ac6b277

Teste 5
Comando : addDir fs-case5.bin /dec7556
hash: 0bbb605c52bc0d4f5c2cb8aa2df5f6437aec028072f2d7c37b91a6fe9e4cb644

Teste 6
Comando: addFile fs-case6.bin /dec7556/t2.txt fghi
hash: c5d515d82f091549d9a2b55836e7dc28e5c414021d030ea84e40ee76bf05f0c6

 */
int main(int argc, int argv[])
{
    char buffer[255];
    FILE *fp;

    fgets(buffer, sizeof(buffer), stdin);

    //Cria Arquivo
    if (strncmp(buffer, "init", 4) == 0)
    {
        inicializaArquivo(buffer);
    }

    // Adiciona um arquivo
    else if (strncmp(buffer, "add", 3) == 0)
    {
        adicionaArquivo(buffer);
    }
    // Adiciona um diretório
    else if (strncmp(buffer, "addDir", 6) == 0)
    {
        //printSha256("fs.bin");
        //adicionaDiretorio(buffer);
    }
}
