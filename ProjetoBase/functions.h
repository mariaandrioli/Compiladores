#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct elemento_t {
  char simbolo[100];
  int categoria;
  int endereco;
  int tipo;
} *elemento_t;

typedef struct tabelaSimbolos_t {
  int head;
  elemento_t elementos[100];
} *tabelaSimbolos_t;

tabelaSimbolos_t initTabelaSimbolos();
int buscaTabela(tabelaSimbolos_t tabela, char *simbolo);
void freeTabela(tabelaSimbolos_t tabela);
int insereTabela(tabelaSimbolos_t tabela, elemento_t paraInserir);
void abaixaTopo(tabelaSimbolos_t tabela);


#endif // __FUNCTIONS_H__