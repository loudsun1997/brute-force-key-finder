#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    /*
     * Set up the key and iv. 
     */

    /* A 256 bit key */
    unsigned char *key;
    /* A 128 bit IV */
    unsigned char iv[16] = {0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11};

    /* Message to be encrypted */
    unsigned char *plaintext = (unsigned char *)"This is lab1 in CS3840.";
    unsigned char givenCipherText[128] = {0x6b, 0x64, 0x2b, 0x4d, 0x23, 0x2d, 0x28, 0xfb, 0x92, 0x72, 0xd3, 0xaa, 0xe0, 0x53, 
      0xd6, 0x41, 0x0e, 0xf9, 0xdf, 0xb2, 0x67, 0xbb, 0xb9, 0xd9, 0xad, 0xcf, 0xee, 0x0f, 0x2d, 0x82, 0x3f, 0x14};

    /*
     * Buffer for ciphertext. Ensure the buffer is long enough for the
     * ciphertext which may be longer than the plaintext, depending on the
     * algorithm and mode.
     */
    unsigned char ciphertext[128];
  
    /*
     * Getting the keys
     */
    unsigned char word[16];
    FILE *fp;
    fp = fopen("words.txt", "r");
    if (fp == NULL)
    {
       fprintf(stderr, "Could not open file\n");
    }


    char *buffer;
    size_t read;
    size_t bufsize  = 16;

    buffer = (char *)malloc(bufsize * sizeof(char));
    //while (fgets(word, 17, fp))


    FILE *stream;
    stream = fopen("output.txt", "w+");

    while ((read = getline(&buffer, &bufsize, fp)) != -1) 
    {
       /* Buffer for the decrypted text */
       
       key = (unsigned char *)buffer;
    //    key=(unsigned char *)"nature##########";

       int ciphertext_len;

       /* Encrypt the plaintext */
       ciphertext_len = encrypt(plaintext, strlen((char *)plaintext), key, iv,
          ciphertext);

    // Print out the ciphertext converted into hex from binary
    for(int i = 0; i < ciphertext_len; i++)
    {
        printf("%02x", ciphertext[i]);
    }
    

    // Dump all the ciphertexts into the output file for further investigation
    BIO_dump_fp (stream, (const char *)ciphertext, ciphertext_len);
    }

    return 0;
}

void handleErrors(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
            unsigned char *iv, unsigned char *ciphertext)
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int ciphertext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    /*
     * Initialise the encryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
        handleErrors();

    /*
     * Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        handleErrors();
    ciphertext_len = len;

    /*
     * Finalise the encryption. Further ciphertext bytes may be written at
     * this stage.
     */
    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        handleErrors();
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
            unsigned char *iv, unsigned char *plaintext)
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int plaintext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    /*
     * Initialise the decryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
        handleErrors();

    /*
     * Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_DecryptUpdate can be called multiple times if necessary.
     */
    if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        handleErrors();
    plaintext_len = len;

    /*
     * Finalise the decryption. Further plaintext bytes may be written at
     * this stage.
     */
    if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
        handleErrors();
    plaintext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}
