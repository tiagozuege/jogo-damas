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

  //Info do jogo
  puts(0, 1, YELLOW, GRAY, "Jogador:");
  puts(9, 1, BLUE, GRAY, "A");
  puts(0, 3, YELLOW, GRAY, "Score");
  puts(0, 4, YELLOW, GRAY, "---------");
  puts(0, 5, BLUE, GRAY, "Azul:");
  puts(0, 6, RED, GRAY, "Vermelho:");
}

//desenhaPecas(int x, int y, char cor)
//Faz o desenho das posicoes iniciais das pecas
//e tambem é utilizado para redesenhar pecas individuais
//quando necessario
//Se os argumentos x & y == 0 & cor = ' ' entao redesenha
//todas as pecas
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

  //Funcao que avalia se jogada a ser feita
  //é valida ou nao.
  //x0 & y0 --> ponto de partida da peca
  //x1 & y1 --> casa de destino da peca
  //REGRAS:
  //--> Pecas andam na diagonal, 1 casa para frente
  //--> Peca que 'comeu' outra peca pula uma casa na diagonal
  //--> Jogador que esta na vez nao pode selecionar peca de outra cor
  //--> Jogador = 0 [Azul] / Jogador = 1 [Vermelho]
  //Retorna 1 se jogada valida [true] e 0 se jogada invalida [false]
  int validaJogada(char cor, int x0, int x1, int y0, int y1, int jogador) {

    int x2, y2, x3, y3, achouPecaAzulFrente, achouPecaAzulMeio, achouPecaVermelhaFrente, achouPecaVermelhaMeio;
    x2 = y2 = x3 = y3 = 0;
    achouPecaAzulFrente = achouPecaAzulMeio = -1;
    achouPecaVermelhaFrente = achouPecaVermelhaMeio = -1;

  	//int mov[1][2];// = {{x2, y2}};
      if (jogador == 0 && cor == 'A') {
        if ( (x0 - x1) == 4 || (x0 - x1) == -4 ) {
          if ( (y0 - y1) == -2 ) {
            //Condicao em que peca AZUL move para a ESQUERDA
  			if ( (x0 - x1) == 4) {
  				x2 = x1 - 4;
  				y2 = y1 +2;
  				printf("X2 = %d\n", x2);
  				printf("Y2 %d\n", y2);
  				int mov[1][2] = {{x2, y2}};
  				for (int l = 0; l < 12; l++) {    //atualiza posicao (x,y) da peca que se moveu
          			for (int c = 0; c < 1; c++) {
                  if (pecasAzuis[l][c] == mov[0][0] && pecasAzuis[l][c+1] == mov[0][1]) {
                    achouPecaAzulFrente = 1;
                    printf("Achou azul-frente\n");
                  }
                  if (pecasVermelhas[l][c] == mov[0][0] && pecasVermelhas[l][c+1] == mov[0][1]) {
                    achouPecaVermelhaFrente = 1;
                    printf("Achou vermelha-frente\n");
                  }
        					// printf("Matriz Azul: %d,%d\n", pecasAzuis[l][c], pecasAzuis[l][c+1]);
          				// if ( (pecasAzuis[l][c] == mov[0][0] && pecasAzuis[l][c+1] == mov[0][1]) && (pecasAzuis[l][c] == x1 && pecasAzuis[l][c+1] == y1) ) {
      						// 	printf("1o. Azul");
      						// 	return 0;
          				// }

          			}
      		}
  				for (int l = 0; l < 12; l++) {    //atualiza posicao (x,y) da peca que se moveu
          			for (int c = 0; c < 1; c++) {
                  if (pecasAzuis[l][c] == x1 && pecasAzuis[l][c+1] == y1) {
                    achouPecaAzulMeio = 1;
                    printf("Achou azul-meio\n");
                  }
                  if (pecasVermelhas[l][c] == x1 && pecasVermelhas[l][c+1] == y1) {
                    achouPecaVermelhaMeio = 1;
                    printf("Achou vermelha-meio\n");
                  }
      						// printf("Matriz Vermelha: %d,%d\n", pecasVermelhas[l][c], pecasVermelhas[l][c+1]);
          				// if ( (pecasVermelhas[l][c] == mov[0][0] && pecasVermelhas[l][c+1] == mov[0][1]) && (pecasVermelhas[l][c] == x1 && pecasVermelhas[l][c+1] == y1) ) {
      						// 	printf("2o. Azul");
      						// 	return 0;
          				// }

          			}
      		}
          if ( (achouPecaVermelhaFrente == 1) && (achouPecaVermelhaMeio == 1) ) { return 0; }
          if ( (achouPecaVermelhaFrente == 1) && (achouPecaAzulMeio == 1) ) { return 0; }
          if ( (achouPecaAzulFrente == 1) && (achouPecaAzulMeio == 1) ) { return 0; }
          if ( (achouPecaAzulFrente == 1) && (achouPecaVermelhaMeio == 1) ) { return 0; }
          if (achouPecaAzulMeio == 1) { return 0; }   //*****

  			}
        //Condicao em que peca AZUL move para a DIREITA
  			if ( (x0 - x1) == -4) {
  				x3 = x1 + 4;
  				y3 = y1 +2;
  				printf("X3 = %d\n", x3);
  				printf("Y3 %d\n", y3);
  				int mov2[1][2] = {{x3, y3}};
  				for (int l = 0; l < 12; l++) {    //atualiza posicao (x,y) da peca que se moveu
          			for (int c = 0; c < 1; c++) {
                  if (pecasAzuis[l][c] == mov2[0][0] && pecasAzuis[l][c+1] == mov2[0][1]) {
                    achouPecaAzulFrente = 1;
                    printf("Achou azul-frente\n");
                  }
                  if (pecasVermelhas[l][c] == mov2[0][0] && pecasVermelhas[l][c+1] == mov2[0][1]) {
                    achouPecaVermelhaFrente = 1;
                    printf("Achou vermelha-frente\n");
                  }
      						// printf("Matriz Azul: %d,%d\n", pecasAzuis[l][c], pecasAzuis[l][c+1]);
          				// if ( (pecasAzuis[l][c] == mov2[0][0] && pecasAzuis[l][c+1] == mov2[0][1]) && (pecasAzuis[l][c] == x1 && pecasAzuis[l][c+1] == y1) ) {
      						// 	printf("3o. Azul");
      						// 	return 0;
          				// }

          			}
      		}
  				for (int l = 0; l < 12; l++) {    //atualiza posicao (x,y) da peca que se moveu
          			for (int c = 0; c < 1; c++) {
                  if (pecasAzuis[l][c] == x1 && pecasAzuis[l][c+1] == y1) {
                    achouPecaAzulMeio = 1;
                    printf("Achou azul-meio\n");
                  }
                  if (pecasVermelhas[l][c] == x1 && pecasVermelhas[l][c+1] == y1) {
                    achouPecaVermelhaMeio = 1;
                    printf("Achou vermelha-meio\n");
                  }
      						// printf("Matriz Vermelha: %d,%d\n", pecasVermelhas[l][c], pecasVermelhas[l][c+1]);
          				// if ( (pecasVermelhas[l][c] == mov2[0][0] && pecasVermelhas[l][c+1] == mov2[0][1]) && (pecasVermelhas[l][c] == x1 && pecasVermelhas[l][c+1] == y1) ) {
      						// 	printf("4o. Azul");
      						// 	return 0;
          				// }

          			}
      		}
          if ( (achouPecaVermelhaFrente == 1) && (achouPecaVermelhaMeio == 1) ) { return 0; }
          if ( (achouPecaVermelhaFrente == 1) && (achouPecaAzulMeio == 1) ) { return 0; }
          if ( (achouPecaAzulFrente == 1) && (achouPecaAzulMeio == 1) ) { return 0; }
          if ( (achouPecaAzulFrente == 1) && (achouPecaVermelhaMeio == 1) ) { return 0; }
          if (achouPecaAzulMeio == 1) { return 0; }   //*****

  			}
            return 1;
          }
        }
      }

      if (jogador == 1 && cor == 'V') {
        printf("X1 (DESTINO) => %d", x1);
        printf("Y1 (DESTINO) => %d", y1);
        if ( (x0 - x1) == 4 || (x0 - x1) == -4 ) {
          if ( (y0 - y1) == 2 ) {
            //Condicao em que peca VERMELHA move para a ESQUERDA
      			if ( (x0 - x1) == 4) {
      				x2 = x1 - 4;
      				y2 = y1 -2;
      				printf("X2 = %d\n", x2);
      				printf("Y2 %d\n", y2);
      				int mov[1][2] = {{x2, y2}};
      				for (int l = 0; l < 12; l++) {    //atualiza posicao (x,y) da peca que se moveu
              			for (int c = 0; c < 1; c++) {
                      if (pecasAzuis[l][c] == mov[0][0] && pecasAzuis[l][c+1] == mov[0][1]) {
                        achouPecaAzulFrente = 1;
                        printf("Achou azul-frente\n");
                      }
                      if (pecasVermelhas[l][c] == mov[0][0] && pecasVermelhas[l][c+1] == mov[0][1]) {
                        achouPecaVermelhaFrente = 1;
                        printf("Achou vermelha-frente\n");
                      }
          						// printf("Matriz Azul: %d,%d\n", pecasAzuis[l][c], pecasAzuis[l][c+1]);
              				// if ( (pecasAzuis[l][c] == mov[0][0] && pecasAzuis[l][c+1] == mov[0][1]) && (pecasAzuis[l][c] == x1 && pecasAzuis[l][c+1] == y1) ) {
          						// 	printf("1o. Vermelho");
          						// 	return 0;
              				// }

              			}
          		}
              for (int l = 0; l < 12; l++) {
                for (int c = 0; c < 1; c++) {
                  if (pecasAzuis[l][c] == x1 && pecasAzuis[l][c+1] == y1) {
                    achouPecaAzulMeio = 1;
                    printf("Achou azul-meio\n");
                  }
                  if (pecasVermelhas[l][c] == x1 && pecasVermelhas[l][c+1] == y1) {
                    achouPecaVermelhaMeio = 1;
                    printf("Achou vermelha-meio\n");
                  }
                }
              }
              if ( (achouPecaVermelhaFrente == 1) && (achouPecaVermelhaMeio == 1) ) { return 0; }
              if ( (achouPecaVermelhaFrente == 1) && (achouPecaAzulMeio == 1) ) { return 0; }
              if ( (achouPecaAzulFrente == 1) && (achouPecaAzulMeio == 1) ) { return 0; }
              if ( (achouPecaAzulFrente == 1) && (achouPecaVermelhaMeio == 1) ) { return 0; }
              if (achouPecaVermelhaMeio == 1) { return 0; }

        				// for (int l = 0; l < 12; l++) {    //atualiza posicao (x,y) da peca que se moveu
              	// 		for (int c = 0; c < 1; c++) {
          			// 			printf("Matriz Vermelha: %d,%d\n", pecasVermelhas[l][c], pecasVermelhas[l][c+1]);
              	// 			if ( (pecasVermelhas[l][c] == mov[0][0] && pecasVermelhas[l][c+1] == mov[0][1]) && (pecasVermelhas[l][c] == x1 && pecasVermelhas[l][c+1] == y1) ) {
          			// 				printf("2o. Vermelho");
          			// 				return 0;
              	// 			}
                //     }
                //   }
                        // if ( (pecasVermelhas[l][c] == mov[0][0] && pecasVermelhas[l][c+1] == mov[0][1]) && (pecasAzuis[l][c] == x1 && pecasAzuis == y1) ) {
                        //   printf("2o. Vermelho 2");
                        //   return 0;
      			}
            //Condicao em que peca VERMELHA move para a DIREITA
  			if ( (x0 - x1) == -4) {
  				x3 = x1 + 4;
  				y3 = y1 -2;
  				printf("X3 = %d\n", x3);
  				printf("Y3 %d\n", y3);
  				int mov2[1][2] = {{x3, y3}};
  				for (int l = 0; l < 12; l++) {    //atualiza posicao (x,y) da peca que se moveu
          			for (int c = 0; c < 1; c++) {
                  if (pecasAzuis[l][c] == mov2[0][0] && pecasAzuis[l][c+1] == mov2[0][1]) {
                    achouPecaAzulFrente = 1;
                    printf("Achou azul-frente\n");
                  }
                  if (pecasVermelhas[l][c] == mov2[0][0] && pecasVermelhas[l][c+1] == mov2[0][1]) {
                    achouPecaVermelhaFrente = 1;
                    printf("Achou vermelha-frente\n");
                  }
        					// 	printf("Matriz Azul: %d,%d\n", pecasAzuis[l][c], pecasAzuis[l][c+1]);
            			// 	if ( (pecasAzuis[l][c] == mov2[0][0] && pecasAzuis[l][c+1] == mov2[0][1]) && (pecasAzuis[l][c] == x1 && pecasAzuis[l][c+1] == y1) ) {
        					// 		printf("3o. Vermelho");
        					// 		return 0;
          				// }

          			}
      		}
  				for (int l = 0; l < 12; l++) {    //atualiza posicao (x,y) da peca que se moveu
          			for (int c = 0; c < 1; c++) {

                  if (pecasAzuis[l][c] == x1 && pecasAzuis[l][c+1] == y1) {
                    achouPecaAzulMeio = 1;
                    printf("Achou azul-meio\n");
                  }
                  if (pecasVermelhas[l][c] == x1 && pecasVermelhas[l][c+1] == y1) {
                    achouPecaVermelhaMeio = 1;
                    printf("Achou vermelha-meio\n");
                  }
        						// printf("Matriz Vermelha: %d,%d\n", pecasVermelhas[l][c], pecasVermelhas[l][c+1]);
            				// if ( (pecasVermelhas[l][c] == mov2[0][0] && pecasVermelhas[l][c+1] == mov2[0][1]) && (pecasVermelhas[l][c] == x1 && pecasVermelhas[l][c+1] == y1) ) {
        						// 	printf("4o. Vermelho");
        						// 	return 0;
            				// }

          			}
      		}
          if ( (achouPecaVermelhaFrente == 1) && (achouPecaVermelhaMeio == 1) ) { return 0; }
          if ( (achouPecaVermelhaFrente == 1) && (achouPecaAzulMeio == 1) ) { return 0; }
          if ( (achouPecaAzulFrente == 1) && (achouPecaAzulMeio == 1) ) { return 0; }
          if ( (achouPecaAzulFrente == 1) && (achouPecaVermelhaMeio == 1) ) { return 0; }
          if (achouPecaVermelhaMeio == 1) { return 0; }

  			}
            return 1;
          }
        }
      }

      return 0;   //Nenhuma condicao valida entao retorna 0
  }



int kmain(void)
{

    int x, y, posAntX, posAntY, x_sel, y_sel;
    int key;
    char cor = ' ';
    char cor_sel = ' ';
    int found = -1;
    int enter = 0;    //Enter pressionado 1x = 1;

    posAntX = posAntY = x_sel = y_sel = 0;
    x = 28;
    y = 5;

    serial_init();    //inicializa a porta serial para 'escrever' no terminal ( funcao prinft() )

    desenhaTela();

    desenhaPecas(0, 0, ' ');
    printf("INICIO: Jogador => %d\n", jogada);
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

        //Tecla enter seleciona a origem e destino da peca
        //Enter (1) => seleciona a peca (MODO SELECAO)
        //Enter (0) => seleciona o destino (MODO MOVIMENTO)
        if (key == KEY_ENTER) {
          enter = 1 - enter;    //alterna entre 1 / 0

          if (enter == 1) {   //se enter == 1 entao esta no modo SELECAO
            x_sel = x; y_sel = y;   //pega a posicao da peca selecionada e gurda em x_sel e y_sel
            cor_sel = verificaCor(x_sel, y_sel);
            printf("[X,Y] selecionado: %d,%d\n", x_sel, y_sel);
            puts(1, 23, GRAY, GRAY, "                  ");
    			}

    		  int pecas[1][2] = {{x_sel, y_sel}};     //armazena em matriz peca a ser movida

          if (enter == 0) {   //se enter == 0 entao esta no modo MOVIMENTO
            if ( validaJogada(cor_sel, x_sel, x, y_sel, y, jogada) == 0 ) {
              // printf("Cor:%c\nx_sel:%d\nx:%d\ny_sel:%d\ny:%d\njogador:%d\n", cor_sel, x_sel, x, y_sel, y, jogada);
              puts(1, 23, MAGENTA, GRAY, "Jogada Invalida!!");
            }
            else {
      			  if (jogada == 0) {   //Se jogada == 0 -> vez do Azul

        				for (int l = 0; l < 12; l++) {    //atualiza posicao (x,y) da peca que se moveu
        					for (int c = 0; c < 1; c++) {
        						if (pecasAzuis[l][c] == pecas[0][0] && pecasAzuis[l][c+1] == pecas[0][1]) {
        							pecasAzuis[l][c] = x;
        							pecasAzuis[l][c+1] = y;
        						}
        						// printf("Matriz Azul: %d,%d\n", pecasAzuis[l][c], pecasAzuis[l][c+1]);
        				  }
        				}

        				// printf("Matriz pecas: %d,%d\n", pecas[0][0], pecas[0][1]);
        				// printf("[X,Y] atual: %d,%d\n", x, y);
        				desenhaPecas(0, 0, ' ');    //redesenha as pecas de acordo com a matriz atualizada
        				desenhaPecas(x_sel, y_sel, 'C');  //desenha posicao da peca que se moveu em cinza
        				// jogada = 1;   //troca de jogador
                putc(9, 1, GRAY, GRAY, "");
                puts(9, 1, RED, GRAY, "V");
        			  }
        			  if (jogada == 1) {
        			    for (int l = 0; l < 12; l++) {
          					for (int c = 0; c < 1; c++) {
          						if (pecasVermelhas[l][c] == pecas[0][0] && pecasVermelhas[l][c+1] == pecas[0][1]) {
          							pecasVermelhas[l][c] = x;
          							pecasVermelhas[l][c+1] = y;
          						}
          						// printf("Matriz Vermelha: %d,%d\n", pecasVermelhas[l][c], pecasVermelhas[l][c+1]);

          				  }
          				}

          				// printf("Matriz pecas: %d,%d\n", pecas[0][0], pecas[0][1]);
          				// printf("[X,Y] atual: %d,%d\n", x, y);
          				desenhaPecas(0, 0, ' ');
          				desenhaPecas(x_sel, y_sel, 'C');
          				// jogada = 0;   //troca de jogador
                  putc(9, 1, GRAY, GRAY, "");
                  puts(9, 1, BLUE, GRAY, "A");
        			  }

                jogada = 1 - jogada;
                printf("Jogador => %d\n", jogada);
              }
          }

          putc(15, 15, GRAY, MAGENTA, cor);   //Teste para ver a cor que esta selecionando
        }


        desenhaPecas(posAntX, posAntY, cor);  //necessario para redesenhar onde cursor passou
        putc(x, y, GREEN, MAGENTA, "");       //coloca o cursor na posicao selecionada

		}

    return 0;
}
