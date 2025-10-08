%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex(void);
%}

%token FOR LPAREN RPAREN SEMICOLON ASSIGN LT GT LE GE EQ INC DEC
%token NUMBER
%token ID

%%

stmt : FOR LPAREN expr SEMICOLON expr SEMICOLON expr RPAREN
       { printf("Valid FOR statement syntax\n"); }
     ;


expr : ID ASSIGN expr
     | ID
     | NUMBER
     | expr LT expr
     | expr GT expr
     | expr LE expr
     | expr GE expr
     | expr EQ expr
     | ID INC
     | ID DEC
     | /*empty*/
     ;

%%

void yyerror(const char *s) {
    printf("Incorrect Format\n");
}

int main() {
    printf("Enter a FOR statement:\n");
    yyparse();
    return 0;
}
