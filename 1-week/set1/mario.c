#include <cs50.h>
#include <stdio.h>

void print_blocks(int size, int full_size);
bool valid_input(int size);
void init(void);

//gcc -g mario.c -lcs50 -o mario
int main(void)
{
    init();
}

/**
 * @brief Will initialize the project. Call methods to validate and print blocks
 * With this method, I'm able to call again the method instead to put a do while
 */
void init(void)
{
    int size = get_int("Height: ");
    bool is_valid = valid_input(size);
    int const c_size = size;
    // If valid, print the bocks
    if (is_valid == true)
    {
        int i = 0;
        while (size > 0)
        {
            print_blocks(i++, c_size);
            // Decrement size to loop
            size--;
            printf("\n");
        }
    }
    else
    {
        // Initialize again, until digit something correct
        init();
    }
}

/**
 * @brief Handle the print blocks
 * @param size Size to print block
 */
void print_blocks(int size, int full_size)
{
    // Fill by blank until full size. j start with 1
    int j = 1;
    while (j < (full_size - size))
    {
        // Fill with white space
        printf(" ");
        j++;
    }

    int i = 0;
    while (i <= size)
    {
        // Print Block
        printf("#");
        i++;
    }
}

/**
 * @brief Validate the input passed by user. Must be between 1 and 9
 * @param size - Size typed by user
 * @return boolean - Valid or invalid
 */
bool valid_input(int size)
{
    if (size >= 1 && size <= 8)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}
