#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int compute_score(string word);
int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    string p1 = get_string("Player 1: ");
    string p2 = get_string("Player 2: ");

    int s1 = compute_score(p1);
    int s2 = compute_score(p2);

    //print winner
    if (s1 > s2)
    {
        printf("Player 1 wins!\n");
    }
    else if(s1 < s2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie\n");
    }
    return 0;
}

int compute_score(string word)
{
    int i = 0, sum = 0;
    do
    {
        word[i] = toupper(word[i]);
        i++;
    }
    while(word[i] != '\0');

    for (int j = 0, n = strlen(word); j < n; j++)
    {
        for(int k = 0; k < 26; k++)
        {
            if ((int)word[j] - 65 == k)
            {
                sum += points[k];
            }
        }
    }
    return sum;
}
