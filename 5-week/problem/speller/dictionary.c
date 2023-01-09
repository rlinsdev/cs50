// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
    long int size;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 650;
unsigned int g_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *aux = table[hash(&word[0])];

    while (aux)
    {
        // strcasecmp: 0 is equivalent
        if (strcasecmp(aux->word, word) == 0)
        {
            return (true);
        }
        aux = aux->next;
    }
    return (false);
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int result = 0;
    int i = 0;
    while (word[i] && i < 2)
    {
        // Just 1 letter: First place in table
        if (!word[i + 1])
        {
            result = toupper(word[0]) - 'A';
            break;
        }
        else
        {
            if (i == 0)
            {
                result = (toupper(word[i]) - 'A') * 25;
            }
            else
            {
                result += (toupper(word[i]) - 'A') + 26;
            }
        }
        i++;
    }
    return result;
}

static FILE *get_file(const char *file_path);
bool load(const char *dictionary)
{
    // Get the file
    FILE *dic_file = get_file(dictionary);
    if (dic_file == NULL)
    {
        return (false);
    }
    char word[LENGTH + 1];

    // Read while diff EndOfFile
    while (fscanf(dic_file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Allocate memory problem");
            return (false);
        }
        n->next = NULL;
        strncpy(n->word, word, strlen(word));
        // Get Hash Code
        unsigned int hash_code = hash(&word[0]);
        // Verify is this is the first register in hash table
        if (table[hash_code] == NULL)
        {
            // Just add node
            table[hash_code] = n;
        }
        else
        {
            // Add node in the begin.
            node *aux = malloc(sizeof(node));
            aux = table[hash_code];
            table[hash_code] = n;
            // Fixing the appointment
            n->next = aux;
        }
        g_count++;
    }
    return (true);
}

/**
 * @brief Get File. Path passed by param, in argv
 * @param file_path Path of file to analyze
 * @return FILE* object
 */
static FILE *get_file(const char *file_path)
{
    FILE *dic_file = fopen(file_path, "r");
    if (dic_file == NULL)
    {
        printf("Could not open %s\n", file_path);
        exit(2);
    }
    return dic_file;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return (g_count);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    bool result = false;
    for (int i = 0; i < N; i++)
    {
        if (table[i])
        {
            while (table[i])
            {
                node *temp = table[i];
                free(temp);
                temp = NULL;
                table[i] = table[i]->next;
            }
            result = true;
            free(table[i]);
            table[i] = NULL;
        }
    }
    return (result);
}
