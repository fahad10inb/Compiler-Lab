%{
#include <stdio.h>
%}

%%

.*fah.*        { printf("Rejected: contains 'fah'\n"); }
.*              { printf("Accepted: %s\n", yytext); }

%%

int yywrap(void) {
    return 1;
}

int main(void) {
    yylex();
    return 0;
}
