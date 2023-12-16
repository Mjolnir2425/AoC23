#include <stdio.h>
#include <string.h>
#define PATH "day4.txt"
#define MAX_LEN 150
#define MAX_WINNING_ON_CARD 50
#define MAX_NUMS_ON_CARD 50

typedef struct {
    int card_num;
    int winning[MAX_WINNING_ON_CARD];
    int nums[MAX_NUMS_ON_CARD];
} Card;

void get_cards_info(int *winning_start, int *nums_start, int *num_of_winning,
                    int *num_of_nums, int *num_of_cards) {
    FILE *fptr = fopen(PATH, "r");
    char line[MAX_LEN];
    fgets(line, MAX_LEN, fptr);

    *num_of_cards = 1;
    int i, j, len = strlen(line) - 1;
    for (i = 0; i < len; i++) {
        if (line[i] == ':') {
            *winning_start = i + 2;
        } else if (line[i] == '|') {
            *nums_start = i + 2;
            *num_of_winning = (i - *winning_start) / 3;
        }
    }
    *num_of_nums = (len - *nums_start + 1) / 3;

    while (1) {
        fgets(line, MAX_LEN + 1, fptr);
        if (!strcmp(line, "\n")) {
            break;
        }
        ++*num_of_cards;
    }

    fclose(fptr);
}

void create_cards(Card *cards, int num_of_winning, int num_of_nums,
                  int winning_start, int nums_start) {
    FILE *fptr = fopen(PATH, "r");
    char line[MAX_LEN];
    int card_num = 1, ind, i, j;

    while (1) {
        fgets(line, MAX_LEN + 1, fptr);

        if (!strcmp(line, "\n")) {
            break;
        }

        cards[card_num - 1].card_num = card_num;

        // fill array with winning numbers of current card
        for (i = 0; i < num_of_winning; i++) {
            ind = winning_start + 3 * i;
            if (line[ind] == ' ') {
                line[ind] = '0';
            }
            cards[card_num - 1].winning[i] =
                (line[ind] - '0') * 10 + line[ind + 1] - '0';
        }

        // fill array with guessed numbers of current card
        for (i = 0; i < num_of_nums; i++) {
            ind = nums_start + 3 * i;
            if (line[ind] == ' ') {
                line[ind] = '0';
            }
            cards[card_num - 1].nums[i] =
                (line[ind] - '0') * 10 + line[ind + 1] - '0';
        }
        card_num++;
    }
}

int get_num_of_matches(Card *card, int num_of_winning, int num_of_nums) {
    int i, j, num_of_matches = 0;

    for (i = 0; i < num_of_nums; i++) {
        for (j = 0; j < num_of_winning; j++) {
            if (card->nums[i] == card->winning[j]) {
                num_of_matches++;
                break;
            }
        }
    }

    return num_of_matches;
}

int process_card(int card_number, Card *all_cards, int num_of_winning,
                 int num_of_nums) {
    int num_of_matches = get_num_of_matches(all_cards + card_number - 1,
                                            num_of_winning, num_of_nums);
    int num_of_new_cards = num_of_matches;

    if (num_of_matches == 0) {
        return 0;
    }

    for (int i = 1; i <= num_of_new_cards; i++) {
        num_of_matches += process_card(card_number + i, all_cards,
                                       num_of_winning, num_of_nums);
    }
    return num_of_matches;
}

int main(void) {
    char line[MAX_LEN];
    int num_of_winning, num_of_nums, num_of_cards, winning_start, nums_start;

    get_cards_info(&winning_start, &nums_start, &num_of_winning, &num_of_nums,
                   &num_of_cards);

    Card cards[num_of_cards];
    create_cards(cards, num_of_winning, num_of_nums, winning_start, nums_start);

    int won_cards = num_of_cards, i;

    for (i = 0; i < num_of_cards; i++) {
        won_cards +=
            process_card(cards[i].card_num, cards, num_of_winning, num_of_nums);
    }

    printf("%d", won_cards);

    return 0;
}
