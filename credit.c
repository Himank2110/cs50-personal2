#include <stdio.h>
#include <cs50.h>

int main()
{
    long n, x, y, total = 0, sum = 0;
    n = get_long("Enter your card number : ");
    x = n%100; //code for checksum
    while (x>1)
    {
        x = x * 2;
        if(x>9)
        {
            for(int i=0;i<2;i++)
            {
                sum = sum + x%10;
            }
        }
        else
        {
            sum = sum + x;
        }
        x = n % 100;
    }
    printf("sum is %ld", sum);
    total = sum;
    y = n;
    total = total + y % 10;
    while(y>1)
    {
        total = total + y % 100;
    }

    if (total % 10 == 0)
    {
        printf("valid\n");
    }
    else
    {
        printf("invalid\n");
    }
    return (0);
}
