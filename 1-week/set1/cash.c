#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);
static int handle_coins(int cents, int base);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    return cents;
}
/**
 * @brief (25C)
 *
 * @param cents
 * @return int
 */
int calculate_quarters(int cents)
{
    return handle_coins(cents, 25);
}

/**
 * @brief (10C)
 * @param cents
 * @return int
 */
int calculate_dimes(int cents)
{
    return handle_coins(cents, 10);
}

/**
 * @brief (5C)
 * @param cents
 * @return int
 */
int calculate_nickels(int cents)
{
    return handle_coins(cents, 5);
}

/**
 * @brief (1C)
 * @param cents
 * @return int
 */
int calculate_pennies(int cents)
{
    return handle_coins(cents, 1);
}

/**
 * @brief Handle the coins to return. Will calculate verify the base passed
 * @param cents value of cents
 * @param base Base to handle the calc
 * @return int Number of coins
 */
static int handle_coins(int cents, int base)
{
    int i = 0;
    while (cents > 0 && (cents / base) > 0)
    {
        cents = cents - base;
        i++;
    }
    return i;
}
