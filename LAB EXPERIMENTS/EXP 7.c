#include <stdio.h>
#include <string.h>

int main() {
    char cipher[2000], key[128];
    char plain[128];
    int i;

    for (i = 0; i < 128; i++) {
        key[i] = (char)i;
        plain[i] = (char)i;
    }

    printf("Enter ciphertext:\n");
    fgets(cipher, sizeof(cipher), stdin);

    printf("Enter ciphertext character to replace: ");
    {
        char from;
        scanf("%c", &from);

        printf("Enter corresponding plaintext character: ");
        {
            char to;
            scanf(" %c", &to);
            key[(unsigned char)from] = to;
        }
    }

    printf("Decrypted text:\n");

    for (i = 0; cipher[i] != '\0'; i++) {
        unsigned char ch = (unsigned char)cipher[i];
        putchar(key[ch]);
    }

    return 0;
}