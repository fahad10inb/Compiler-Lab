#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void get_code(char *expr,int operator, char *reg)
{
    char temp[100];    
    int i=0,j=0;
    while(expr[i]!='\0')
    {
        if(expr[i]== operator)
        {
            printf("\t%c\t%c\t%c\t%c\n",operator,*reg,expr[i-1],expr[i+1]);
            temp[j-1] = *reg;
            i+=2;
            (*reg)--;
            continue;
        }
        temp[j++] = expr[i++];
    }
    temp[j] = '\0';
    strcpy(expr,temp);
}

void convert(char *expr)
{
    char reg = 'Z';
    get_code(expr,'/',&reg);
    get_code(expr,'*',&reg);
    get_code(expr,'+',&reg);
    get_code(expr,'-',&reg);
    get_code(expr,'=',&reg);
}

int main()
{
    char input[100];
    printf("Enter an expression :\n");
    scanf("%s",input);
    printf("Op\tDestn\tArg1\tArg2\n");
    convert(input);
    return 0;
}