#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int compute_score(string word);
    //string for storing points
int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    //get words from both players
    string p1 = get_string("Player 1: ");
    string p2 = get_string("Player 2: ");

    //calculate and store score for both players

    int s1 = compute_score(p1);
    int s2 = compute_score(p2);

    //compare score and print winner
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

    //make entire string uppercase for comparision

    do
    {
        word[i] = toupper(word[i]);
        i++;
    }
    while(word[i] != '\0');

    //two loops for checking each letter of given word with each of the 0 to 25 index numbers on points[]

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
