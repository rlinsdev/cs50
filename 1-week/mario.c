#include <cs50.h>
#include <stdio.h>

void print_blocks(int size);
bool valid_input(int size);
void init(void);

int main(void)
{
    init();
}

/**
 * @brief Will initialize the project. Call methods to validate and print blocks
 */
void init(void)
{
    int size = get_int("Height: ");
    bool is_valid = valid_input(size);

    if (is_valid == true)
    {
        int i = 0;
        while (size > 0)
        {
            print_blocks(i++);
            size--;
            printf("\n");
        }
    }
    else
    {
        init();
    }
}

/**
 * @brief Handle the print blocks
 * @param size Size to print block
 */
void print_blocks(int size)
{
    int i = 0;
    while (i <= size)
    {
        printf("#");
        i++;
    }
}

/**
 * @brief Validate the input passed by user
 * @param size - Size typed by user
 * @return boolean - Valid or invalid
 */
bool valid_input(int size)
{
    if (size >= 1 && size <= 8)
        return (true);
    else
        return (false);
}
