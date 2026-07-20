#include <cs50.h>
#include <stdio.h>

int main()
{
    int n;
    do
    {
      n = get_int("Enter desired height : ");
    }
    while(n<1 || n>8);
    for(int row=1; row<=n; row++)
    {
        for(int col=0; col<=n-row; col++)
        {
            printf(" ");
        }
        for(int k=1; k<=row; k++)
        {
            printf("#");
        }

        printf("  ");

        for(int k=1; k<=row; k++)
        {
            printf("#");
        }
        printf("\n");
    }
    return (0);
}
