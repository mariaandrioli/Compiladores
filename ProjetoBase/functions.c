#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "compilador.h"
#define TAM_PILHA 100

pilha_t initPilha() {
    pilha_t pilha = (pilha_t) malloc(sizeof(struct pilha_t));
    pilha->elementos = (void**) malloc(TAM_PILHA* sizeof(void*));
    pilha->head = -1;
    return pilha;
}

void push(pilha_t pilha, void *elem) {
    (pilha->head)++;
    if(pilha->head == TAM_PILHA) {
        puts("Pilha cheia");
        exit(1);
    }
    pilha->elementos[pilha->head] = elem;
    return ;
}

void* pop(pilha_t pilha) {
    if(pilha->head == -1)
        return NULL;
    --(pilha->head);
    return pilha->elementos[pilha->head+1];
}

void freePilha(pilha_t pilha) {
    free(pilha->elementos);
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