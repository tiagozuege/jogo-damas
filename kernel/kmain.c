#include <console.h>
#include <keyboard.h>
#include <string.h>
#include <serial.h>
#include <stdio.h>

//pecasCor[peca][x,y]
int pecasAzuis[12][2] = { {28, 5},
                          {36, 5},
                          {44, 5},
                          {52, 5},
                          {24, 7},
                          {32, 7},
                          {40, 7},
                          {48, 7},
                          {28, 9},
                          {36, 9},
                          {44, 9},
                          {52, 9} };
//pecasCor[peca][x,y]
int pecasVermelhas[12][2] = { {24, 19},
                              {32, 19},
                              {40, 19},
                              {48, 19},
                              {28, 17},
                              {36, 17},
                              {44, 17},
                              {52, 17},
                              {24, 15},
                              {32, 15},
                              {40, 15},
                              {48, 15} };
//jogada => 0 --> azul
//jogada => 1 --> vermelha
int jogada = 0;

void desenhaTela() {

//Tamanho total da tela = 25 L. / 80 COL.

  int x = 0;
  int y = 0;
  int aux_x = 0;
  int aux_y = 0;
  int trocaCor = 0;

  clear(GRAY);

  //desenha a parte superior da tela (AZUL)
  for (char col = 0; col < 80; col++) {
    for (char lin = 0; lin < 1; lin++) {

      putc(x, y, YELLOW, BLUE, "");
      y ++;
    }

    y = 0;
    x++;
  }

  //posiciona o cursor Y na posicao 24 para comecar o desenha inferior
  y = 24;
  x = 0;
  //desenha a parte inferior da tela (VERMELHO)
  for (char col = 0; col < 80; col++) {
    for (char lin = 0; lin < 1; lin++) {
      putc(x, y, YELLOW, RED, "");
      y ++;
    }

    y = 24;
    x++;
  }

  //desenha o tabuleiro
  x = 20;
  y = 2;

  for (char col = 0; col < 40; col++) {     //colunas (X)
    for (char lin = 0; lin < 20; lin++) {   //linhas (Y)

      putc(x, y, GRAY, BLACK, "");

      //Desenha as casas
      if ( (x > 23 && y > 3) && (x < 56 && y > 3) ) { //bordas
        if ( (x > 23 && y < 20) && (x < 56 && y < 20 )) { //bordas

          if (trocaCor == 0) {
            putc(x, y, GRAY, YELLOW, "");
          }
          if (trocaCor == 1) {
            putc(x, y, GRAY, GRAY, "");
          }
        }
      }

      y ++;
      aux_y ++;

      if (aux_y >= 2) {
        trocaCor = 1 - trocaCor;
        aux_y = 0;
      }

    }

    y = 2;
    x++;
    aux_x ++;

    if (aux_x >= 4) {
      trocaCor = 1 - trocaCor;
      aux_x = 0;
    }

  }

  puts(0, 1, YELLOW, GRAY, "Jogador:");
  puts(9, 1, BLUE, GRAY, "AZUL");
  puts(0, 3, YELLOW, GRAY, "Score");
  puts(0, 4, YELLOW, GRAY, "---------");
  puts(0, 5, BLUE, GRAY, "Azul:");
  puts(0, 6, RED, GRAY, "Vermelho:");
}

//desenhaPecas(int x, int y, char cor)
//Faz o desenho das posicoes iniciais das pecas
//e tambem é utilizado para redesenhar pecas individuais
//quando necessario
void desenhaPecas(int x, int y, char cor) {

  if (x != 0 && y != 0) {

    if (cor == 'A') {
      putc (x, y, GRAY, BLUE, "");
      putc (x+1, y, GRAY, BLUE, "");
      putc (x+2, y, GRAY, BLUE, "");
      putc (x+3, y, GRAY, BLUE, "");
    }
    if (cor == 'V') {
      putc (x, y, GRAY, RED, "");
      putc (x+1, y, GRAY, RED, "");
      putc (x+2, y, GRAY, RED, "");
      putc (x+3, y, GRAY, RED, "");
    }
    if (cor == 'C') {
      putc (x, y, GRAY, GRAY, "");
      putc (x+1, y, GRAY, GRAY, "");
      putc (x+2, y, GRAY, GRAY, "");
      putc (x+3, y, GRAY, GRAY, "");
    }
  }
  else {
    //pecas azuis
    for (int l = 0; l < 12; l++) {
      for (int c = 0; c < 1; c++) {
        putc(pecasAzuis[l][c], pecasAzuis[l][c+1], GRAY, BLUE, "");
        putc( (pecasAzuis[l][c])+1, pecasAzuis[l][c+1], GRAY, BLUE, "");
        putc( (pecasAzuis[l][c])+2, pecasAzuis[l][c+1], GRAY, BLUE, "");
        putc( (pecasAzuis[l][c])+3, pecasAzuis[l][c+1], GRAY, BLUE, "");
      }
    }
    // pecas vermelhas
    for (int l = 0; l < 12; l++) {
      for (int c = 0; c < 1; c++) {
        putc(pecasVermelhas[l][c], pecasVermelhas[l][c+1], GRAY, RED, "");
        putc( (pecasVermelhas[l][c])+1, pecasVermelhas[l][c+1], GRAY, RED, "");
        putc( (pecasVermelhas[l][c])+2, pecasVermelhas[l][c+1], GRAY, RED, "");
        putc( (pecasVermelhas[l][c])+3, pecasVermelhas[l][c+1], GRAY, RED, "");
      }
    }

  }

}

//Verifica qual a cor da peca ou da casa onde o cursor estava
//pois conforme o cursor se movimenta, precisa voltar o estado anterior
//para nao ficar 'sujeira' no local onde o cursor passou
//Pode ser usado para saber qual peca esta 'na vez'
char verificaCor(int x, int y) {
  char cor = ' ';
  int found = 0;

  for (int l = 0; l < 12; l++) {
    for (int c = 0; c < 1; c++) {
      if (pecasAzuis[l][c] == x && pecasAzuis[l][c+1] == y) { cor = 'A'; found = 1;}
      if (pecasVermelhas[l][c] == x && pecasVermelhas[l][c+1] == y) { cor = 'V'; found = 1;}
      }
      if (found == 1) { break ;}
    }

    if (found == 0) { cor = 'C'; }

    return cor;
  }



int kmain(void)
{

    int x, y, posAntX, posAntY, x_sel, y_sel;
    int key;
    char cor = ' ';
    int found = -1;
    int enter = 0;    //Enter pressionado 1x = 1;

    posAntX = posAntY = x_sel = y_sel = 0;
    x = 28;
    y = 5;

    serial_init();    //inicializa a porta serial para 'escrever' no serial ( funcao prinft() )

    desenhaTela();

    desenhaPecas(0, 0, ' ');

    // puts(1, 1, GREEN, GRAY, "Mensagem de teste 2...");    //puts(posX, posY, cor_frente, cor_fundo, str_a_ser_exibida)

    while (1) {
        key = getkey();   //captura tecla digitada

        if (key == -1) {
          continue;        //se tecla for -1 (nao digitou nada) volta pro inicio do while
        }


        int pecas[1][2] = {{0, 0}};
		cor = verificaCor(x, y);

        posAntX = x;
        posAntY = y;

        if (key == KEY_UP && y > 5 && x < TABULEIRO_X) {y -= 2; x += 4;}
        if (key == KEY_DOWN && y < TABULEIRO_Y && x < TABULEIRO_X) {y += 2; x += 4;}
        if (key == KEY_RIGHT && x < TABULEIRO_X && x != 48) { x += 8; }
        if (key == KEY_LEFT && x > 24 && x != 28) { x -= 8;}
      	desenhaPecas(posAntX, posAntY, cor);
        putc(x, y, GREEN, MAGENTA, "");

        if (key == KEY_ENTER) {
          enter = 1 - enter;
          if (enter == 1) {
            x_sel = x; y_sel = y;
            printf("[X,Y] selecionado: %d,%d\n", x_sel, y_sel);
			}

		  int pecas[1][2] = {{x_sel, y_sel}};     //armazena peca a ser movida

          if (enter == 0) {
			  if (jogada == 0) {

				for (int l = 0; l < 12; l++) {
					for (int c = 0; c < 1; c++) {
						if (pecasAzuis[l][c] == pecas[0][0] && pecasAzuis[l][c+1] == pecas[0][1]) {
							pecasAzuis[l][c] = x;
							pecasAzuis[l][c+1] = y;
						}
						printf("Matriz Azul: %d,%d\n", pecasAzuis[l][c], pecasAzuis[l][c+1]);

				  }
				}
				printf("Matriz pecas: %d,%d\n", pecas[0][0], pecas[0][1]);
				printf("[X,Y] atual: %d,%d\n", x, y);
				desenhaPecas(0, 0, ' ');
				desenhaPecas(x_sel, y_sel, 'C');
				jogada = 1;
        puts(9, 1, RED, GRAY, "VERMELHO");
			  }
			  if (jogada == 1) {

			    for (int l = 0; l < 12; l++) {
					for (int c = 0; c < 1; c++) {
						if (pecasVermelhas[l][c] == pecas[0][0] && pecasVermelhas[l][c+1] == pecas[0][1]) {
							pecasVermelhas[l][c] = x;
							pecasVermelhas[l][c+1] = y;
						}
						printf("Matriz Vermelha: %d,%d\n", pecasVermelhas[l][c], pecasVermelhas[l][c+1]);

				  }
				}
				printf("Matriz pecas: %d,%d\n", pecas[0][0], pecas[0][1]);
				printf("[X,Y] atual: %d,%d\n", x, y);
				desenhaPecas(0, 0, ' ');
				desenhaPecas(x_sel, y_sel, 'C');
				jogada = 0;
        puts(9, 1, BLUE, GRAY, "AZUL");
			  }
          }
          // printf("[X,Y] selecionado: %d,%d\n", x_sel, y_sel);
          // printf("[X,Y] anterior: %d,%d\n", aux_x, aux_y);
          // printf("[X,Y] atual: %d,%d\n", x, y);
          putc(15, 15, GRAY, MAGENTA, cor);

        }


        desenhaPecas(posAntX, posAntY, cor);
        putc(x, y, GREEN, MAGENTA, "");

		}

    return 0;
}
