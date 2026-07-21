#include <stdio.h>
#include <cs50.h>

int main()
{
    long temp, n, x, y, i, total = 0, sum = 0, c = 0;

 //code for checksum
        n = get_long("Enter your card number : ");
        temp = n;
        temp = temp * 10;
            while (temp>0)
            {
                temp = temp / 100;
                x = temp % 10;
                x = x * 2;
                if(x>9)
                {
                    for(i=0;i<2;i++)
                    {
                        sum = sum + x%10;
                        x = x/10;
                    }
                }
                else
                {
                    sum = sum + x;
                }

            }
        total = sum;
        temp = n;
        y = n;
        total = total + y % 10;
        while(temp>0)
        {
            temp = temp / 100;
            y = temp % 10;
            total = total + y;
        }

    if(total % 10 == 0)
    {
    // code for checking type of card
        i = 0;
        temp = n;
        do  //count no. of digits
        {
            temp = temp / 10;
            i++;
        }
        while(temp>0);
        do  //get the first 2 digits
        {
            n = n/10;
        }
        while(n>=100);
//conditionals for each type of card
        if(i == 15 && (n == 34 || n == 37))
        {
            printf("AMEX\n");
        }
        else if(i == 16 && (n ==51 || n == 52 || n == 53 || n == 54 || n == 55))
        {
            printf("MASTERCARD\n");
        }
        else if((i == 13 || i == 16) && (n%10 == 4))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    return (0);
}
