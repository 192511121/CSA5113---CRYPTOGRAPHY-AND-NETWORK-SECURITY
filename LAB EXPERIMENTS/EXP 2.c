#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char text[100], key[100];
    int i, j, valid = 1;
    int seen[26] = {0};

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter 26-letter substitution alphabet: ");
    scanf("%99s", key);

    if (strlen(key) != 26) {
        printf("Invalid key! Enter exactly 26 letters.\n");
        return 1;
    }

    for (i = 0; i < 26; i++) {
        key[i] = (char)toupper((unsigned char)key[i]);

        if (key[i] < 'A' || key[i] > 'Z') {
            valid = 0;
            break;
        }

        j = key[i] - 'A';

        if (seen[j]) {
            valid = 0;
            break;
        }

        seen[j] = 1;
    }

    if (!valid) {
        printf("Invalid key! Letters must be unique A-Z.\n");
        return 1;
    }

    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = key[text[i] - 'A'];
        }
        else if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = (char)tolower(
                (unsigned char)key[text[i] - 'a']
            );
        }
    }

    printf("Encrypted text: %s", text);

    return 0;
}