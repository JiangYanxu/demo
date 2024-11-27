%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s) { fprintf(stderr, "Error: %s\n", s); }
%}

%token NUMBER
%left '+' '-'
%left '*' '/'

%%
input:
    /* 空规则 */
    | input line
    ;

line:
    expr '\n' { printf("Result: %d\n", $1); }
    ;

expr:
    expr '+' expr   { $$ = $1 + $3; printf("\t-> %d = %d + %d\n", $$, $1, $3); }
    | expr '-' expr { $$ = $1 - $3; printf("\t-> %d = %d - %d\n", $$, $1, $3); }
    | expr '*' expr { $$ = $1 * $3; printf("\t-> %d = %d * %d\n", $$, $1, $3); }
    | expr '/' expr { $$ = $1 / $3; printf("\t-> %d = %d / %d\n", $$, $1, $3); }
    | '(' expr ')'  { $$ = $2;      printf("\t-> %d = (%d)\n", $$, $2); }
    | NUMBER        { $$ = $1;      printf("\t-> %d = %d\n", $$, $1); }
    ;
%%
