#ifndef RODADA_H
#define RODADA_H

#include "fila.h"
#include "jogadores.h"
#include <stdio.h>

void realizarRodada(jogador *lista, tp_fila *baralho);
void distribuirPote(mesa *m, jogador **lista);
jogador *removerSemFichas(jogador *lista);

#endif 
