#ifndef FILA_H
#define FILA_H

#include <stdbool.h>    
#define MAX 100

typedef char tp_item;

typedef struct {
    tp_item item[MAX];
    int ini, fim;
} tp_fila;

void    inicializaFila(tp_fila *f);
bool    filaVazia(const tp_fila *f);
bool    filaCheia(const tp_fila *f);
int     tamanhoFila(const tp_fila *f);
bool    insereFila(tp_fila *f, tp_item e);
bool    removeFila(tp_fila *f, tp_item *e);
void    imprimeFila(const tp_fila *f); 

#endif // FILA_H
