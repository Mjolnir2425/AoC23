#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define PATH "2.txt"
#define MAX_LEN 400

bool is_num(char chr) {
    if (chr >= '0' && chr <= '9') {
        return true;
    }
    return false;
}

int n_pow_10(int n, int p) {
    int i, rez = n;
    for (i = 0; i < p; i++) {
        rez *= 10;
    }
    return rez;
}

int main(void) {
    char line[MAX_LEN + 1], previous_line[MAX_LEN + 1];
    int i, j, k, m = 0, n;
    FILE *fptr = fopen(PATH, "r");

    if (fptr == NULL) {
        printf("File not found.\n");
        return 0;
    }

    // get dimensions of input data
    while (1) {
        strcpy(previous_line, line);
        fgets(line, MAX_LEN + 1, fptr);

        if (!strcmp(line, previous_line) || !strcmp(line, "\n")) {
            break;
        }

        m++;
        n = strlen(line) + 1;
    }

    // create table of characters
    char table[m][n];

    fclose(fptr);
    FILE *file = fopen(PATH, "r");

    for (i = 0; i < m; i++) {
        fgets(line, n, file);

        for (j = 0; j < n; j++) {
            if (line[j] == '\n') {
                table[i][j] = 0;
                break;
            }
            table[i][j] = line[j];
        }
        table[i][n - 1] = 0;
    }

    n -= 2;

    // matching
    unsigned int sum = 0;
    int num_of_adjecent, product, p, q, r, start_r, prev_start_r, start_p,
        prev_start_p, num_len, num;

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (table[i][j] != '*') {
                continue;
            }

            product = 1;
            num_of_adjecent = 0;

            // for every cell that is a number around the *
            for (p = i - 1; p <= i + 1; p++) {
                for (q = j - 1; q <= j + 1; q++) {
                    if (p < 0 || q < 0 || p >= m || q >= n ||
                        !is_num(table[p][q])) {
                        continue;
                    }
                    r = q;

                    // find the starting index of the found number
                    while (is_num(table[p][r]) && r >= 0) {
                        r--;
                    }

                    // determine if that number has already been found
                    start_r = ++r;
                    start_p = p;
                    if (start_r == prev_start_r && start_p == prev_start_p) {
                        continue;
                    }
                    prev_start_r = start_r;
                    prev_start_p = start_p;
                    num_of_adjecent++;

                    while (is_num(table[p][r]) && r < n) {
                        r++;
                    }

                    num_len = --r - start_r;
                    num = 0;

                    // finally, find the number
                    for (k = num_len; k >= 0; k--) {
                        num += n_pow_10(table[p][r - k] - '0', k);
                    }

                    product *= num;
                }
            }

            if (num_of_adjecent == 2) {
                sum += product;
            }
        }
    }

    printf("%u", sum);

    return 0;
}
