#ifndef APOSTA_H
#define APOSTA_H

#include "mesa.h"
#include "jogadores.h"

// zera apostaAtual e marca todos como ativos
void inicializaApostas(jogador *lista);
// executa o ciclo de apostas até ninguém levantar mais
void rodadaApostas(mesa *m, jogador *lista);

#endif
