#include <string.h> 
#include <stdio.h>
#define MAX 50 

char stack[MAX], input[MAX]; 
char table[10][10]; 
char terminals[10]; 
int n; 

int idx(char symbol) { 
    for (int i = 0; i < n; i++) { 
        if (terminals[i] == symbol) 
            return i; 
    } 
    return -1; 
}

int is_operator(char c) {
    return (c != 'i' && c != '$');
}

// function to get the actual symbol (skip precedence markers)
char get_top_symbol(int top) {
    while (top >= 0) {
        if (stack[top] != '<' && stack[top] != '>' && stack[top] != '=') {
            return stack[top];
        }
        top--;
    }
    return '$';
}

int main() { 
    int i, j, top = 0; 
    char temp[MAX], a, b; 
    int col, row; 

    printf("Enter number of terminals: "); 
    scanf("%d", &n); 
    printf("Enter the terminals (single characters like + * i $):\n"); 
    scanf("%s", terminals); 
    printf("\nEnter operator precedence table values (<, >, =):\n"); 
    for (i = 0; i < n; i++) { 
        for (j = 0; j < n; j++) { 
            printf("Enter value for %c %c: ", terminals[i], terminals[j]); 
            scanf(" %c", &table[i][j]); 
        } 
    } 

    printf("\n**** OPERATOR PRECEDENCE TABLE ****\n\t"); 
    for (i = 0; i < n; i++) 
        printf("%c\t", terminals[i]); 
    printf("\n"); 
    for (i = 0; i < n; i++) { 
        printf("%c\t", terminals[i]); 
        for (j = 0; j < n; j++) 
            printf("%c\t", table[i][j]); 
        printf("\n"); 
    } 

    printf("\nEnter the input string (e.g., id+id*id): "); 
    scanf("%s", temp); 

    // convert all "id" into 'i'
    int k = 0, m = 0; 
    while (temp[k] != '\0') { 
        if (temp[k] == 'i' && temp[k + 1] == 'd') { 
            input[m++] = 'i'; 
            k += 2; 
        } else { 
            input[m++] = temp[k++]; 
        } 
    } 
    input[m++] = '$'; 
    input[m] = '\0'; 

    for (k = 0; k < m - 1; k++) {
        if (input[k] != '$' && input[k + 1] != '$') {
            if (is_operator(input[k]) && is_operator(input[k + 1])) {
                printf("\nError: consecutive operators in input\n");
                return 0;
            }
        }
    }

    stack[top] = '$'; 
    stack[top + 1] = '\0';
    printf("\nSTACK\t\tINPUT\t\tACTION\n"); 
    printf("%s\t\t%s\t", stack, input); 

    i = 0; 
    while (1) { 
        a = get_top_symbol(top);
        b = input[i]; 
        col = idx(a); 
        row = idx(b); 

        if (col == -1 || row == -1) { 
            printf("\nError: invalid symbol '%c'\n", (col == -1) ? a : b); 
            break; 
        } 

        if (a == '$' && b == '$') { 
            printf("\nString Accepted.\n"); 
            break; 
        } else if (table[col][row] == '<' || table[col][row] == '=') { 
            stack[++top] = table[col][row]; 
            stack[++top] = b; 
            stack[top + 1] = '\0';
            printf("Shift %c\n", b); 
            i++; 
        } else if (table[col][row] == '>') { 
            while (top > 0 && stack[top] != '<') 
                top--; 
            if (top > 0)
                top--; 
            stack[top + 1] = '\0';
            printf("Reduce\n"); 
        } else { 
            printf("\nError: string not accepted (invalid precedence relation)\n"); 
            break; 
        } 

        printf("%s\t\t", stack); 
        for (int p = i; p < strlen(input); p++) 
            printf("%c", input[p]); 
        printf("\t"); 
    } 

    return 0; 
}