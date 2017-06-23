#ifndef CONSOLE_H
#define CONSOLE_H

#define CONSOLE_ROWS            25
#define CONSOLE_COLS            80

//Tamanho do tabuleiro sem contar as bordas
#define TABULEIRO_LINHAS        16  //y
#define TABULEIRO_COLUNAS       32  //x

#define TABULEIRO_X             52    //limite da posicao x
#define TABULEIRO_Y             19
enum color {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    YELLOW,
    GRAY,
    BRIGHT
};

extern void putc(int x, int y, enum color fg, enum color bg, char c);

extern void puts(int x, int y, enum color fg, enum color bg, const char *s);

extern void clear(enum color bg);

#endif // CONSOLE_H
