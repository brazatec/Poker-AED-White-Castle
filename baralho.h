#ifndef BARALHO_H
#define BARALHO_H

#include "fila.h"

#define NAIPES   4
#define VALORES 13

// inicializa fila com 52 cartas 
void inicializaBaralho(tp_fila *baralho);
// embaralha rodando cartas aleatoriamente
void embaralhar(tp_fila *baralho);
//imprime todos os elementos de uma fila como se fosse uma mão de n cartas
void imprimeBaralho(const tp_fila *baralho);
// retira uma carta do baralho
void retiraCarta(tp_fila *baralho, tp_item *carta);
// imprime o valor e o naipe em uma unica carta
void imprimeCarta(tp_item carta);

// nomes e funções auxiliares
extern const char *NOME_NAIPE[NAIPES];
int naipeCarta(tp_item c);
int valorCarta(tp_item c);

#endif
