#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string sub(string text, string cipher, string key, int n);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }
    int n = strlen(argv[1]);
    // check validity of key given
    if (n != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0; i < n; i++)
    {
        int k = (int) argv[1][i];
        if (!((65 <= k && k <= 90) || (97 <= k && k <= 122)))
        {
            printf("Key must contain only alphabetic characters.\n");
            return 1;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; i != j && j < n; j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }
    int l = 0;
    char key[27];
    do
    {
             key[l] = toupper((int) argv[1][l]);
        l++;
    }
    while(argv[1][l] != '\0');
    key[l] = '\0';

    string plaintext = get_string("plaintext:  ");
    int m = strlen(plaintext);
    char ciphertext[27];
    sub(plaintext, ciphertext, key, m);
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}


string sub(string text, string cipher, string key, int n)
{
    int l = 0, k;
    char key2[27];
    do
    {
        key2[l] = tolower((int) key[l]);
        l++;
    }
    while(key[l] != '\0');
    char ctext[n];
    for (int i = 0; i < n; i++)
    {
        k = (int) text[i];
        if (65 <= k && k <= 90)
        {
            ctext[i] = key[k - 65];
        }
        else if (97 <= k && k <= 122)
        {
            ctext[i] = key2[k - 97];
        }
        else
        {
            ctext[i] = text[i];
        }
        ctext[n] = '\0';
    }
    strcpy(cipher, ctext);
    return 0;
}
