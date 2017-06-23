Projeto II

Desenvolver um jogo de tabuleiro do tipo damas para PC. O jogo deve ter
interface semelhante à encontrada em `https://youtu.be/aTIq_8ncurs`. As regras
do jogo podem ser conferidas em `https://en.wikipedia.org/wiki/Draughts`.

Junto ao arquivo do projeto estão disponibilizados uma imagem carregável,
`damas.iso`, com um exemplo de como deve ser o jogo. Também foi disponibilizado
um projeto com estrutura básica para a construção do software. O projeto pode
ser compilado e gera uma imagem que pode ser emulada pelo software qemu.

O projeto base está organizado da seguinte forma:

    projeto-base
    ├── boot
    │   └── loader.s
    ├── kernel
    │   └── kmain.c
    ├── ld
    │   └── linker.ld
    ├── lib
    │   ├── include
    │   │   ├── console.h
    │   │   ├── io.h
    │   │   ├── keyboard.h
    │   │   ├── printf.h
    │   │   └── string.h
    │   ├── lib.mk
    │   └── src
    │       ├── console.c
    │       ├── keyboard.c
    │       ├── memset.c
    │       ├── printf.c
    │       └── string.c
    ├── Makefile
    └── README.md

O projeto base contém quatro diretórios. No diretório boot está o arquivo que
carrega o sistema no momento do boot. O diretório ld contém o arquivo com a
descrição das seções do objeto binário que deve ser criado. No diretório lib são
encontradas algumas bibliotecas para utilização no projeto. O diretório kernel
contém o pronto de entrada para o software.

Também é disponibilizado uma estrutura de softwares que inclui um terminal de
comandos, compiladores, emulador e um editor de texto para facilitar o
desenvolvimento do projeto. O arquivom compactado mingw.zip deve ser
descompactado na raiz do sistema.

Para compilar o projeto base, após abrir o terminal de comandos, é necessário
navegar até o diretório onde se encontram os arquivos do projeto. O comando
`make` compila o projeto. O comando `make run` executa a imagem gerada no
emulador.
