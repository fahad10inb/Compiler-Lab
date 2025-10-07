#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Only 5 most common keywords for simplicity
char keywords[5][10] = {"int", "if", "else", "while", "return"};

int isKeyword(char *word) {
    for(int i = 0; i < 5; i++) {
        if(strcmp(word, keywords[i]) == 0) return 1;
    }
    return 0;
}

int main() {
    FILE *file = fopen("input.txt", "r");
    char ch, word[50];
    int i = 0;
    
    printf("TOKENS FOUND:\n");
    
    while((ch = fgetc(file)) != EOF) {
        
        // SKIP ALL WHITESPACE (spaces, tabs, newlines)
        if(isspace(ch)) continue;
        
        // Handle LETTERS (keywords and identifiers)
        if(isalpha(ch)) {
            i = 0;
            word[i++] = ch;
            
            // Read complete word
            while((ch = fgetc(file)) != EOF && isalnum(ch)) {
                word[i++] = ch;
            }
            word[i] = '\0';
            ungetc(ch, file);  // Put back last character
            
            // Check if keyword or identifier
            if(isKeyword(word))
                printf("KEYWORD: %s\n", word);
            else
                printf("IDENTIFIER: %s\n", word);
        }
        
        // Handle NUMBERS
        else if(isdigit(ch)) {
            i = 0;
            word[i++] = ch;
            
            // Read complete number
            while((ch = fgetc(file)) != EOF && isdigit(ch)) {
                word[i++] = ch;
            }
            word[i] = '\0';
            ungetc(ch, file);
            
            printf("NUMBER: %s\n", word);
        }
        
        // Handle SYMBOLS (operators and delimiters)
        else {
            printf("SYMBOL: %c\n", ch);
        }
    }
    
    fclose(file);
    return 0;
}
