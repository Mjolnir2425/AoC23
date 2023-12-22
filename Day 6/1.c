#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define PATH "day6.txt"
#define MAX_LEN 100
#define MAX_NUM_OF_RACES 5

typedef struct {
    int time;
    int dist;
} Race;

bool is_num(char c) { return c >= '0' && c <= '9'; }

int n_pow_10(int n, int pow_10) {
    for (int i = 0; i < pow_10; i++) {
        n *= 10;
    }
    return n;
}

void populate_list(Race *races, int *num_of_races, char *line, int line_num) {
    int i = (line_num) ? 9 : 5, len = strlen(line);
    int start_i, j;

    *num_of_races = 0;

    while (i < len) {
        if (*(line + i) == ' ') {
            while (*(line + i) == ' ') {
                i++;
            }
        }

        if (is_num(*(line + i))) {
            start_i = i;
            if (line_num) {
                (races + *num_of_races)->dist = 0;
            } else {
                (races + *num_of_races)->time = 0;
            }

            while (is_num(*(line + i))) {
                i++;
            }
            for (j = i - 1; j >= start_i; j--) {
                if (line_num) {
                    (races + *num_of_races)->dist +=
                        n_pow_10(*(line + j) - '0', i - j - 1);
                } else {
                    (races + *num_of_races)->time +=
                        n_pow_10(*(line + j) - '0', i - j - 1);
                }
            }
            ++*num_of_races;
        }

        i++;
    }
}

void set_races(Race *races, int *num_of_races) {
    char line[MAX_LEN];

    FILE *fptr = fopen(PATH, "r");

    fgets(line, MAX_LEN, fptr);
    populate_list(races, num_of_races, line, 0);

    fgets(line, MAX_LEN, fptr);
    populate_list(races, num_of_races, line, 1);

    fclose(fptr);
}

int get_num_of_winning_games(Race *race) {
    int winning_games = 0, hold_time;

    for (hold_time = 1; hold_time < race->time; hold_time++) {
        if ((race->time - hold_time) * hold_time > race->dist) {
            winning_games++;
        }
    }

    return winning_games;
}

int get_num_of_combinations(Race *races, int num_of_races) {
    int num_of_combinations = 1;

    for (int i = 0; i < num_of_races; i++) {
        num_of_combinations *= get_num_of_winning_games(races + i);
    }

    return num_of_combinations;
}

int main(void) {
    Race races[MAX_NUM_OF_RACES];
    int num_of_races, num_of_combinations;

    set_races(races, &num_of_races);

    num_of_combinations = get_num_of_combinations(races, num_of_races);

    printf("%d", num_of_combinations);

    return 0;
}
