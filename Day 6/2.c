#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define PATH "day6.txt"
#define MAX_LEN 100
#define MAX_NUM_OF_RACES 5

bool is_num(char c) { return c >= '0' && c <= '9'; }

unsigned long long get_num_from_line(char *line) {
    int len = strlen(line), i = len - 1;
    unsigned long long pow10 = 1, num = 0;

    while (is_num(*(line + i)) || *(line + i) == ' ' || *(line + i) == '\n') {
        if (*(line + i) == ' ') {
            while (*(line + i) == ' ') {
                i--;
            }
        }

        while (is_num(*(line + i))) {
            num += (*(line + i--) - '0') * pow10;
            pow10 *= 10;
        }

        i--;
    }

    return num;
}

void set_data(unsigned long long *time, unsigned long long *dist) {
    char line[MAX_LEN];

    FILE *fptr = fopen(PATH, "r");

    fgets(line, MAX_LEN, fptr);
    *time = get_num_from_line(line);

    fgets(line, MAX_LEN, fptr);
    *dist = get_num_from_line(line);

    fclose(fptr);
}

unsigned long long get_num_of_ways(unsigned long long time,
                                   unsigned long long dist) {
    return 1 + (unsigned long long)sqrtl(time * time - 4 * dist) / 2 * 2;
}

int main(void) {
    unsigned long long time, dist, num_of_ways;

    set_data(&time, &dist);

    num_of_ways = get_num_of_ways(time, dist);

    printf("%llu", num_of_ways);

    return 0;
}
