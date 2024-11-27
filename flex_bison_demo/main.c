#include <stdio.h>
#include <calc.tab.h>

int main()
{
    printf("main start!\n");
    yyparse();
    printf("main done!\n");
    return 0;
}