#include <stdio.h>
#include <stdlib.h>
#include "armazenamento.h"
#include "AVL.h"

static ArvAVL *tree = NULL;
static FILE *fp = NULL;

void initStats(const char *arquivo_txt) {
    tree = criarAVL();
    fp = fopen(arquivo_txt, "w");
    if (!fp) { perror("fopen"); exit(1); }
}

void registarJogada(int tipoComb) {
    // 1) escreve no arquivo
    fprintf(fp, "%d\n", tipoComb);
    // 2) insere na árvore (ou incrementa se já existir)
    inserir(tree, tipoComb);
}

// percusa em-ordem e imprime info + count
static void _printInOrder(ArvAVL *r, const char *nomes[]) {
    if (!r || !*r) return;
    _printInOrder(&((*r)->esq), nomes);
    printf("%s: %d vezes\n",
           nomes[(*r)->info],
           (*r)->count);
    _printInOrder(&((*r)->dir), nomes);
}

void mostrarEstatisticas(void) {
    // vetor de strings com os nomes das combinações
    static const char *nomes[] = {
      "Carta Alta", "Um Par", "Dois Pares", "Trinca",
      "Sequência", "Flush", "Full House", "Quadra",
      "Straight Flush", "Royal Flush"
    };
    printf("\n=== Estatísticas de Combinações ===\n");
    _printInOrder(tree, nomes);
}

void closeStats(void) {
    if (fp) fclose(fp);
    liberaABB(tree);
}
