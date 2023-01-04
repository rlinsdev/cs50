#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);
static void dec_to_binary(int asc_nbr);
void handle_base(string msg);

int main(void)
{
    string msg = get_string("Message: ");
    handle_base(msg);
}

/**
 * @brief While trought all string
 * @param msg String typed by user
 */
void handle_base(string msg)
{
    int i = 0;
    // while all string
    while (msg[i])
    {
        dec_to_binary(msg[i]);
        i++;
    }
}

/**
 * @brief Handle the decimal value to binary value. Get the rest of division
 * to discovery the value.
 * Print in reverse order to be right result
 * @param asc_nbr Number in decimal. Representation of ASCII table
 */
static void dec_to_binary(int asc_nbr)
{
    // Base to calculate. To solve this problem: Base 2
    int base = 2;
    int result[32];
    int i = 0;

    // Until the end of number. If less then 7, add 0 to complete 8 bits representation
    while (asc_nbr > 0 || i < 7)
    {
        // Divided by base, get the rest by division
        result[i] = asc_nbr % base;
        // update number
        asc_nbr = (asc_nbr / base);
        i++;
    }

    // Print reverse order
    while (i >= 0)
    {
        print_bulb(result[i]);
        // printf("%i", result[i]);
        i--;
    }
    // Break line
    printf("\n");
}

/**
 * @brief Responsible to print the emoji. Angram of bulbs (light on / off)
 * @param bit Value 1 or 0
 */
void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
