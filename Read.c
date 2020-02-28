#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <stdio.h>
<<<<<<< HEAD

int main (void)
{    
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
}
=======
int main(void)
{
   /* A 128 bit key */
   /*unsigned char *key = (unsigned char *)"0123456789012345";*/
   unsigned char *key;
   /* A 128 bit IV */
   /*unsigned char *iv = (unsigned char *)"0123456789012345";*/
   unsigned char iv[16] = { 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11 };

   /* Message to be encrypted */
   unsigned char *plaintext =
      (unsigned char *)"This is lab1 in CS3840.";

   unsigned char ciphertext[128];

   unsigned char *outputText;
   FILE *stream;
   char *line = NULL;
   size_t len = 0;
   ssize_t read;

   stream = fopen("words.txt", "r");
   if (stream == NULL)
      exit(EXIT_FAILURE);

   while ((read = getline(&line, &len, stream)) != -1)
   {
      key = (unsigned char*)read;
      //printf("Retrieved line of length %u :\n", read);
      //printf("%s", line);
      encrypt(plaintext, sizeof(ciphertext), key, iv, ciphertext);

      if (strcmp(outputText, plaintext) == 0)
      {
         printf("The Key used is: %s ", line);
         break;
      }
      else
      {
         printf("this doesnt work\n");
      }
   }
}
int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
   unsigned char *iv, unsigned char *ciphertext)
{
   EVP_CIPHER_CTX *ctx;

   int len;

   int ciphertext_len;

   /* Create and initialise the context */
   if (!(ctx = EVP_CIPHER_CTX_new()))
      handleErrors();

   /*
    * Initialise the encryption operation. IMPORTANT - ensure you use a key
    * and IV size appropriate for your cipher
    * In this example we are using 256 bit AES (i.e. a 256 bit key). The
    * IV size for *most* modes is the same as the block size. For AES this
    * is 128 bits
    */
   if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
      handleErrors();

   /*
    * Provide the message to be encrypted, and obtain the encrypted output.
    * EVP_EncryptUpdate can be called multiple times if necessary
    */
   if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
      handleErrors();
   ciphertext_len = len;

   /*
    * Finalise the encryption. Further ciphertext bytes may be written at
    * this stage.
    */
   if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
      handleErrors();
   ciphertext_len += len;

   /* Clean up */
   EVP_CIPHER_CTX_free(ctx);

   return ciphertext_len;
}

void handleErrors(void)
{
   ERR_print_errors_fp(stderr);
   abort();
}

>>>>>>> 815ab3168d06334e7d71fb6bca56270d37ca6035
