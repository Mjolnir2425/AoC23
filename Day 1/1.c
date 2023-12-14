#include <stdio.h>
#include <string.h>
#define MAX 200
#define PATH "1.txt"

int main(void) {
    char line[MAX + 1], previous_line[MAX + 1];
    int sum = 0, i, len;
    FILE *fptr = fopen(PATH, "r");

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
            }
        }

        for (i = len - 1; i >= 0; i--) {
            if (line[i] >= '0' && line[i] <= '9') {
                sum += (line[i] - '0');
                break;
            }
        }
    }

    printf("%d", sum);

    return 0;
}
