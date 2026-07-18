#include <cs50.h>
#include <stdio.h>

#define VISA_CHECK_13 1000000000000
#define VISA_MASTERCARD_CHECK 1000000000000000
#define AMEX_CHECK 100000000000000

void calculate_visa_checksum(long card);
void calculate_mastercard_checksum(long card);
void calculate_amex_checksum(long card);

int main(void)
{
    // Prompt user for credit card number;
    long card;
    do
    {
        card = get_long("Number: ");
    }
    while (card < 0);

    // Check for valid card length
    if (((card / VISA_CHECK_13) > 0) && ((card / VISA_CHECK_13) < 10))
    {
        // Check for valid starting digit
        if (card / VISA_CHECK_13 == 4)
        {
            // Perform VISA checksum calculation (Luhn's Algorithm)
            calculate_visa_checksum(card);
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (((card / VISA_MASTERCARD_CHECK) > 0) && ((card / VISA_MASTERCARD_CHECK) < 10))
    {
        // Check for valid starting digit/s
        if ((card / VISA_MASTERCARD_CHECK) == 4)
        {
            // Perform VISA checksum calculation (Luhn's Algorithm)
            calculate_visa_checksum(card);
        }
        else if (((card / (VISA_MASTERCARD_CHECK / 10)) > 50) &&
                 ((card / (VISA_MASTERCARD_CHECK / 10)) < 56))
        {
            // Perform MASTERCARD checksum calculation (Luhn's Algorithm)
            calculate_mastercard_checksum(card);
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (((card / AMEX_CHECK) > 1) && ((card / AMEX_CHECK) < 10))
    {
        // Check for valid starting digits
        if (card / (AMEX_CHECK / 10) == 34 || card / (AMEX_CHECK / 10) == 37)
        {
            // Perform AMEX checksum calculation (Luhn's Algorithm)
            calculate_amex_checksum(card);
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

void calculate_visa_checksum(long card)
{
    long checksum_card = card;
    int checksum_initial = 0;
    int checksum_secondary = 0;
    int checksum_secondary_product = 0;
    int total_checksum = 0;
    int iterator = 0;

    // Iterate over each digit of supplied card
    while (checksum_card > 0)
    {
        if (iterator % 2 == 0)
        {
            // Add every n digit to one checksum sum
            checksum_initial = checksum_initial + (checksum_card % 10);
        }
        else
        {
            // Add every n+1 digit multiplied by 2 to other checksum sum
            checksum_secondary_product = (checksum_card % 10) * 2;
            // If digit multiplied by 2 is two digits, then add each of those digits together, then
            // add to other checksum sum
            if (checksum_secondary_product > 9)
            {
                checksum_secondary = checksum_secondary + (checksum_secondary_product % 10) +
                                     (checksum_secondary_product / 10);
            }
            else
            {
                // Otherwise, add digit multiplied by 2 to other checksum sum
                checksum_secondary = checksum_secondary + checksum_secondary_product;
            }
        }
        checksum_card = checksum_card / 10;
        iterator = iterator + 1;
    }

    // Add both checksums together
    total_checksum = checksum_initial + checksum_secondary;

    // Check for valid VISA card based on modulus of total checksum
    if (total_checksum % 10 == 0)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

void calculate_mastercard_checksum(long card)
{
    long checksum_card = card;
    int checksum_initial = 0;
    int checksum_secondary = 0;
    int checksum_secondary_product = 0;
    int total_checksum = 0;
    int iterator = 0;

    // Iterate over each digit of supplied card
    while (checksum_card > 0)
    {
        if (iterator % 2 == 0)
        {
            // Add every n digit to one checksum sum
            checksum_initial = checksum_initial + (checksum_card % 10);
        }
        else
        {
            // Add every n+1 digit multiplied by 2 to other checksum sum
            checksum_secondary_product = (checksum_card % 10) * 2;
            // If digit multiplied by 2 is two digits, then add each of those digits together, then
            // add to other checksum sum
            if (checksum_secondary_product > 9)
            {
                checksum_secondary = checksum_secondary + (checksum_secondary_product % 10) +
                                     (checksum_secondary_product / 10);
            }
            else
            {
                // Otherwise, add digit multiplied by 2 to other checksum sum
                checksum_secondary = checksum_secondary + checksum_secondary_product;
            }
        }
        checksum_card = checksum_card / 10;
        iterator = iterator + 1;
    }

    // Add both checksums together
    total_checksum = checksum_initial + checksum_secondary;

    // Check for valid MASTERCARD card based on modulus of total checksum
    if (total_checksum % 10 == 0)
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

void calculate_amex_checksum(long card)
{
    long checksum_card = card;
    int checksum_initial = 0;
    int checksum_secondary = 0;
    int checksum_secondary_product = 0;
    int total_checksum = 0;
    int iterator = 0;

    // Iterate over each digit of supplied card
    while (checksum_card > 0)
    {
        if (iterator % 2 == 0)
        {
            // Add every n digit to one checksum sum
            checksum_initial = checksum_initial + (checksum_card % 10);
        }
        else
        {
            // Add every n+1 digit multiplied by 2 to other checksum sum
            checksum_secondary_product = (checksum_card % 10) * 2;
            // If digit multiplied by 2 is two digits, then add each of those digits together, then
            // add to other checksum sum
            if (checksum_secondary_product > 9)
            {
                checksum_secondary = checksum_secondary + (checksum_secondary_product % 10) +
                                     (checksum_secondary_product / 10);
            }
            else
            {
                // Otherwise, add digit multiplied by 2 to other checksum sum
                checksum_secondary = checksum_secondary + checksum_secondary_product;
            }
        }
        checksum_card = checksum_card / 10;
        iterator = iterator + 1;
    }

    // Add both checksums together
    total_checksum = checksum_initial + checksum_secondary;

    // Check for valid AMEX card based on modulus of total checksum
    if (total_checksum % 10 == 0)
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
