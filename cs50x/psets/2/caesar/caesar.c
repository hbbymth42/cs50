#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string key);

char rotate(char c, int n);

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    if (argc < 2 || argc > 2)
    {
        printf("Usage ./caesar key\n");
        return 1;
    }
    // Make sure every character in argv[1] is a digit
    if (only_digits(argv[1]) == false)
    {
        printf("Usage ./caesar key\n");
        return 1;
    }
    // Convert argv[1] from a `string` to an `int`
    string argument = argv[1];
    int cipher_key = atoi(argv[1]);
    // Prompt user for plaintext
    string plaintext = get_string("plaintext: ");
    // Rotate the character if it's a letter
    printf("ciphertext: ");
    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        printf("%c", rotate(plaintext[i], cipher_key));
    }
    printf("\n");
    return 0;
}

bool only_digits(string key)
{
    // Iterates over provided key
    for (int i = 0, len = strlen(key); i < len; i++)
    {
        // Return false if key is alphabetical
        if (isalpha(key[i]))
        {
            return false;
        }
    }

    return true;
}

char rotate(char c, int n)
{
    // Checks if character is alphabetical, for cipher rotation
    if (isalpha(c))
    {
        // Calculates rotation of character for uppercase letters
        if (isupper(c))
        {
            n = (((int) c - (int) 'A') + n) % 26;

            c = (int) 'A' + n;

            return c;
        }
        else
        {
            // Calculates rotation of character for lowercase letters
            n = (((int) c - (int) 'a') + n) % 26;

            c = (int) 'a' + n;

            return c;
        }
    }
    // If not alphabetical, return original character
    else
    {
        return c;
    }
}
