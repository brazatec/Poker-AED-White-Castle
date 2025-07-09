#include <stdio.h>
#include <stdlib.h>

#include "fila.h"
#include "jogadores.h"
#include "baralho.h" 
#include "combinacoes.h"
#include "mesa.h"

#define NUM 25
#define FICHASINI 1000
#define CARTAS_MAO 2


// aloca um espaço dinamico para o jogador que tem ficha e nome
jogador* criarjogador(char *nome, int fichas){
    
    // aloca na memoria para um novo jogador
    jogador* novo = (jogador*) malloc(sizeof(jogador)); 
    if(!novo) return NULL; // retorna NULL em erro
    
    int i=0;
    while(nome[i] != '\0' && i < NUM -1){ // enquanto o caracter nao for vazio. O -1 é pq so tem 24 caracteres o 25 é o vazio
        novo->nome[i] = nome[i];
        i++;
    }
    novo->nome[i] = '\0'; // colocar o vazio para garantir o fim da string
    novo->fichas = fichas; // vai ser 1000 se dar ruim coloca 1000 aqui
    novo->proximo = NULL;  // colocar o ponteiro proximo como nulo

    return novo;  // retorna o ponteiro pronto
}


// insere o jogador na lista circular
jogador* inserirjogador(jogador* ult,char* nome, int fichas){
    // aloca espaço na memoria
    jogador *novo = criarjogador(nome,fichas); // define que o novo nó criado é o player
    if(!novo) return ult; // se nao funcionar o novo nó retorna para o ponteiro original(ult)
    
    // aloca vetor para a mão
    novo->mao = malloc(sizeof(tp_item) * CARTAS_MAO);
    if (!novo->mao) {
        free(novo);
        return ult;
    }
    novo->numCartas = 0;

    
    // se nao tiver nenhum no de lista o ponteiro aponta para ele mesmo
    if(!ult){
        novo->proximo=novo;
        return novo; // return novo inves de ult, pq ja como é o unico elemento ele é o ultimo
    }
    
    // transformar em circular
    novo->proximo = ult ->proximo; // faz o o novo apontar para o antigo primeiro
    ult->proximo = novo; // o proximo do ultimo é o 1
    return novo;
}

// imprime a mao do jogador
void imprimeMao(jogador *j) {
    printf("Mão de %s: ", j->nome);
    for (int i = 0; i < j->numCartas; i++) {
        tp_item c = j->mao[i];
        printf("%s%d ", NOME_NAIPE[naipeCarta(c)], valorCarta(c) + 1);
    }
    printf("\n");
    
}

// libera somente 1 jogador
void liberaJogador(jogador *j) {
    free(j->mao); // libera vetor de cartas
    free(j); // libera struct
}

// libera toda a lista circular de jogadores
void liberaTodosJogadores(jogador *lista) {
    if (!lista) return;
    jogador *p = lista->proximo;

    // “quebra” o ciclo para facilitar o laço
    lista->proximo = NULL;

    // enquanto houver nós
    while (p) {
        jogador *next = p->proximo;
        liberaJogador(p);  // chama a função existente
        p = next;
    }
}

void avaliaMelhorJogada(jogador *j, mesa *m) {
    j->melhorComb = melhorDaJogada(
        j->mao, j->numCartas,
        m->Total_Mesa, m->cartas_viradas
    );
}
