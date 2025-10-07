#include <stdio.h>

#define MAX 5

int states = 3, symbols = 3; // symbols: a, b, e (e for epsilon)
char alpha[] = {'a', 'b', 'e'};

// transitions[from][symbol][to] = 1 if transition exists
int trans[3][3][3] = {
    { {0,1,0}, {0,0,0}, {0,0,1} },  // q0: a→q1, ε→q2
    { {0,0,1}, {1,0,0}, {0,0,0} },  // q1: a→q2, b→q07
    { {0,0,0}, {0,0,0}, {0,0,0} }   // q2: no transitions
};

// Recursive epsilon closure
void epsilonClosure(int s, int closure[]) {
    if (closure[s]) return;
    closure[s] = 1;
    for (int t = 0; t < states; t++)
        if (trans[s][2][t]) epsilonClosure(t, closure);
}

void printSet(int set[]) {
    printf("{ ");
    for (int i = 0; i < states; i++)
        if (set[i]) printf("q%d ", i);
    printf("}");
}

int main() {
    int closure[MAX][MAX] = {0};

    // Compute epsilon-closures
    for (int i = 0; i < states; i++)
        epsilonClosure(i, closure[i]);

    printf("Epsilon Closures:\n");
    for (int i = 0; i < states; i++) {
        printf("ε-closure(q%d) = ", i);
        printSet(closure[i]);
        printf("\n");
    }

    // Print transitions ignoring epsilon
    printf("\nNFA Transitions:\n");
    for (int i = 0; i < states; i++) {
        for (int j = 0; j < symbols - 1; j++) { // skip epsilon
            int result[MAX] = {0};
            for (int s = 0; s < states; s++)
                if (closure[i][s])
                    for (int t = 0; t < states; t++)
                        if (trans[s][j][t])
                            for (int k = 0; k < states; k++)
                                if (closure[t][k]) result[k] = 1;
            printf("From ");
            printSet(closure[i]);
            printf(" on '%c' -> ", alpha[j]);
            printSet(result);
            printf("\n");
        }
    }
    return 0;
}
