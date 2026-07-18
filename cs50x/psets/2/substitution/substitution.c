#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_LENGTH 26

bool only_alphabet(string key);

bool check_unique(char array[ALPHABET_LENGTH]);

char substitute(char c, char array[ALPHABET_LENGTH]);

int main(int argc, string argv[])
{
    char substitution_key[ALPHABET_LENGTH];
    // Make sure program was run with just one command-line argument
    if (argc < 2 || argc > 2)
    {
        printf("Usage ./substitution key\n");
        return 1;
    }
    // Make sure every character in argv[1] is alphabetical
    if (only_alphabet(argv[1]) == false)
    {
        printf("Usage ./substitution key\n");
        return 1;
    }
    // Make sure length of key is ALPHABET_LENGTH
    if (strlen(argv[1]) != ALPHABET_LENGTH)
    {
        printf("Key must contain %i characters\n", ALPHABET_LENGTH);
        return 1;
    }
    // Create substitution array (and make all characters capitalised)
    for (int i = 0, len = ALPHABET_LENGTH; i < len; i++)
    {
        // If character in substitution key is lowercase, make uppercase and add to substitution key
        // array
        if (islower(argv[1][i]))
        {
            substitution_key[i] = argv[1][i] - 32;
        }
        else
        {
            substitution_key[i] = argv[1][i];
        }
    }
    // Make sure every character in substitution key array is unique
    if (check_unique(substitution_key) == false)
    {
        printf("Key must contain %i unique characters\n", ALPHABET_LENGTH);
        return 1;
    }
    // Prompt user for plaintext
    string plaintext = get_string("plaintext: ");
    // Substitute user-provided plaintext to substituted ciphertext
    printf("ciphertext: ");
    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        printf("%c", substitute(plaintext[i], substitution_key));
    }
    printf("\n");
    return 0;
}

bool only_alphabet(string key)
{
    // Iterates over provided key
    for (int i = 0, len = strlen(key); i < len; i++)
    {
        // Return false if key is not alphabetical
        if (!isalpha(key[i]))
        {
            return false;
        }
    }

    return true;
}

bool check_unique(char array[ALPHABET_LENGTH])
{
    int num_letters = 0;
    // Iterates over each letter in key array
    for (int i = 0, i_len = ALPHABET_LENGTH; i < i_len; i++)
    {
        num_letters = 0;
        // Count number of times a letter appears in key
        for (int j = 0, j_len = ALPHABET_LENGTH; j < j_len; j++)
        {
            // Count each time a letter is present in the key array
            if (array[i] == array[j])
            {
                num_letters = num_letters + 1;
            }
        }
        // Where the letter appears more than once, key is invalid
        if (num_letters > 1)
        {
            return false;
        }
    }
    // If all checks pass, there are no duplicate values
    return true;
}

char substitute(char c, char array[ALPHABET_LENGTH])
{
    // If character non-alphabetical, return the original character
    if (!isalpha(c))
    {
        return c;
    }
    // If character is lowercase, make uppercase, check for substitution character, then convert
    // back to lowercase character
    else if (islower(c))
    {
        c = c - 32;
        c = array[c - 'A'] + 32;
        return c;
    }
    // If character is uppercase, check for substitution character and return substitution character
    else
    {
        c = array[c - 'A'];
        return c;
    }
}
