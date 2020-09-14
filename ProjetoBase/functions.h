#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct pilha_t { 
    int top; 
    unsigned capacity; 
    int* array; 
}; 

struct pilha_t* createStack(unsigned capacity);
int isFull(struct pilha_t* stack);
int isEmpty(struct pilha_t* stack);
void push(struct pilha_t* stack, int item);
int pop(struct pilha_t* stack);
void geraFinalRepeticao(struct pilha_t* pilhaDeRotulos);

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
void geraRotulo(int *num, char* rot);

#endif // __FUNCTIONS_H__