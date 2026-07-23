// Implements a dictionary's functionality

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Number of words in dictionary
int num_words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hash_index_check = hash(word);

    node *check = table[hash_index_check];

    while (check != NULL)
    {
        if (strcasecmp(check->word, word) == 0)
        {
            return true;
        }

        check = check->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Improve this hash function - Arithmetic Mean
    float a_mean = 0.0;
    float g_mean = 0.0;
    int final_index = 0;
    int word_len = strlen(word);
    for (int i = 0; i < word_len; i++)
    {
        a_mean = a_mean + (float) (toupper(word[i]) - 'A');
        g_mean = g_mean + log2((float) (toupper(word[i]) - 'A'));
    }

    a_mean = a_mean / (float) word_len;
    g_mean = pow((g_mean / (float) word_len), 2);
    final_index = (int) round(((a_mean + g_mean) / 2));

    if (final_index > N - 1)
    {
        final_index = N - 1;
    }
    return final_index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }

    char *dict_word = malloc(LENGTH + 1);
    int hash_index = 0;
    // Read each word in the file
    while (fscanf(source, "%s", dict_word) != EOF)
    {
        // Add each word to the hash table
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, dict_word);

        hash_index = hash(dict_word);

        n->next = table[hash_index];

        table[hash_index] = n;

        num_words = num_words + 1;
    }

    // Close the dictionary file
    fclose(source);
    free(dict_word);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return num_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];

        while (ptr != NULL)
        {
            node *tmp = ptr;
            ptr = ptr->next;
            free(tmp);
        }
    }
    return true;
}
