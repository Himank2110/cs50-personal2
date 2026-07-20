#include <cs50.h>
#include <stdio.h>

int main()
{
    int n;
    do
    {
        n = get_int("Enter desired height : ");
    }
    while (n < 1 || n > 8);
    for (int row = 1; row <= n; row++) // outer loop to handle rows
    {
        for (int col = 1; col <= n - row; col++) // inner loop to print beginning spaces
        {
            printf(" ");
        }
        for (int k = 1; k <= row; k++) // inner loop to print left side blocks(#)
        {
            printf("#");
        }

        printf("  "); // adds 2 block spaace b/w the left and right sides

        for (int k = 1; k <= row; k++) // right side loop for blocks
        {
            printf("#");
        }
        printf("\n");
    }
    return (0);
}
