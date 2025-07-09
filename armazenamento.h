#ifndef STATS_H
#define STATS_H
#include "AVL.h"    

// inicializa árvore e abre o arquivo texto
void initStats(const char *arquivo_txt);
// registra uma jogada: insere na AVL e escreve no disco
void registarJogada(int tipoComb);
// mostra em tela, em-ordem, cada combinação e quantas vezes saiu
void mostrarEstatisticas(void);
// fecha o arquivo e libera memória da árvore
void closeStats(void);

#endif
