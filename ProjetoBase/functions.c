#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "compilador.h"

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
