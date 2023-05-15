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
  
  // Setup encryption
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
  
  EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
  EVP_CipherInit(ctx, EVP_aes_256_cbc(), key, iv, 1);
  unsigned int blocksize = EVP_CIPHER_CTX_block_size(ctx);
  unsigned char *buf = malloc((sizeof(char)*strlen(message))+blocksize);
  int encrypted_len;
  EVP_CipherUpdate(ctx, buf, &encrypted_len, message, strlen(message));

  FILE *fp = fopen(filepath, "wb");
  fwrite(buf, sizeof(unsigned char), encrypted_len, fp);
  fclose(fp);

  EVP_CIPHER_CTX_free(ctx);
  return 1;
}