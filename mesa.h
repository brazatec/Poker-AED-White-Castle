#ifndef MESA_H
#define MESA_H

#include "baralho.h"     // para tp_item
#include "fila.h"
#define MAX_MESA 5   // 5 cartas serao inseridas na mesa 

//deixar legivel os numeros para melhorar a visualização
typedef enum {
    PRE_FLOP,  // (0) -> antes de revelar qualquer carta da mesa
    FLOP,      // (1) -> revela as 3 primeiras cartas comunitárias
    TURN,      // (2) -> revela a 4ª carta
    RIVER,     // (3) -> revela a 5ª carta
    SHOWDOWN   // (4) -> compara mãos
} FaseRodada;


typedef struct jogador jogador;

typedef struct mesa {
    jogador *dealer; // quem distribui na mão atual
    tp_item Total_Mesa[MAX_MESA];
    int cartas_viradas; // quantas já estão abertas
    int pote; // fichas na mesa
    FaseRodada fase;
} mesa;

//funções
mesa *criarMesa(jogador *lista);
void liberaMesa(mesa *m);
void DistribuirMesa(mesa *m, tp_fila *baralho);
void imprimeMesa(const mesa *m);
void proximaRodada(mesa *m, tp_fila *baralho);
void iniciarMesa(mesa *m);




#endif
