#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define MAX 200
#define PATH "day2.txt"
#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14

int main(void) {
    char line[MAX + 1];
    int i, j, start_i, game_id = 0, count, sum = 0, reds_max, greens_max,
                       blues_max, len;
    FILE *fptr = fopen(PATH, "r");
    bool passed_colon, possible;

    if (fptr == NULL) {
        printf("File not found.\n");
        return 0;
    }

    while (true) {
        fgets(line, MAX + 1, fptr);
        if (!strcmp(line, "\n")) {
            break;
        }
        game_id++;

        passed_colon = false;
        possible = true;

        len = strlen(line);
        i = reds_max = greens_max = blues_max = 0;
        while (i < len) {
            // skipping to first character after colon
            if (!passed_colon) {
                if (line[i] == ':') {
                    passed_colon = true;
                    i++;
                }
                i++;
                continue;
            }

            // if the character is a number, store it to `count` and go to first
            // character of color
            if (line[i] >= '0' && line[i] <= '9') {
                start_i = i;

                while (line[i] >= '0' && line[i] <= '9') {
                    i++;
                }

                count = 0;

                for (j = i - start_i - 1; j >= 0; j--) {
                    count += (line[i - j - 1] - '0') * pow(10, j);
                }

                i++;
            }

            switch (line[i]) {
                case 'r':
                    i += 4;
                    if (count > reds_max) {
                        reds_max = count;
                    }
                    break;
                case 'g':
                    i += 6;
                    if (count > greens_max) {
                        greens_max = count;
                    }
                    break;
                case 'b':
                    i += 5;
                    if (count > blues_max) {
                        blues_max = count;
                    }
                    break;
            }

            i++;
        }

        if (reds_max <= MAX_RED && greens_max <= MAX_GREEN &&
            blues_max <= MAX_BLUE) {
            sum += game_id;
        }
    }

    printf("%d", sum);

    return 0;
}
