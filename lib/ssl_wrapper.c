#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/hmac.h>
#include <openssl/aes.h>
#include <ssl_wrapper.h>

static unsigned char salt[] = {'s','p','i','d','e','r','o','a','k'};
static unsigned char salt2[] = {'a','e','s','2','5','6','c','b','c'};

int encrypt_to_file(char* pass, char* message, char* filepath)
{
  /**
   * Basic encryption of a message using a passphrase
   * @param pass     The passphrase
   * @param message  The message to encrypt
   * @param filepath The path of a file to which we are writing our encrypted message
   * @return         1 if successful, 0 if not
   */
  
  // Setup key and iv
  unsigned char key[32] = {};
  if (0 == PKCS5_PBKDF2_HMAC_SHA1(pass, strlen(pass), salt, 9, 1, 32, key))
  {
    return 0;
  }

  unsigned char iv[32] = {};
  if (0 == PKCS5_PBKDF2_HMAC_SHA1(pass, strlen(pass), salt2, 9, 1, 32, iv))
  {
    return 0;
  }
  
  // Setup cipher and buffer
  EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
  EVP_CipherInit(ctx, EVP_aes_256_cbc(), key, iv, 1);
  unsigned int blocksize = EVP_CIPHER_CTX_block_size(ctx);
  unsigned char *buf = malloc((sizeof(char)*strlen(message))+blocksize);
  int encrypted_len;

  // Run cipher and write encrypted message
  EVP_CipherUpdate(ctx, buf, &encrypted_len, message, strlen(message));
  FILE *fp = fopen(filepath, "wb");
  fwrite(buf, sizeof(unsigned char), encrypted_len, fp);
  fclose(fp);

  // Run final cipher block an append it
  EVP_CipherFinal(ctx, buf, &encrypted_len);
  fp = fopen(filepath, "ab");
  fwrite(buf, sizeof(unsigned char), encrypted_len, fp);
  fclose(fp);

  // Free relevant memory
  EVP_CIPHER_CTX_free(ctx);
  return 1;
}

int decrypt_from_file(char* pass, char** message, char* filepath)
{
  /**
   * Basic decryption of a file using a passphrase
   * @param pass     The passphrase
   * @param message  A pointer to where the message will be stored
   * @param filepath The path of a file to which contains our encrypted message
   * @return         1 if successful, 0 if not
   */
  
  // Setup key and iv
  unsigned char key[32] = {};
  if (0 == PKCS5_PBKDF2_HMAC_SHA1(pass, strlen(pass), salt, 9, 1, 32, key))
  {
    return 0;
  }

  unsigned char iv[32] = {};
  if (0 == PKCS5_PBKDF2_HMAC_SHA1(pass, strlen(pass), salt2, 9, 1, 32, iv))
  {
    return 0;
  }
  
  // Setup cipher
  EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
  EVP_CipherInit(ctx, EVP_aes_256_cbc(), key, iv, 0);
  unsigned int blocksize = EVP_CIPHER_CTX_block_size(ctx);

  // Setup buffer using size of file
  FILE *fp = fopen(filepath, "rb");
  fseek(fp, 0L, SEEK_END);
  int fsize = ftell(fp);
  char *buf = malloc(sizeof(char)*fsize);
  rewind(fp);

  // Read file into buffer
  fread(buf, sizeof(char), fsize, fp);
  fclose(fp);

  // Prepare message string to receive decrypted message
  int decrypted_len;
  *message = malloc(sizeof(char)*fsize);
  memset(*message, 0, sizeof(char)*fsize);

  // Run cipher
  EVP_CipherUpdate(ctx, *message, &decrypted_len, buf, fsize);
  EVP_CipherFinal(ctx, (*message)+decrypted_len, &decrypted_len);

  // Free relevant memory
  EVP_CIPHER_CTX_free(ctx);
  return 1;
}