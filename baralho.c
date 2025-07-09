#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include "fila.h"
#include "baralho.h"
#include "jogadores.h"

#define NAIPES 4
#define VALORES 13

// Tornam-se visíveis para todo o programa:
const char *NOME_NAIPE[NAIPES] = { "♣","♦","♥","♠" };

int naipeCarta(tp_item c)  { 
    return c / VALORES; 
}

int valorCarta(tp_item c)  { 
    return c % VALORES; 
}


void inicializaBaralho(tp_fila *baralho) {
    inicializaFila(baralho); // inicializa
    for (int naipe = 0; naipe < NAIPES; naipe++) {
        for (int valor = 0; valor < VALORES; valor++) { // laço aninhado para criar as cartas
            tp_item cartas = (tp_item)(naipe * VALORES + valor); // cartas = naipe*13 + 12
            insereFila(baralho, cartas);
        }
    }
}

// embaralha as cartas usando uma fila auxiliar
void embaralhar(tp_fila *baralho){
    tp_fila aux1;
    tp_item cartas;
    inicializaFila(&aux1);
    srand((unsigned)time(NULL));
    
    // gira enquanto houver cartas no baralho
    while(!filaVazia(baralho)){
        int tam = tamanhoFila(baralho);
        int rotacoes = rand() % tam;
        
        // criar uma rotação dentro do baralho
        for(int i=0; i<rotacoes; i++){
            removeFila(baralho, &cartas);
            insereFila(baralho, cartas);
        }
        // agora move uma carta para auxiliar
        removeFila(baralho, &cartas);
        insereFila(&aux1, cartas); 
        
    } // quando acabar nao vai ter nenhuma carta no baralho so no aux
    
    *baralho = aux1; // aux vira baralho por ponteiro
}

// Strings para imprimir valor e naipe
static const char *strValores[VALORES] = {
    "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"
};
static const char *strNaipes[NAIPES] = {
    "♣", "♦", "♥", "♠"
};

// imprime o valor e o naipe em uma unica carta
void imprimeCarta(tp_item carta) {
    int valor = carta % VALORES;      
    int naipe = carta / VALORES;      
    printf("%2s%s", strValores[valor], strNaipes[naipe]);
}
 
// Imprime todos os elementos de uma fila como se fosse uma mão de n cartas.
// A fila volta exatamente como estava no final.
void imprimeBaralho(const tp_fila *baralho) {
    tp_fila copia = *baralho;
    tp_item carta;
    
while (removeFila(&copia, &carta)) {
        imprimeCarta(carta);  
        printf(" ");
    }
    printf("\n");
    
}

// retira a carta do topo do baralho
void retiraCarta(tp_fila *baralho, tp_item *carta) {
    removeFila(baralho, carta);
}


