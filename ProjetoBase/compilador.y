
// Testar se funciona corretamente o empilhamento de par�metros
// passados por valor ou por refer�ncia.


%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"
#include "functions.h"

tabelaSimbolos_t tabelaSimbolos;
int num_vars;
int conta_ids;

%}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES 
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token T_BEGIN T_END VAR IDENT ATRIBUICAO NUMERO
%token LABEL TYPE ARRAY OF PROCEDURE FUNCTION
%token INTEGER BOOLEAN
%token GOTO IF THEN ELSE WHILE DO OR DIV AND NOT
%token ABRE_CHAVES FECHA_CHAVES ABRE_COLCHETES FECHA_COLCHETES

%%

programa :{ 
               tabelaSimbolos = initTabelaSimbolos();
               geraCodigo (NULL, "INPP"); 
            }
               PROGRAM IDENT 
               ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
               bloco PONTO {
               geraCodigo (NULL, "PARA"); 
            }
;

bloco       : 
              parte_declara_vars
              { 
              }

              comando_composto 
              ;


parte_declara_vars:  var 
;

var         : {
                  conta_ids = 0;
               } 
               VAR declara_vars
              { /* AMEM */
               char amem[10];
               sprintf(amem, "AMEM %d", conta_ids);
               geraCodigo(NULL, amem);
              }
            |
;

declara_vars: declara_vars declara_var 
            | declara_var 
;

declara_var : 
               { 
               
               } 
              lista_id_var DOIS_PONTOS 
              tipo 
              PONTO_E_VIRGULA
;

tipo        : IDENT
;

lista_id_var: lista_id_var VIRGULA IDENT 
               { 
                 conta_ids++; 
               }
            | IDENT 
               {
                conta_ids++; 
               }
;

lista_idents: lista_idents VIRGULA IDENT  
            | IDENT
;

comando_composto: T_BEGIN comandos T_END ;

comandos: atribuicao PONTO_E_VIRGULA comandos |
         atribuicao PONTO_E_VIRGULA 
;

atribuicao: IDENT  
            {
               // printf("%s\n", token); // imprime nome da var
            }
            ATRIBUICAO
            NUMERO
            {
               char crct[10];
               sprintf(crct, "CRCT %d", atoi(token));
               geraCodigo(NULL, crct);
               //printf("%s\n", token); // imprime valor da var
            }
;

%%

int main (int argc, char** argv) {
   FILE* fp;
   extern FILE* yyin;

   if (argc<2 || argc>2) {
         printf("usage compilador <arq>a %d\n", argc);
         return(-1);
      }

   fp=fopen (argv[1], "r");
   if (fp == NULL) {
      printf("usage compilador <arq>b\n");
      return(-1);
   }


/* -------------------------------------------------------------------
 *  Inicia a Tabela de S�mbolos
 * ------------------------------------------------------------------- */

   yyin=fp;
   yyparse();

   return 0;
}

void yyerror (char* msg){
    imprimeErro(msg);
}

