#include <stdio.h>
#include <stdlib.h> 

#include "jogadores.h"
#include "mesa.h"
#include "rodada.h"
#include "aposta.h"
#include "combinacoes.h"

    void distribuirPote(mesa *m, jogador **lista) {
      if (!*lista) return;
// pega a melhor combinação já calculada em melhorComb
      Comb best = (*lista)->melhorComb;
      jogador *at = (*lista)->proximo;
      while (at != *lista) {
          if (compararComb(&at->melhorComb, &best) > 0) 
          best = at->melhorComb;
         at = at->proximo;
        }

 // conta quantos empatam com essa combinação
     int nwin = 0;
     at = *lista;
     do {
        if (compararComb(&at->melhorComb, &best) == 0)
             nwin++;
         at = at->proximo;
     } while (at != *lista);

// divide o pote e dá sobras 1 a 1
     int share = m->pote / nwin;
     int rem   = m->pote % nwin;
     at = *lista;
     do {
         if (compararComb(&at->melhorComb, &best) == 0) {
             int ganho = share + (rem>0 ? 1:0);
             at->fichas += ganho;
             if (rem>0) rem--;
             printf("%s ganhou %d fichas!\n", at->nome, ganho);
         }
         at = at->proximo;
    } while (at != *lista);

    m->pote = 0;
 }

 jogador *removerSemFichas(jogador *lista) {
    if (!lista) return NULL;
    jogador *ant = NULL;
    jogador *at  = lista;
    jogador *ini = lista;

    do {
         jogador *prox = at->proximo;
         if (at->fichas <= 0) {
             printf("%s saiu do jogo (0 fichas).\n", at->nome);
             if (ant)        ant->proximo = prox;
             if (at == ini) ini = prox;
             free(at);
         } else {
             ant = at;
         }
         at = prox;
     } while (at != ini);

     return ini;
 }

void realizarRodada(jogador *lista, tp_fila *baralho) {
// Cria e inicia a mesa
    mesa *m = criarMesa(lista);
    iniciarMesa(m);

    jogador *at = lista;
// Distribuir cartas nao viradas
    for (int c = 0; c < CARTAS_MAO; c++) {
        at = lista;
        do {
            tp_item carta;
            if (removeFila(baralho, &carta))
                at->mao[at->numCartas++] = carta;
            at = at->proximo;
        } while (at != lista);
    }
    
    printf("\n-- Cartas dos jogadores (hole cards) --\n");
    at = lista;
    do {
        imprimeMao(at);      
        at = at->proximo;
    } while (at != lista);
    printf("\n");
    
// PRÉ-FLOP    
    printf("=== PRE-FLOP ===\n");
    rodadaApostas(m, lista);
    printf("\n");


// FLOP
    printf("\n");
    printf("=== FLOP ===\n");
    proximaRodada(m, baralho);
    imprimeMesa(m);
    rodadaApostas(m, lista);
    printf("\n");

// TURN
    printf("=== TURN ===\n");
    proximaRodada(m, baralho);
    imprimeMesa(m);
    rodadaApostas(m, lista);
    printf("\n");

// RIVER
    printf("=== RIVER ===\n");
    proximaRodada(m, baralho);
    imprimeMesa(m);
    rodadaApostas(m, lista);
    printf("\n");

// aponta para o primeiro dnv
    at = lista;

// SHOWDOWN avalia e armazena melhor combinação de cada jogador
    do {
        avaliaMelhorJogada(at, m);
        at = at->proximo;
    } while (at != lista);
    
    distribuirPote(m, &lista);
    lista = removerSemFichas(lista);

// determina vencedor
    jogador *vencedor = lista;
    at = lista->proximo;
    do {
        if (compararComb(&at->melhorComb, &vencedor->melhorComb) > 0)
            vencedor = at;
        at = at->proximo;
    } while (at != lista);

    printf("\nVencedor da rodada: %s\n", vencedor->nome);
    
    static const char *nomeCombinacoes[] = {
    "Carta Alta",      
    "Um Par",          
    "Dois Pares",      
    "Trinca",          
    "Sequência",       
    "Flush",          
    "Full House",      
    "Quadra",          
    "Straight Flush",  
    "Royal Flush"      
};
    
    printf("Ele ganhou com: %s\n", nomeCombinacoes[vencedor->melhorComb.tipo]);
    liberaMesa(m);
}