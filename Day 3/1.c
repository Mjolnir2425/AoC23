#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define PATH "1.txt"
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
    char line[MAX_LEN + 1];
    int i, j, k, m = 0, n, sum = 0, start_j, num_len, num, p, q;
    bool is_part_number;
    FILE *fptr = fopen(PATH, "r");

    if (fptr == NULL) {
        printf("File not found.\n");
        return 0;
    }

    // get dimensions of input data
    while (1) {
        fgets(line, MAX_LEN + 1, fptr);
        if (!strcmp(line, "\n")) {
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
    i = 0;
    while (i < m) {
        j = 0;
        while (j < n) {
            if (!is_num(table[i][j])) {
                j++;
                continue;
            }

            start_j = j;
            while (is_num(table[i][j])) {
                j++;
            }
            num_len = j - start_j;

            num = 0;
            for (k = num_len - 1; k >= 0; k--) {
                num += n_pow_10(table[i][j - k - 1] - '0', k);
            }

            is_part_number = false;
            for (p = i - 1; p <= i + 1; p++) {
                for (q = start_j - 1; q <= j; q++) {
                    if (p < 0 || p >= m || q < 0 || q >= n ||
                        is_num(table[p][q]) || table[p][q] == '.') {
                        continue;
                    }
                    is_part_number = true;
                }
            }

            if (is_part_number) {
                sum += num;
            }
            j++;
        }
        i++;
    }
    printf("%d", sum);

    return 0;
}
