#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    unsigned char word[16];
    FILE *fp;
    fp = fopen("words.txt", "r");
    if(fp == NULL)
    {
        fprintf(stderr, "Could not open file\n");
    }
    for(int i = 0; i <10; i++)
    {
        fgets(word, 16, fp);
        printf("word: %s", word);
        break;
    }
}