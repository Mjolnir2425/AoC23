#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH "day7.txt"
#define MAX_LEN 15

typedef struct {
    int hand[5];
    int bid;
    int type;
} Hand;

int get_num_of_hands() {
    char line[MAX_LEN];
    int num_of_hands = 0;

    FILE *fptr = fopen(PATH, "r");

    while (1) {
        fgets(line, MAX_LEN, fptr);
        if (!strcmp(line, "\n")) {
            break;
        }
        num_of_hands++;
    }

    fclose(fptr);
    return num_of_hands;
}

void parse_hands(Hand *hands, int num_of_hands) {
    char line[MAX_LEN], *token = NULL;
    int i, j;
    FILE *fptr = fopen(PATH, "r");

    for (i = 0; i < num_of_hands; i++) {
        fgets(line, MAX_LEN, fptr);
        for (j = 0; j < 5; j++) {
            if (line[j] >= '0' && line[j] <= '9') {
                (hands + i)->hand[j] = line[j] - '0';
            } else {
                switch (line[j]) {
                    case 'A':
                        (hands + i)->hand[j] = 13;
                        break;
                    case 'K':
                        (hands + i)->hand[j] = 12;
                        break;
                    case 'Q':
                        (hands + i)->hand[j] = 11;
                        break;
                    case 'J':
                        (hands + i)->hand[j] = 1;
                        break;
                    case 'T':
                        (hands + i)->hand[j] = 10;
                        break;
                }
            }
        }
        (hands + i)->bid = atoi(&line[6]);
    }

    fclose(fptr);
}

int get_type(int *hand) {
    int i, counter[13] = {0}, appearances[5] = {0}, max_i = 1;

    for (i = 0; i < 5; i++) {
        counter[*(hand + i) - 1]++;
    }

    for (i = 2; i < 13; i++) {
        if (counter[i] > counter[max_i]) {
            max_i = i;
        }
    }
    counter[max_i] += counter[0];

    for (i = 1; i < 13; i++) {
        appearances[counter[i] - 1]++;
    }

    if (appearances[4]) {
        return 6;
    } else if (appearances[3]) {
        return 5;
    } else if (appearances[2]) {
        if (appearances[1]) {
            return 4;
        }
        return 3;
    } else {
        return appearances[1];
    }
}

void set_types(Hand *hands, int num_of_hands) {
    for (int i = 0; i < num_of_hands; i++) {
        (hands + i)->type = get_type((hands + i)->hand);
    }
}

void swap_hands(Hand *a, Hand *b) {
    Hand tmp = *a;
    *a = *b;
    *b = tmp;
}

int handcmp(Hand a, Hand b) {
    if (a.type < b.type) {
        return 1;
    } else if (a.type > b.type) {
        return 0;
    }

    for (int i = 0; i < 5; i++) {
        if (a.hand[i] < b.hand[i]) {
            return 1;
        } else if (a.hand[i] > b.hand[i]) {
            return 0;
        }
    }

    return 0;
}

void sort_ranks(Hand *hands, int num_of_hands) {
    int i, j, min_i;
    for (i = 0; i < num_of_hands; i++) {
        min_i = i;
        for (j = i; j < num_of_hands; j++) {
            if (handcmp(*(hands + j), *(hands + min_i))) {
                min_i = j;
            }
        }
        if (min_i != i) {
            swap_hands(hands + i, hands + min_i);
        }
    }
}

int get_total_winnings(Hand *hands, int num_of_hands) {
    int i, total_winnings = 0;
    for (i = 0; i < num_of_hands; i++) {
        total_winnings += (hands + i)->bid * (i + 1);
    }
    return total_winnings;
}

int main(void) {
    int num_of_hands = get_num_of_hands(), total_winnings;

    Hand hands[num_of_hands];

    parse_hands(hands, num_of_hands);
    set_types(hands, num_of_hands);
    sort_ranks(hands, num_of_hands);

    total_winnings = get_total_winnings(hands, num_of_hands);

    printf("%d", total_winnings);

    return 0;
}
