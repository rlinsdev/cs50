#include <cs50.h>
#include <stdio.h>

void print_blocks(int size);
bool valid_input(int size);

//gcc mario.c -lcs50 -o mario.out

int main(void)
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
        main();
    }
}

void print_blocks(int size)
{
    int i = 0;
    while (i <= size)
    {
        printf("#");
        i++;
    }
}

bool valid_input(int size)
{
    if (size >= 1 && size <= 8)
        return (true);
    else
        return (false);
}
