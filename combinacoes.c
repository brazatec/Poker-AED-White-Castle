#include "combinacoes.h"
#include "baralho.h"

#include <stdlib.h>   // para qsort
#include <string.h>
#include <stdbool.h>
#include "combinacoes.h"


// Função de comparação para qsort
static int comparar_decrescente(const void *a, const void *b) {
    int va = *(int *)a;
    int vb = *(int *)b;
    return vb - va;  // se vb > va, retorna positivo → vb antes de va
}

Comb avaliar5(tp_item cartas[5]) {
    Comb resultado;
    int valores[5], naipes[5];

    // 1) Extrai valores e naipes
    for (int i = 0; i < 5; i++) {
        tp_item c = cartas[i];
        naipes[i] = naipeCarta(c);
        int v = valorCarta(c);        // 0..12
        valores[i] = (v == 0 ? 14 : v + 1); // mapeia Ás para 14
    }

    // 2) Ordena valores em ordem decrescente usando qsort
    qsort(valores, 5, sizeof(int), comparar_decrescente);

    // 3) Verifica flush (mesmo naipe)
    bool flush = true;
    for (int i = 1; i < 5; i++) {
        if (naipes[i] != naipes[0]) {
            flush = false;
            break;
        }
    }

    // 4) Verifica sequência (straight)
    bool sequencia = true;
    for (int i = 0; i < 4; i++) {
        if (valores[i] != valores[i + 1] + 1) {
            sequencia = false;
            break;
        }
    }
    
    // Checa A-2-3-4-5
    if (!sequencia) {
        sequencia = (valores[0] == 14 && valores[1] == 5 && valores[2] == 4 && valores[3] == 3 && valores[4] == 2);
    }

    // 5) Conta quantas cartas de cada valor
    int contagem[15] = {0};
    for (int i = 0; i < 5; i++) {
        contagem[valores[i]]++;
    }

    // 6) Identifica pares, trincas e quadras
    int quadra = 0, trinca = 0, par1 = 0, par2 = 0;
    for (int v = 14; v >= 2; v--) {
        if (contagem[v] == 4) quadra = v;
        else if (contagem[v] == 3) trinca = v;
        else if (contagem[v] == 2) {
            if (par1 == 0) par1 = v;
            else if (par2 == 0) par2 = v;
        }
    }

    // 7) Decide tipo de mão
    if (sequencia && flush && valores[0] == 14) {
        resultado.tipo = ROYAL_FLUSH;
    } else if (sequencia && flush) {
        resultado.tipo = STRAIGHT_FLUSH;
        resultado.ranks[0] = valores[0];
    } else if (quadra) {
        resultado.tipo = FOUR_OF_A_KIND;
        resultado.ranks[0] = quadra;
    } else if (trinca && par1 > 0) {
        resultado.tipo = FULL_HOUSE;
        resultado.ranks[0] = trinca;
        resultado.ranks[1] = par1;
    } else if (flush) {
        resultado.tipo = FLUSH;
    } else if (sequencia) {
        resultado.tipo = STRAIGHT;
        resultado.ranks[0] = valores[0];
    } else if (trinca) {
        resultado.tipo = THREE_OF_A_KIND;
        resultado.ranks[0] = trinca;
    } else if (par1 > 0 && par2 > 0) {
        resultado.tipo = TWO_PAIR;
        resultado.ranks[0] = par1;
        resultado.ranks[1] = par2;
    } else if (par1 > 0) {
        resultado.tipo = ONE_PAIR;
        resultado.ranks[0] = par1;
    } else {
        resultado.tipo = HIGH_CARD;
    }

    // 8) Preenche ranks para desempate (valores em ordem)
    for (int i = 0; i < 5; i++) {
        resultado.ranks[i] = valores[i];
    }

    return resultado;
}

int compararComb(const Comb *a, const Comb *b) {
    if (a->tipo != b->tipo)
        return (int)a->tipo - (int)b->tipo;
    for (int i = 0; i < 5; i++) {
        if (a->ranks[i] != b->ranks[i])
            return a->ranks[i] - b->ranks[i];
    }
    return 0;
}

Comb melhorDaJogada(tp_item mao[], int numCartas, tp_item mesa[], int cartas_viradas) {
    tp_item todas[7];
    memcpy(todas, mao, numCartas * sizeof(tp_item));
    memcpy(todas + numCartas, mesa, cartas_viradas * sizeof(tp_item));

    Comb melhor;
    melhor.tipo = HIGH_CARD;
    for (int i = 0; i < 5; i++) melhor.ranks[i] = 0;
    tp_item selecao[5];

    // Testa todas as combinações de 5 cartas em 7
    for (int i = 0; i < 7; i++) {
        for (int j = i + 1; j < 7; j++) {
            for (int k = j + 1; k < 7; k++) {
                for (int l = k + 1; l < 7; l++) {
                    for (int m = l + 1; m < 7; m++) {
                        selecao[0] = todas[i];
                        selecao[1] = todas[j];
                        selecao[2] = todas[k];
                        selecao[3] = todas[l];
                        selecao[4] = todas[m];
                        Comb atual = avaliar5(selecao);
                        if (compararComb(&atual, &melhor) > 0) {
                            melhor = atual;
                        }
                    }
                }
            }
        }
    }
    return melhor;
}