#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

static void validate_args(int argc);
static FILE *get_file(string file_path);

// # define BLOCK_SIZE 512;
const int BLOCK_SIZE = 512;
typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    validate_args(argc);
    // char buffer = [BLOCK_SIZE];

    // string file_path = argv[1];
    string file_path = "/home/rlins/Projects/cs50-delivery/4-week/problem/recover/card.raw";

    // Open Memory card
    // FILE *memory_card = get_file(file_path);
    FILE *memory_card = fopen(file_path, "r");
    if (memory_card == NULL)
    {
        printf("Could not open %s\n", file_path);
        exit(2);
    }
    BYTE buffer[BLOCK_SIZE];

    while (fread(buffer, 1, BLOCK_SIZE,memory_card) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2]==0xff)
        {
            // TODO Faltam 16
            // if(buffer[3] == 0xe0 || buffer[3] == 0xe1)
            if((buffer[3] & 0xf0) == 0xe0)
            {

                // sprintf(filename, "%03i.jpg", 2);
                // FILE *img = fopen(filename, "w");
                // fclose(img);

                // fwrite

            }
        }
    }

    // Look for images

    // Open

    // Write this files

    fclose(memory_card);

    return (0);
}

/**
 * @brief Get the file object
 *
 * @param file_path
 * @return FILE*
 */
static FILE *get_file(string file_path)
{
    FILE *memory_card = fopen(file_path, "r");
    if (memory_card == NULL)
    {
        printf("Could not open %s\n", file_path);
        exit(2);
    }
    return memory_card;
}

/**
 * @brief
 *
 * @param argc
 */
static void validate_args(int argc)
{
    if (argc != 2)
    {
        printf("Parameters invalid.\n");
        exit(1);
    }
}

