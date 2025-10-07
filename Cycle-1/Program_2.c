#include <stdio.h>

#define MAX 10

int states, symbols;
char alpha[MAX];           // input symbols (last one is epsilon)
int trans[MAX][MAX][MAX];  // transitions[from][symbol][to]
int final[MAX];            // final states

// Compute epsilon closure of a state
void epsilonClosure(int state, int closure[]) {
    if (closure[state]) return;
    closure[state] = 1;
    for (int next = 0; next < states; next++)
        if (trans[state][symbols-1][next])  // epsilon is last symbol
            epsilonClosure(next, closure);
}

// Print set of states
void printSet(int set[]) {
    printf("{ ");
    for (int i = 0; i < states; i++)
        if (set[i]) printf("q%d ", i);
    printf("}");
}

int main() {
    int start, numFinal, numTrans;

    printf("Number of states: ");
    scanf("%d", &states);

    printf("Number of symbols (include epsilon 'e'): ");
    scanf("%d", &symbols);

    printf("Enter symbols: ");
    for (int i = 0; i < symbols; i++)
        scanf(" %c", &alpha[i]);

    printf("Start state: ");
    scanf("%d", &start);

    printf("Number of final states: ");
    scanf("%d", &numFinal);
    printf("Enter final states: ");
    for (int i = 0; i < numFinal; i++) {
        int f; scanf("%d", &f);
        final[f] = 1;
    }

    printf("Number of transitions: ");
    scanf("%d", &numTrans);
    printf("Enter transitions (from symbol to):\n");
    for (int i = 0; i < numTrans; i++) {
        int from, to; char sym;
        scanf("%d %c %d", &from, &sym, &to);

        int symIndex = 0;
        for (; symIndex < symbols; symIndex++)
            if (alpha[symIndex] == sym) break;

        trans[from][symIndex][to] = 1;
    }

    // Compute epsilon closures
    int closure[MAX][MAX] = {0};
    for (int i = 0; i < states; i++)
        epsilonClosure(i, closure[i]);

    // Print NFA transitions
    printf("\nEquivalent NFA transitions:\n");
    for (int i = 0; i < states; i++) {
        for (int j = 0; j < symbols-1; j++) {  // skip epsilon
            int result[MAX] = {0};
            for (int s = 0; s < states; s++) {
                if (closure[i][s]) {
                    for (int t = 0; t < states; t++)
                        if (trans[s][j][t])
                            for (int k = 0; k < states; k++)
                                if (closure[t][k]) result[k] = 1;
                }
            }
            printf("From ");
            printSet(closure[i]);
            printf(" on %c -> ", alpha[j]);
            printSet(result);
            printf("\n");
        }
    }

    // Print final states of NFA
    printf("\nFinal states of NFA: ");
    for (int i = 0; i < states; i++)
        for (int j = 0; j < states; j++)
            if (closure[i][j] && final[j]) { printSet(closure[i]); break; }

    printf("\n");
    return 0;
}
