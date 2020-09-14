
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
int conta_vars;
int conta_vars_tipo;
char var_atribuicao_atual[20];
char operacao_bool[5];
int nivel_lex_atual;

%}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES 
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token T_BEGIN T_END VAR IDENT ATRIBUICAO NUMERO
%token LABEL TYPE ARRAY OF PROCEDURE FUNCTION
%token INTEGER BOOLEAN
%token GOTO IF THEN ELSE WHILE DO OR DIV AND NOT
%token ABRE_CHAVES FECHA_CHAVES ABRE_COLCHETES FECHA_COLCHETES
%token IGUAL MAIOR MENOR DESIGUAL MAIOR_IGUAL MENOR_IGUAL
%token MAIS MENOS ASTERISCO 

%%

programa: { 
               geraCodigo (NULL, "INPP"); 
               nivel_lex_atual = 0;
            }
               PROGRAM IDENT 
               ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
               bloco PONTO {
               geraCodigo (NULL, "PARA"); 
            }
;

bloco: 
              parte_declara_vars
              { 
               imprimeTabela(tabelaSimbolos);
              }

              comando_composto 
              ;


parte_declara_vars:  var 
;

var: {
                  conta_vars = 0;
               } 
               VAR declara_vars
              { /* AMEM */
               char amem[10];
               sprintf(amem, "AMEM %d", conta_vars);
               geraCodigo(NULL, amem);
              }
            |
;

declara_vars: declara_vars declara_var 
            | declara_var 
;

declara_var: 
               { 
                  conta_vars_tipo = 0;
               } 
              lista_id_var DOIS_PONTOS 
              tipo 
              PONTO_E_VIRGULA
              {
               
              }
;

tipo: IDENT 
            {
               insereTipo(tabelaSimbolos, conta_vars_tipo, token); // insere tipo na tabela
            }
;

lista_id_var: lista_id_var VIRGULA IDENT 
               { 
                  conta_vars_tipo++;
                  elemento_t paraInserir = malloc(sizeof(elemento_t));
                  strcpy(paraInserir->simbolo, token);
                  paraInserir->categoria = varSimples;
                  paraInserir->endereco = conta_vars;
                  insereTabela(tabelaSimbolos, paraInserir);
                 // adiciona na tabela de simbolos com simbolo, offset == contaids
                 conta_vars++; 
               }
            | IDENT 
               {
                  conta_vars_tipo++;
                  elemento_t paraInserir = malloc(sizeof(elemento_t));
                  strcpy(paraInserir->simbolo, token);
                  paraInserir->categoria = varSimples;
                  paraInserir->endereco = conta_vars;
                  insereTabela(tabelaSimbolos, paraInserir);
                // adiciona na tabela de simbolos com simbolo, offset == contaids
                conta_vars++; 
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
               sprintf(var_atribuicao_atual, token);
            }
            ATRIBUICAO
            expressao
;

expressao: expressao_interna relacao expressao_interna
         {

         } | expressao_interna {
            
         }
;

relacao: MAIOR {
      strcpy(operacao_bool, "CMMA"); 
      } 
      | MENOR {
      strcpy(operacao_bool, "CMME");
      } 
      | MAIOR_IGUAL {
         strcpy(operacao_bool, "CMAG");
      } 
      | MENOR_IGUAL {
         strcpy(operacao_bool, "CMEG");
      } 
      | IGUAL {
         strcpy(operacao_bool, "CMIG");
      } 
      | DESIGUAL {
         strcpy(operacao_bool, "CMDG");
      }
;

expressao_interna: expressao_interna MAIS termo |
      expressao_interna MENOS termo |
      expressao_interna OR termo |
      termo
;

termo: termo ASTERISCO fator |
      termo DIV fator |
      termo AND fator |
      fator
;

fator: IDENT |
      
      NUMERO
      {
         /* CRCT */
         char crct[10];
         sprintf(crct, "CRCT %d", atoi(token));
         geraCodigo(NULL, crct);

            /* ARMZ */
         int offset;
         offset = buscaTabela(tabelaSimbolos, var_atribuicao_atual);
         sprintf(crct, "ARMZ %d, %d", nivel_lex_atual,offset);
         geraCodigo(NULL, crct);
      } |

      ABRE_PARENTESES expressao FECHA_PARENTESES

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

   tabelaSimbolos = initTabelaSimbolos();

   yyin=fp;
   yyparse();

   return 0;
}

void yyerror (char* msg){
    imprimeErro(msg);
}

