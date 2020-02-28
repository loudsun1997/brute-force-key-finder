    unsigned char* outputText;
    FILE *stream;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    stream = fopen("words.txt", "r");
    if (stream == NULL)
       exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, stream)) != -1)
    {
       //printf("Retrieved line of length %u :\n", read);
       //printf("%s", line);
       decrypt(ciphertext, sizeof(ciphertext), read, iv, outputText);

       if (strcmp(outputText, plaintext) == 0)
       {
          printf("The Key used is: %u ", line);
          break;
       }
    }
