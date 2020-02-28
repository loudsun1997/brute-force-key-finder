#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    unsigned char word[16];
    FILE *fp;
    fp = fopen("word.txt", "r");
    if(fp == NULL)
    {
        fprintf(stderr, "Could not open file\n");
    }
    while(fgets(word, 16, fp))
    {
        printf("word: %s", word);
    }

}