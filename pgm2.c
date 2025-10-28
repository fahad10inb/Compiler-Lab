#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 50

char prod[MAX][MAX];
char first[26][MAX], follow[26][MAX];
int n;

int isNt(char c) { return (c >= 'A' && c <= 'Z'); }

int has(char s[], char c) {
    for (int i = 0; s[i]; i++)
        if (s[i] == c) return 1;
    return 0;
}

void add(char s[], char c) {
    if (c != ' ' && !has(s, c)) {
        int len = strlen(s);
        s[len] = c;
        s[len + 1] = '\0';
    }
}

// ---------------- FIRST SET CALCULATION ----------------
void calcFirst() {
    int changed = 1;
    while (changed) {
        changed = 0;
        for (int i = 0; i < n; i++) {
            char A = prod[i][0];
            int start = (prod[i][1] == '-' && prod[i][2] == '>') ? 3 : 2;
            int oldLen = strlen(first[A - 'A']);

            for (int j = start; prod[i][j]; j++) {
                char B = prod[i][j];
                if (!isNt(B)) { // terminal
                    add(first[A - 'A'], B);
                    break;
                } else { // non-terminal
                    for (int k = 0; first[B - 'A'][k]; k++)
                        if (first[B - 'A'][k] != 'e')
                            add(first[A - 'A'], first[B - 'A'][k]);
                    if (!has(first[B - 'A'], 'e'))
                        break;
                    else if (!prod[i][j + 1])
                        add(first[A - 'A'], 'e');
                }
            }
            if (strlen(first[A - 'A']) > oldLen)
                changed = 1;
        }
    }
}

// ---------------- FOLLOW SET CALCULATION ----------------
void calcFollow() {
    add(follow[prod[0][0] - 'A'], '$'); // Start symbol gets $

    int changed = 1;
    while (changed) {
        changed = 0;
        for (int i = 0; i < n; i++) {
            char A = prod[i][0];
            int start = (prod[i][1] == '-' && prod[i][2] == '>') ? 3 : 2;

            for (int j = start; prod[i][j]; j++) {
                char B = prod[i][j];
                if (!isNt(B)) continue;

                int oldLen = strlen(follow[B - 'A']);
                int k = j + 1;

                // Case 1: Follow from FIRST of next symbols
                while (prod[i][k]) {
                    char C = prod[i][k];
                    if (!isNt(C)) {
                        add(follow[B - 'A'], C);
                        break;
                    }
                    for (int m = 0; first[C - 'A'][m]; m++)
                        if (first[C - 'A'][m] != 'e')
                            add(follow[B - 'A'], first[C - 'A'][m]);

                    if (!has(first[C - 'A'], 'e'))
                        break;
                    k++;
                }

                // Case 2: If at end or everything after B can be ε
                if (!prod[i][k]) {
                    for (int x = 0; follow[A - 'A'][x]; x++)
                        add(follow[B - 'A'], follow[A - 'A'][x]);
                }

                if (strlen(follow[B - 'A']) > oldLen)
                    changed = 1;
            }
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);
    printf("Enter productions (like A->aB or A->e):\n");
    for (int i = 0; i < n; i++)
        scanf("%s", prod[i]);

    for (int i = 0; i < 26; i++)
        first[i][0] = follow[i][0] = '\0';

    calcFirst();
    calcFollow();

    int printed[26] = {0};

    printf("\nFIRST SET\n");
    for (int i = 0; i < n; i++) {
        char A = prod[i][0];
        if (!printed[A - 'A']) {
            printf("FIRST(%c) = { %s }\n", A, first[A - 'A']);
            printed[A - 'A'] = 1;
        }
    }

    memset(printed, 0, sizeof(printed));
    printf("\nFOLLOW SET\n");
    for (int i = 0; i < n; i++) {
        char A = prod[i][0];
        if (!printed[A - 'A']) {
            printf("FOLLOW(%c) = { %s }\n", A, follow[A - 'A']);
            printed[A - 'A'] = 1;
        }
    }

    return 0;
}
