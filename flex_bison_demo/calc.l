%{
#include "calc.tab.h"
#include <stdio.h>
%}

%%
[0-9]+          { yylval = atoi(yytext); printf("\t=> NUMBER: %s -> %d\n", yytext, yylval); return NUMBER; }
[+\-*/()]       { printf("\t=> symbol: %c\n", yytext[0]); return yytext[0]; }
[ \t]+          { printf("\t=> null: %s\n", yytext); }
[\n]            { printf("\t=> \\n\n"); return yytext[0]; }
.               { printf("\t=> unexpected character:%s\n", yytext); return 1; }
%%