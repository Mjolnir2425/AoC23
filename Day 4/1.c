#include <stdio.h>
#include <string.h>
#define PATH "1.txt"
#define MAX_LEN 150

int main(void) {
    char line[MAX_LEN + 1];
    int num_of_cards = 0, num_of_winning, num_of_nums, winning_start,
        nums_start;

    FILE *fptr_first_pass = fopen(PATH, "r");

    if (fptr_first_pass == NULL) {
        printf("File not found.\n");
        return 0;
    }

    fgets(line, MAX_LEN, fptr_first_pass);

    int i, j, len = strlen(line) - 1;
    for (i = 0; i < len; i++) {
        if (line[i] == ':') {
            winning_start = i + 2;
        } else if (line[i] == '|') {
            nums_start = i + 2;
            num_of_winning = (i - winning_start) / 3;
        }
    }
    num_of_nums = (len - nums_start + 1) / 3;

    fclose(fptr_first_pass);
    FILE *fptr = fopen(PATH, "r");

    int points = 0, card_points, winning[num_of_winning], ind, num;

    while (1) {
        fgets(line, MAX_LEN + 1, fptr);

        if (!strcmp(line, "\n")) {
            break;
        }

        // fill array with winning numbers of current card
        for (i = 0; i < num_of_winning; i++) {
            ind = winning_start + 3 * i;
            if (line[ind] == ' ') {
                line[ind] = '0';
            }
            winning[i] = (line[ind] - '0') * 10 + line[ind + 1] - '0';
        }

        // check which nums appear in the list
        card_points = 0;
        for (i = 0; i < num_of_nums; i++) {
            ind = nums_start + 3 * i;
            if (line[ind] == ' ') {
                line[ind] = '0';
            }
            num = (line[ind] - '0') * 10 + line[ind + 1] - '0';

            for (j = 0; j < num_of_winning; j++) {
                if (num != winning[j]) {
                    continue;
                } else if (card_points == 0) {
                    card_points = 1;
                } else {
                    card_points *= 2;
                }
            }
        }
        points += card_points;
    }
    printf("%d", points);

    return 0;
}
