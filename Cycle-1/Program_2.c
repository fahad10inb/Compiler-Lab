#include <stdio.h>

#define MAX 5

int states = 3, symbols = 3; // symbols: a, b, e (e for epsilon)
char alpha[] = {'a', 'b', 'e'};

int startState = 0;
int finalStates[] = {2};
int numFinalStates = 1;

// transitions[from][symbol][to] = 1 if transition exists
int trans[3][3][3] = {
    { {0,1,0}, {0,0,0}, {0,0,1} },  // q0: a→q1, ε→q2
    { {0,0,1}, {1,0,0}, {0,0,0} },  // q1: a→q2, b→q0
    { {0,0,0}, {0,0,0}, {0,0,0} }   // q2: no transitions
};

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

int isFinal(int state) {
    for (int i = 0; i < numFinalStates; i++)
        if (finalStates[i] == state) return 1;
    return 0;
}

int main() {
    int closure[MAX][MAX] = {0};

    for (int i = 0; i < states; i++)
        epsilonClosure(i, closure[i]);

    printf("Epsilon Closures:\n");
    for (int i = 0; i < states; i++) {
        printf("ε-closure(q%d) = ", i);
        printSet(closure[i]);
        printf("\n");
    }

    printf("\nStart State: q%d\n", startState);
    printf("Final States: ");
    for (int i = 0; i < numFinalStates; i++) printf("q%d ", finalStates[i]);
    printf("\n");

    printf("\nNFA Transitions (excluding ε):\n");
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

    // Show epsilon closure of start state and its reachable finals
    printf("\nε-closure of Start State (q%d): ", startState);
    printSet(closure[startState]);
    printf("\n");
    printf("Reachable Final States: ");
    for (int i = 0; i < states; i++)
        if (closure[startState][i] && isFinal(i)) printf("q%d ", i);
    printf("\n");

    return 0;
}
