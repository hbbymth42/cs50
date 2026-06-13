#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Compute the Coleman-Liau index
    float index = (0.0588 * (((float) letters / (float) words) * 100.0)) -
                  (0.296 * (((float) sentences / (float) words) * 100.0)) - 15.8;
    // Print the grade level
    if ((int) round(index) < 1)
    {
        printf("Before Grade 1\n");
    }
    else if ((int) round(index) > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}

int count_letters(string text)
{
    // Return the number of letters in text
    int letters_num = 0;

    // Increments number of letters based on if character is alphanumeric.
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalnum(text[i]))
        {
            letters_num += 1;
        }
    }

    return letters_num;
}

int count_words(string text)
{
    // Return the number of words in text
    int words_num = 0;

    // Increments number of words based on presence of spaces between words
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == ' ')
        {
            words_num += 1;
        }
    }

    // 1 added to include last word
    return words_num + 1;
}

int count_sentences(string text)
{
    // Return the number of sentences in text
    int sentences_num = 0;

    // Increments number of sentences based on presence of 'ending characters' i.e. '.', '!', '?'
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences_num += 1;
        }
    }

    return sentences_num;
}
