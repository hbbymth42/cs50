#include <cs50.h>
#include <stdio.h>

void print_row(int spaces, int bricks);

int main(void)
{
    // Prompt the user for the pyramid's height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1);

    // Print a pyramid of the specified height
    for (int i = 1; i <= height; i++)
    {
        // Print row of bricks
        print_row(height - i, i);
    }
}

void print_row(int spaces, int bricks)
{
    // Print spaces
    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }
    // Print bricks
    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
    printf("\n");
}
