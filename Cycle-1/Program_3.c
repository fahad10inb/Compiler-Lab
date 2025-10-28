#include <stdio.h>
#include <string.h>

#define MAX 20  // maximum number of states

// ------------------- Global Variables -------------------
int n, a, s, f[MAX], t;          // NFA: states, symbols, start, finals, transition count
int T[MAX][MAX][MAX], Tcount[MAX][MAX];  // NFA transitions for normal symbols
int E[MAX][MAX], Ecount[MAX];             // epsilon transitions (magic portals)
int DFA[MAX][MAX], dfaCount = 0;          // DFA states (each row = set of NFA states)
char alpha[MAX];                          // input symbols


// ------------------- Helper Functions -------------------

// Analogy: "Magic teleport" for epsilon
void epsilonClosure(int state, int closure[]) {
    if (closure[state]) return;  // already visited, prevent loops
    closure[state] = 1;          // mark current room as reachable

    // teleport to other rooms connected via epsilon
    for (int i = 0; i < Ecount[state]; i++)
        epsilonClosure(E[state][i], closure);
}

// Analogy: print a "squad of friends" (set of NFA states)
void printSet(int set[]) {
    printf("{ ");
    for (int i = 0; i < n; i++)
        if (set[i]) printf("q%d ", i);
    printf("}");
}

// ------------------- Main Program -------------------
int main() {
    int i, j, k, from, to;
    char sym;

    // ---------- 1. Input NFA info ----------
    printf("States, Alphabets, Start: ");
    scanf("%d %d %d", &n, &a, &s);  // e.g., 3 2 0

    printf("Alphabets: ");
    for (i = 0; i < a; i++) scanf(" %c", &alpha[i]); // e.g., a b

    // Final states
    int finCount;
    printf("Final count & states: ");
    scanf("%d", &finCount);
    printf("states: ");
    for (i = 0; i < finCount; i++) scanf(" %d", &f[i]); // e.g., 2

    // ---------- 2. Input transitions ----------
    printf("Transitions count: ");
    scanf("%d", &t);
    printf("Transitions (from symbol to), use 'e' for epsilon:\n");
    for (i = 0; i < t; i++) {
        scanf("%d %c %d", &from, &sym, &to);

        if (sym == 'e') {               // epsilon: magic portal
            E[from][Ecount[from]++] = to;
        } else {                        // normal road
            for (j = 0; j < a; j++)
                if (alpha[j] == sym) break;
            T[from][j][Tcount[from][j]++] = to;
        }
    }

    // ---------- 3. Start DFA = epsilon closure of NFA start ----------
    int startClosure[MAX] = {0};
    epsilonClosure(s, startClosure);            // teleport from start
    memcpy(DFA[0], startClosure, sizeof(startClosure));
    dfaCount = 1;

    // ---------- 4. Construct DFA ----------
    for (i = 0; i < dfaCount; i++) {           // for each DFA state (squad of rooms)
        for (j = 0; j < a; j++) {               // for each symbol
            int newSet[MAX] = {0};              // next DFA state (new squad)

            // Check each NFA state in current DFA set
            for (k = 0; k < n; k++) {
                if (DFA[i][k]) {               // if this room is in the squad
                    for (int l = 0; l < Tcount[k][j]; l++) { // each road of symbol j
                        int dest = T[k][j][l];

                        // teleport from destination
                        int tempClosure[MAX] = {0};
                        epsilonClosure(dest, tempClosure);

                        // combine all reachable rooms into new squad
                        for (int m = 0; m < n; m++)
                            if (tempClosure[m]) newSet[m] = 1;
                    }
                }
            }

            // Check if this squad already exists in DFA
            int found = -1;
            for (int m = 0; m < dfaCount; m++)
                if (memcmp(DFA[m], newSet, sizeof(newSet)) == 0)
                    found = m;

            // If new squad, add to DFA
            if (found == -1) memcpy(DFA[dfaCount++], newSet, sizeof(newSet));
        }
    }

    // ---------- 5. Print DFA states ----------
    printf("\n--- DFA States ---\n");
    for (i = 0; i < dfaCount; i++) {
        printf("q%d = ", i);
        printSet(DFA[i]);
        printf("\n");
    }

    // ---------- 6. Identify final DFA states ----------
    printf("\n--- Final DFA States ---\n");
    for (i = 0; i < dfaCount; i++) {
        for (j = 0; j < n; j++)
            for (k = 0; k < finCount; k++)
                if (DFA[i][j] && f[k] == j) {
                    printf("q%d ", i);
                    j = n; // break inner loop
                }
    }
    printf("\n");

    return 0;
}

