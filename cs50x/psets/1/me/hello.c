#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Gets name from user in console and prints the entered name to the console.
    string name = get_string("What's your name? ");
    printf("hello, %s\n", name);
}
