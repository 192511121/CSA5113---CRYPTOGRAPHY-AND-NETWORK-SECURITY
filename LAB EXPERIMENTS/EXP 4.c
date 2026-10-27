#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char text[200], key[200];
    int i, j = 0, klen;

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);

    // Remove newline from the key
    key[strcspn(key, "\n")] = '\0';

    klen = strlen(key);

    if (klen == 0) {
        printf("Key cannot be empty!\n");
        return 1;
    }

    // Check whether the key contains only letters
    for (i = 0; i < klen; i++) {
        if (!isalpha((unsigned char)key[i])) {
            printf("Key must contain only alphabets!\n");
            return 1;
        }
    }

    printf("Encrypted text: ");

    for (i = 0; text[i] != '\0'; i++) {
        char ch = text[i];

        if (isupper((unsigned char)ch)) {
            int p = ch - 'A';
            int k = toupper((unsigned char)key[j % klen]) - 'A';

            printf("%c", (p + k) % 26 + 'A');
            j++;
        }
        else if (islower((unsigned char)ch)) {
            int p = ch - 'a';
            int k = toupper((unsigned char)key[j % klen]) - 'A';

            printf("%c", (p + k) % 26 + 'a');
            j++;
        }
        else {
            printf("%c", ch);
        }
    }

    return 0;
}