#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

void generateMatrix(char key[]) {
    int used[26] = {0};
    int i, j, k = 0;
    char ch;

    used['J' - 'A'] = 1;

    for (i = 0; key[i] != '\0'; i++) {
        ch = toupper((unsigned char)key[i]);

        if (ch < 'A' || ch > 'Z')
            continue;

        if (ch == 'J')
            ch = 'I';

        if (!used[ch - 'A']) {
            matrix[k / 5][k % 5] = ch;
            used[ch - 'A'] = 1;
            k++;
        }
    }

    for (ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            matrix[k / 5][k % 5] = ch;
            k++;
        }
    }
}

void findPosition(char ch, int *row, int *col) {
    int i, j;

    if (ch == 'J')
        ch = 'I';

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encryptPair(char a, char b, char *x, char *y) {
    int r1, c1, r2, c2;

    findPosition(a, &r1, &c1);
    findPosition(b, &r2, &c2);

    if (r1 == r2) {
        *x = matrix[r1][(c1 + 1) % 5];
        *y = matrix[r2][(c2 + 1) % 5];
    }
    else if (c1 == c2) {
        *x = matrix[(r1 + 1) % 5][c1];
        *y = matrix[(r2 + 1) % 5][c2];
    }
    else {
        *x = matrix[r1][c2];
        *y = matrix[r2][c1];
    }
}

int main() {
    char key[100], text[500], clean[500], encrypted[1000];
    int i, j = 0, n = 0;

    printf("Enter keyword: ");
    fgets(key, sizeof(key), stdin);

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);

    generateMatrix(key);

    for (i = 0; text[i] != '\0'; i++) {
        char ch = toupper((unsigned char)text[i]);

        if (ch >= 'A' && ch <= 'Z') {
            if (ch == 'J')
                ch = 'I';

            clean[n++] = ch;
        }
    }

    clean[n] = '\0';

    i = 0;
    while (i < n) {
        char a = clean[i];
        char b;

        if (i + 1 >= n) {
            b = 'X';
            i++;
        }
        else if (clean[i] == clean[i + 1]) {
            b = 'X';
            i++;
        }
        else {
            b = clean[i + 1];
            i += 2;
        }

        encryptPair(a, b, &encrypted[j], &encrypted[j + 1]);
        j += 2;
    }

    encrypted[j] = '\0';

    printf("\nPlayfair Matrix:\n");
    for (i = 0; i < 5; i++) {
        for (int c = 0; c < 5; c++)
            printf("%c ", matrix[i][c]);
        printf("\n");
    }

    printf("\nEncrypted text: %s\n", encrypted);

    return 0;
}