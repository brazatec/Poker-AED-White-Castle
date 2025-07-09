#ifndef AVL_H
#define AVL_H

#include <stdlib.h>   // para size_t, malloc, free, se precisar em inline

// Definição do nó da AVL (agora contendo info e count)
typedef struct NO {
    int info;            // fenômeno armazenado (índice da combinação)
    int count;           // quantas vezes essa combinação apareceu
    struct NO *esq;
    struct NO *dir;
    int alt;
} NO;

// Ponteiro para a árvore
typedef NO* ArvAVL;

// Protótipos da API
ArvAVL*   criarAVL(void);
void      preOrd(ArvAVL* raiz);
void      emOrd (ArvAVL* raiz);
void      posOrd(ArvAVL* raiz);

int       inserir(ArvAVL* raiz, int valor);
int       remover(ArvAVL* raiz, int valor);
int       consultarValorAVL(ArvAVL* raiz, int valor);

int       alt_NO(struct NO* no);
int       fb_NO(struct NO* no);
int       maior(int x, int y);

void      RotacaoLL(ArvAVL* raiz);
void      RotacaoRR(ArvAVL* raiz);
void      RotacaoLR(ArvAVL* raiz);
void      RotacaoRL(ArvAVL* raiz);

struct NO* buscarMenor(struct NO* atual);
void       liberaNO(struct NO* no);
void       liberaABB(ArvAVL* raiz);

#endif // AVL_H
