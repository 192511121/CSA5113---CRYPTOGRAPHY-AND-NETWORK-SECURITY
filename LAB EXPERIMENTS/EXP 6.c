#include <stdio.h>
#include <string.h>
#include <ctype.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int modInverse(int a) {
    int i;

    for (i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1)
            return i;
    }

    return -1;
}

int main() {
    char text[500];
    int a, b, inv, i, c, p;

    printf("Enter ciphertext: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter key a: ");
    scanf("%d", &a);

    printf("Enter key b: ");
    scanf("%d", &b);

    a = (a % 26 + 26) % 26;
    b = (b % 26 + 26) % 26;

    if (gcd(a, 26) != 1) {
        printf("Invalid key: a must be coprime to 26.\n");
        return 1;
    }

    inv = modInverse(a);

    printf("Decrypted text: ");

    for (i = 0; text[i] != '\0'; i++) {
        if (isupper((unsigned char)text[i])) {
            c = text[i] - 'A';
            p = (inv * (c - b + 26)) % 26;
            printf("%c", p + 'A');
        }
        else if (islower((unsigned char)text[i])) {
            c = text[i] - 'a';
            p = (inv * (c - b + 26)) % 26;
            printf("%c", p + 'a');
        }
        else {
            printf("%c", text[i]);
        }
    }

    return 0;
}