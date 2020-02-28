#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <stdio.h>
int main(void)
{
   /* A 128 bit key */
   /*unsigned char *key = (unsigned char *)"0123456789012345";*/
   unsigned char *key;
   /* A 128 bit IV */
   /*unsigned char *iv = (unsigned char *)"0123456789012345";*/
   unsigned char iv[16] = {0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11};

   /* Message to be encrypted */
   unsigned char *plaintext =
      (unsigned char *)"This is lab1 in CS3840.";

   unsigned char ciphertext[128] = {0x6b, 0x64, 0x2b, 0x4d, 0x23, 0x2d, 0x28, 0xfb, 0x92 0x72, 0xd3, 0xaa, 0xe0, 0x53, 
      0xd6, 0x41, 0x0e, 0xf9, 0xdf, 0xb2, 0x67, 0xbb, 0xb9, 0xd9, 0xad 0xcf, 0xee, 0x0f, 0x2d, 0x82, 0x3f, 0x14};
   
   unsigned char *outputText;

   unsigned char word[16];
   FILE *fp;
   fp = fopen("word.txt", "r");
   if (fp == NULL)
   {
      fprintf(stderr, "Could not open file\n");
   }
   while (fgets(word, 16, fp))
   {
      printf("word: %s", word);
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

