#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string cipher_text(string text, int key);
bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    if (only_digits(argv[1]) == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]);
    string text = get_string("Plain text:  ");

    cipher_text(text, key);

    printf("ciphertext: %s\n", text);
    return 0;
}

string cipher_text(string text, int key)
{
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        text[i] = rotate(text[i], key);
    }
    return 0;
}

bool only_digits(string s)
{
    bool result = true;

    for (int i = 0, len = strlen(s); i < len; i++)
    {
        if (!isdigit(s[i]))
        {
            printf("'%c' is not a Number\n", s[i]);
            result = false;
        }
    }
    return result;
}

char rotate(char c, int n)
{

    if (c >= 'a' && c <= 'z')
    {
        return ((c - 'a' + n) % 26) + 'a';
    }
    else if (c >= 'A' && c <= 'Z')
    {
        return ((c - 'A' + n) % 26) + 'A';
    }
    else
    {
        return c;
    }
}