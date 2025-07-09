#ifndef COMBINACOES_H
#define COMBINACOES_H

#include "baralho.h"

// tipos de mão, do mais fraco ao mais forte
typedef enum {
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH,
    ROYAL_FLUSH,       
} TipoComb;

// struct com tipo de mão e valores para desempate (ex.: ranks das cartas)
typedef struct {
    TipoComb tipo;
    int ranks[5];
} Comb;

// avalia exatamente 5 cartas
Comb avaliar5(tp_item cartas[5]);

// compara duas cartas
int compararComb(const Comb *a, const Comb *b);

// dado vetor de hole cards (numCartas = 2) e vetor de mesa (cartas_viradas ≤ 5),
// gera todas as combinações de 5 cartas e retorna a melhor
Comb melhorDaJogada(tp_item *mao, int nCartas, tp_item *mesa, int nMesa);

#endif
