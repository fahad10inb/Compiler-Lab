#include <stdio.h>
#include <string.h>

char trans[20][3][10];
int tCount = 0;

int main() {
    int n, i, j, k, size;
    char states[20][10], closure[20][10];

    printf("How many states? ");
    scanf("%d", &n);
    printf("Enter states: ");  
    for (i = 0; i < n; i++) scanf("%s", states[i]);
    FILE *f = fopen("automata.txt", "r");
    if (!f) return printf("File error\n"), 1;
    
    while (fscanf(f, "%s %s %s", trans[tCount][0], trans[tCount][1], trans[tCount][2]) == 3)
        tCount++;
    fclose(f);

    for (i = 0; i < n; i++) {
        size = 1;
        strcpy(closure[0], states[i]);

        for (j = 0; j < size; j++) {
            for (k = 0; k < tCount; k++) {
                if (strcmp(trans[k][0], closure[j]) == 0 && trans[k][1][0] == 'e') {
                   
                    int exists = 0;
                    for (int m = 0; m < size && !exists; m++)
                        if (strcmp(closure[m], trans[k][2]) == 0) 
                        exists = 1;
                    
                    if (!exists) 
                    strcpy(closure[size++], trans[k][2]);
                }
            }
        }

        printf("Epsilon closure of %s = { ", states[i]);
        for (j = 0; j < size; j++) 
        printf("%s ", closure[j]);
        printf("}\n");
    }
    return 0;
}
