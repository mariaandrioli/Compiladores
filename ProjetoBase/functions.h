#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <stdlib.h>
#include <stdio.h>
#include <math.h>


typedef struct pilha_t {
    int head;
    void **elementos;
} *pilha_t;

pilha_t initPilha();
void push(pilha_t pilha, void *elem);
void* pop(pilha_t pilha);
void freePilha(pilha_t pilha);

enum categorias {varSimples, procedure, parametro, function, label}; 

typedef struct elemento_t {
  char simbolo[100];
  enum categorias categoria;
  int endereco;
  char tipo[8];
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
void imprimeTabela(tabelaSimbolos_t tabela);
void insereTipo(tabelaSimbolos_t tabela, int cont, char* token);


#endif // __FUNCTIONS_H__