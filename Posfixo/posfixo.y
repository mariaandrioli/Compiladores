
%{
#include <stdio.h>
%}

%token AIDENT BIDENT MAIS MENOS ASTERISCO DIV ABRE_PARENTESES FECHA_PARENTESES AND OR

%%

expr       : expr MAIS termo {printf ("+"); } |
             expr MENOS termo {printf ("-"); } | 
             expr OR termo {printf ("|"); } |
             termo
;

termo      : termo ASTERISCO fator  {printf ("*"); }| 
             termo DIV fator  {printf ("/"); }|
             termo AND fator  {printf ("&"); }|
             fator
;

fator      : AIDENT {printf ("A"); }|
             BIDENT {printf ("B"); }
;

%%

int main (int argc, char** argv) {
   yyparse();
   printf("\n");
}

