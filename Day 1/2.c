#include <stdio.h>
#include <string.h>
#define MAX 200
#define PATH "day1.txt"

int digit_started(char* start_char) {
    char next_three[3 + 1] = {0}, next_four[4 + 1] = {0},
                        next_five[5 + 1] = {0};
    int i;

    for (i = 0; i < 5; i++) {
        switch (i) {
            case 0:
            case 1:
            case 2:
                next_three[i] = *(start_char + i);
                next_four[i] = *(start_char + i);
                next_five[i] = *(start_char + i);
                break;
            case 3:
                next_four[3] = *(start_char + 3);
                next_five[3] = *(start_char + 3);
                break;
            case 4:
                next_five[4] = *(start_char + 4);
        }
    }

    if (!strcmp(next_three, "one")) {
        return 1;
    } else if (!strcmp(next_three, "two")) {
        return 2;
    } else if (!strcmp(next_five, "three")) {
        return 3;
    } else if (!strcmp(next_four, "four")) {
        return 4;
    } else if (!strcmp(next_four, "five")) {
        return 5;
    } else if (!strcmp(next_three, "six")) {
        return 6;
    } else if (!strcmp(next_five, "seven")) {
        return 7;
    } else if (!strcmp(next_five, "eight")) {
        return 8;
    } else if (!strcmp(next_four, "nine")) {
        return 9;
    } else {
        return 0;
    }
}

int main(void) {
    char line[MAX + 1] = {0}, previous_line[MAX + 1];
    int sum = 0, i, len, matched;
    FILE* fptr = fopen(PATH, "r");

    if (fptr == NULL) {
        printf("File not found.\n");
    }

    while (1) {
        strcpy(previous_line, line);
        fgets(line, MAX + 1, fptr);

        if (!strcmp(line, previous_line)) {
            break;
        }

        len = strlen(line);

        for (i = 0; i < len; i++) {
            if (line[i] >= '0' && line[i] <= '9') {
                sum += (line[i] - '0') * 10;
                break;
            } else {
                matched = digit_started(&line[i]);
                if (matched != 0) {
                    sum += matched * 10;
                    break;
                }
            }
        }

        for (i = len - 1; i >= 0; i--) {
            if (line[i] >= '0' && line[i] <= '9') {
                sum += line[i] - '0';
                break;
            } else {
                matched = digit_started(&line[i]);
                if (matched != 0) {
                    sum += matched;
                    break;
                }
            }
        }
    }

    printf("%d", sum);

    return 0;
}
