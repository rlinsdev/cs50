#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

typedef uint8_t  BYTE;
const int BLOCK_SIZE = 512;

static void validate_args(int argc);
static FILE *get_file(string file_path);
void write_file(int i, char file_name[8], BYTE buffer[BLOCK_SIZE], FILE *img);

int main(int argc, char *argv[])
{
    validate_args(argc);

    string file_path = argv[1];
    // string file_path = "/home/rlins/Projects/cs50-delivery/4-week/problem/recover/card.raw";

    // Open Memory card
    FILE *memory_card = get_file(file_path);
    // Size buffer
    BYTE buffer[BLOCK_SIZE];
    FILE *img = NULL;

    int i = 0;
    char file_name[8];
    // Read trunk of 512 bytes
    while (fread(buffer, 1, BLOCK_SIZE, memory_card) == BLOCK_SIZE)
    {
        // All .jpg files
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close previous file
            if (i > 0)
            {
                fclose(img);
            }
            // Generate a name
            sprintf(file_name, "%03i.jpg", i);
            img = fopen(file_name, "w");
            fwrite(buffer, BLOCK_SIZE, 1, img);
            i++;
        }
        else if (i > 0)
        {
            // Add more data in file / more part of photos
            fwrite(buffer, BLOCK_SIZE, 1, img);
        }
    }
    // Close objects
    fclose(img);
    fclose(memory_card);
    return (0);
}

/**
 * @brief Get File. Path passed by param, in argv
 * @param file_path Path of file to analyze
 * @return FILE* object
 */
static FILE *get_file(string file_path)
{
    FILE *memory_card = fopen(file_path, "r");
    if (memory_card == NULL)
    {
        printf("Could not open %s\n", file_path);
        exit(1);
    }
    return memory_card;
}

/**
 * @brief Validate params
 * @param argc Arg count
 */
static void validate_args(int argc)
{
    if (argc != 2)
    {
        printf("Parameters invalid.\n");
        exit(1);
    }
}
