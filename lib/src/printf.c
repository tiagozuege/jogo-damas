#include <printf.h>

static char * const vidptr = (char *) 0xb8000;

void printf(const char *str)
{
    char *video = vidptr;

    for (; *str; video += 2, str++)
        *video = *str;
}

void shell_clear(void)
{
    int j;

    /* São 25 linhas, cada linha com 80 colunas; cada elemento possui dois
       bytes, o primeiro contendo o caractere e o segundo o atributo. */
    for (j = 0; j < 80 * 25 * 2; j += 2) {
        vidptr[j] = ' ';
    }
}

