#include <stdio.h>
#include <stdlib.h>
#include "mesa.h"
#include "jogadores.h"
#include "fila.h"  

mesa *criarMesa(jogador *lista){
    mesa *m = malloc(sizeof(mesa));
    if (!m) return NULL;

    m->dealer = lista; // começa no primeiro da lista
    m->cartas_viradas = 0;
    m->pote = 0;
    return m;
}

void liberaMesa(mesa *m)
{
    if (!m) return;
    liberaTodosJogadores(m->dealer);  
    free(m);
}

void DistribuirMesa(mesa *m, tp_fila *baralho){
    tp_item carta;
    for(int i = 0; i < MAX_MESA; i++){
        if(removeFila(baralho, &carta)){
        m->Total_Mesa[m->cartas_viradas++] = carta;
        }
    }
}

void imprimeMesa(const mesa *m) {
    printf("Mesa: ");
    for (int i = 0; i < m->cartas_viradas; i++) {
        imprimeCarta(m->Total_Mesa[i]);
        printf(" ");
    }
    printf("\n");
}

void iniciarMesa(mesa *m) {
    m->cartas_viradas = 0;
    m->fase = PRE_FLOP;
}

void proximaRodada(mesa *m, tp_fila *baralho) {
    switch (m->fase) {
        case PRE_FLOP: 
            m->fase = FLOP; //troca a fase para a proxima
// laço para mostrar 3 cartas
// remove uma carta do baralho e coloca na proxima posição livre da mesa quando isso acontecer ++cartasviradas
            for (int i = 0; i < 3; i++) {
                if (removeFila(baralho, &m->Total_Mesa[m->cartas_viradas]))
                    m->cartas_viradas++;
            }
            break;
        case FLOP:
            m->fase = TURN;
            // revela 1 carta
            if (removeFila(baralho, &m->Total_Mesa[m->cartas_viradas]))
                m->cartas_viradas++;
            break;
        case TURN:
            m->fase = RIVER;
            if (removeFila(baralho, &m->Total_Mesa[m->cartas_viradas]))
                m->cartas_viradas++;
            break;
        case RIVER:
            m->fase = SHOWDOWN;
            // nenhuma carta nova
            break;
        case SHOWDOWN:
            // jogo encerrado ou reiniciar
            break;
    }
}
























