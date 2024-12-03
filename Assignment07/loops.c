/*
Compile: make loops
Run: ./loops
make loops && ./loops
*/

#include "base.h"

void loops_a(int n) {
    if (n > 9) {
        fprintf(stderr, "loops_a: invalid input\n");
        exit(1);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            printf("%d ", j);
        }
        printf("\n");
    }
}

void loops_b(int n) {
    if (n > 9) {
        fprintf(stderr, "loops_b: invalid input\n");
        exit(1);
    }

    for (int i = 1; i <= n; i++) {

        int padlen = (n - i) * 2;
        
        // Potential for padding helper function
        for (int j = 0; j < padlen; j++) {
            printf(" ");
        }

        for (int k = 1; k <= i; k++) {
            printf("%d ", k);
        }
        printf("\n");
    }
}

void loops_c(int n) {
    if (n > 9) {
        fprintf(stderr, "loops_c: invalid input\n");
        exit(1);
    }

    for (int i = 1; i <= n; i++) {

        int padlen = n - i;

        // Potential for padding helper function
        for (int j = 0; j < padlen; j++) {
            printf(" ");
        }

        for (int k = 1; k <= i; k++) {
            printf("%d ", k);
        }
        printf("\n");
    }
}

void loops_d(int n) {
    if (n % 2 == 0 || n > 9) {
        fprintf(stderr, "loops_d: invalid input\n");
        exit(1);
    }
    
    int midpoint = n / 2;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j == i || j == n - i - 1) {
                printf("%d ", midpoint - abs(midpoint - i));
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
}

void loops_e(int n) {
    if (n < 3 || n > 9) {
        fprintf(stderr, "loops_e: invalid input\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {

        int padlen = n - i;

        // Potential for padding helper function
        for (int j = 0; j < padlen ; j++) {
            printf(" ");
        }

        if (i == 0 || i == n - 1) {
            for (int k = 0; k < n * 2; k++) {
                if (k == 0 || k == n * 2 - 1) {
                    printf("+");
                } else {
                    printf("-");
                }
            }
        } else {
            for (int l = 0; l < n * 2; l++) {
                if (l == 0 || l == n * 2 - 1) {
                    printf("/");
                } else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
}

void loops_f(int n) {
    if (n < 3 || n > 9) {
        fprintf(stderr, "loops_f: invalid input\n");
        exit(1);
    }

    int number = 0;

    for (int i = 0; i < n; i++) {

        int padlen = n - i;

        // Potential for padding helper function
        for (int j = 0; j < padlen ; j++) {
            printf(" ");
        }

        if (i == 0 || i == n - 1) {
            for (int k = 0; k < n * 2; k++) {
                if (k == 0 || k == n * 2 - 1) {
                    printf("+");
                } else {
                    printf("-");
                }
            }
        } else {
            for (int l = 0; l < n * 2; l++) {
                if (l == 0 || l == n * 2 - 1) {
                    printf("/");
                } else {
                    if (l % 2 == 0) {
                        printf(" ");
                    } else {
                        printf("%d", number % 10);
                        number++;
                    }
                }
            }
        }
        printf("\n");
    }
}

int main(void) {
    loops_a(5);
    loops_a(9);
    loops_b(5);
    loops_b(9);
    loops_c(5);
    loops_c(9);
    loops_d(5);
    loops_d(9);
    loops_e(3);
    loops_e(4);
    loops_e(5);
    loops_e(9);
    // loops_e(12); // invalid input, to fix: Remove the check for n > 9
    loops_f(5);
    loops_f(9);
    return 0;
}
