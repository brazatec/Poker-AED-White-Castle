#include "aposta.h"
#include <stdio.h>

// Vai zerar a aposta de cada jogador, marcar todos como ativos e tirar o all-in
void inicializaApostas(jogador *lista) {
    jogador *at = lista;
    do {
        at->apostaAtual = 0; // pode zerado
        at->ativo = true;
        at->all_in = false;
        at = at->proximo; // passa pro próximo na lista circular
    } while (at != lista); // repete até voltar ao início
}

void rodadaApostas(mesa *m, jogador *lista) {
    int highestBet = 0; // guarda a maior aposta feita até agora
    inicializaApostas(lista);

    // começa quem esta a esquerda do dealer
    jogador *at = m->dealer->proximo;
    jogador *lastToAct = m->dealer; // quem definiu a aposta mais recente
    bool firstPass = true; // garante que todos joguem pelo menos uma vez

    while (firstPass || at != lastToAct) {
        if (at->ativo) {
            printf("\n%s: fichas=%d, já apostou=%d, pote=%d, maior aposta=%d\n",
                   at->nome, at->fichas, at->apostaAtual, m->pote, highestBet);
            printf("Ação? (c)all, (r)aise, (f)old: ");
            char acao;
            scanf(" %c", &acao);

        // Fold
            if (acao == 'f') {
                at->ativo = false;
                printf("%s desistiu.\n", at->nome);
            }
        
        // Call 
            else if (acao == 'c') {
                int callAmt = highestBet - at->apostaAtual;
            if (callAmt > at->fichas) callAmt = at->fichas;
            // não pode apostar mais do que tem
            
                at->fichas -= callAmt;
                at->apostaAtual += callAmt;
                m->pote += callAmt;
                printf("%s deu call de %d.\n", at->nome, callAmt);
                
            //se todas as fichas acabarem = allwin    
            if (at->fichas == 0) {
                at->all_in = true;
                printf("%s está all-in!\n", at->nome);
                }
            }
            
        // Raise
            else if (acao == 'r') {
                printf("Quanto quer raise (além de igualar)? ");
                int raiseAmt;
                scanf("%d", &raiseAmt);
            
            // calcula    
            int needed = (highestBet - at->apostaAtual) + raiseAmt;
            if (needed > at->fichas) needed = at->fichas; // nao pode apostar mais que tem
            
                at->fichas -= needed;
                at->apostaAtual += needed;
                highestBet = at->apostaAtual; // atualiza a nova maior aposta
                m->pote += needed;
                lastToAct = at;   // garante que todo mundo tenha chance de responder ao raise
                printf("%s aumentou para %d.\n", at->nome, highestBet);
            //allwin dnv    
            if (at->fichas == 0) {
                at->all_in = true;
                printf("%s está all-in!\n", at->nome);
                
            }
        }
        at = at->proximo;
        firstPass = false;
        }
    }
}

