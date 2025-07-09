#include <stdio.h>
#include <stdlib.h>

#include "fila.h"

void inicializaFila(tp_fila *f) {
    f->ini = f->fim = MAX-1;
}

bool filaVazia(const tp_fila *f){
    return (f->ini == f->fim);
}

static int proximo(int pos){
    return (pos == MAX-1 ? 0 : pos + 1);
}

bool filaCheia(const tp_fila *f){
    return (proximo(f->fim) == f->ini);
}

bool insereFila(tp_fila *f, tp_item e){
    if (filaCheia(f)) return false;
    f->fim = proximo(f->fim);
    f->item[f->fim] = e;
    return true;
}

bool removeFila(tp_fila *f, tp_item *e){
    if (filaVazia(f)) return false;
    f->ini = proximo(f->ini);
    *e = f->item[f->ini];
    return true;
}

int tamanhoFila(const tp_fila *f){
    if (filaVazia(f)) return 0;
    if (f->ini < f->fim) return f->fim - f->ini;
    return MAX - 1 - f->ini + f->fim + 1;
}

void imprimeFila(const tp_fila *f){
    tp_fila copia = *f;
    tp_item e;
    while (removeFila(&copia, &e))
        printf("%d ", (int)e);
    printf("\n");
}
