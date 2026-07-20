#include <cs50.h>
#include <stdio.h>

int main()
{
    string name = get_string("What's your name? "); // asks user for their name
    printf("hello, %s", name);                      // says hello to the user using their name
    printf("\n");
    return (0);
}

