#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Get the name
    string name = get_string("Whats your name?\n");
    // Printf to return the message
    printf("Hello, %s\n", name);
}
