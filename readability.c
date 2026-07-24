#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string text = get_string("Text: ");
    int i = 0, l = 0, w = 1, s = 0;
    do
    {
        int k = (int) text[i];
        if ((65 <= k && k <= 90) || (97 <= k && k <= 122)) // calculates no. of letters
        {
            l++;
        }
        if (text[i] == ' ') // calculates no. of words
        {
            w++;
        }
        if (text[i] == '.' || text[i] == '!' || text[i] == '?') // calculates no. of sentences
        {
            s++;
        }
        i++;
    }
    while (text[i] != '\0');
    // claculating avarage per 100 words
    float L = l * 100 / (float) w;
    float S = s * 100 / (float) w;
    // calculating Coleman-Liau index
    float index = 0.0588 * L - 0.296 * S - 15.8;
    // calculating grade level
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) roundf(index));
    }
}
