#ifndef JOGADORES_H
#define JOGADORES_H

#include "fila.h"    
#include "baralho.h"
#include "combinacoes.h"
#include <stdbool.h>

#define NUM 25
#define FICHASINI 1000
#define CARTAS_MAO 2 

typedef struct mesa mesa;

typedef struct jogador {
    char nome[NUM];    // nome do jogador
    int fichas;       // fichas iniciais
    tp_item *mao;          // vetor dinâmico de cartas
    int numCartas;    // quantas cartas tem
    struct jogador *proximo; // lista circular
    Comb melhorComb;    // avaliar melhorCombinação
    bool ativo;         //quando acaba a rodada de aposta
    bool all_in;      //all win
    int apostaAtual;  //quanto apostou
} jogador;

// cria struct e copia nome/fichas
jogador* criarjogador(char *nome, int fichas);
// insere na lista circular e aloca mão
jogador* inserirjogador(jogador *ult, char *nome, int fichas);
// imprime mão do jogador
void imprimeMao(jogador *j);
// libera memória de 1 jogador
void liberaJogador(jogador *j);
//libera todos os jogadores
void liberaTodosJogadores(jogador *lista);
// ve qual é a melhor combinação
void avaliaMelhorJogada(jogador *j, mesa *m);


#endif
