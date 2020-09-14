#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "functions.h"
#include "compilador.h"
#define TAM_PILHA 100

struct pilha_t* createStack(unsigned capacity) 
{ 
    struct pilha_t* stack = (struct pilha_t*)malloc(sizeof(struct pilha_t)); 
    stack->capacity = capacity; 
    stack->top = -1; 
    stack->array = (int*)malloc(stack->capacity * sizeof(int)); 
    return stack; 
} 

int isFull(struct pilha_t* stack) 
{ 
    return stack->top == stack->capacity - 1; 
} 

int isEmpty(struct pilha_t* stack) 
{ 
    return stack->top == -1; 
} 

void push(struct pilha_t* stack, int item) 
{ 
    if (isFull(stack)) 
        return; 
    stack->array[++stack->top] = item; 
    //printf("%d pushed to stack\n", item); 
} 
  
int pop(struct pilha_t* stack) 
{ 
    if (isEmpty(stack)) 
        return INT_MIN; 
    return stack->array[stack->top--]; 
} 
  
int peek(struct pilha_t* stack) 
{ 
    if (isEmpty(stack)) 
        return INT_MIN; 
    return stack->array[stack->top]; 
} 

tabelaSimbolos_t initTabelaSimbolos() {
    tabelaSimbolos_t tabela = (tabelaSimbolos_t) malloc(sizeof(struct tabelaSimbolos_t));
    tabela->head = -1;
    return tabela;
}

int insereTabela(tabelaSimbolos_t tabela, elemento_t paraInserir){
    (tabela->head)++;
    tabela->elementos[tabela->head] = paraInserir;
    return tabela->head;
}

void abaixaTopo(tabelaSimbolos_t tabela){
    (tabela->head)--;
}

int buscaTabela(tabelaSimbolos_t tabela, char *simbolo){
    for (int i = tabela->head; i >= 0; i--){
        if (strcmp((tabela->elementos[i])->simbolo, simbolo) == 0){
            return i;
        }
    }
    return (-1);
}

void freeTabela(tabelaSimbolos_t tabela) {
    free(tabela);
    tabela = NULL;
}

void imprimeTabela(tabelaSimbolos_t tabela) {
    for (int i = tabela->head; i >= 0; i--){
        if (tabela->elementos[i]->simbolo != NULL){
            printf("%s %d %d %s\n", tabela->elementos[i]->simbolo, 
            tabela->elementos[i]->categoria, 
            tabela->elementos[i]->endereco,
            tabela->elementos[i]->tipo);
        }
    }
    printf("\n\n");
}

void insereTipo(tabelaSimbolos_t tabela, int cont, char* token) {
    int j = 0;
    //printf("\n\n%d\n",tabela->head);
    for (int i = tabela->head; j < cont && i >= 0; i--, j++){
        strcpy(tabela->elementos[i]->tipo, token);
    }
}

void geraRotulo(int *num, char* rot) {
    char aux[4];
    int rotulo = *num;;
    rotulo = rotulo + 1;
    sprintf(aux, "%02d", rotulo);
    strcat(rot, aux);
    *num = rotulo;
}

void geraFinalRepeticao(struct pilha_t* pilhaDeRotulos){
    char * rot1 = malloc(sizeof(char)*4);
    char * rot2 = malloc(sizeof(char)*4);
    char * aux = malloc(sizeof(char)*4);
    int num = pop(pilhaDeRotulos); 
    strcpy(rot2, "R");
    sprintf(aux, "%02d", num);
    strcat(rot2, aux);

    num = pop(pilhaDeRotulos); 
    strcpy(rot1, "R");
    sprintf(aux, "%02d", num);
    strcat(rot1, aux);

    char exp[9];
    strcpy(exp, "DSVS ");
    strcat(exp, rot1);
    geraCodigo(NULL, exp);

    geraCodigo(rot2, "NADA");
}