#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/hmac.h>
#include <openssl/aes.h>
#include <ssl_wrapper.h>

static unsigned char salt[] = {'s','p','i','d','e','r','o','a','k'};

int encrypt_to_file(char* pass, char* message, char* filepath)
{
  /**
   * Basic encryption of a message using a passphrase
   * @param pass     The passphrase
   * @param message  The message to encrypt
   * @param filepath A pointer where we are passing back our encrypted message
   * @return         1 if successful, 0 if not
   */
  
  // Setup encryption
  unsigned char key[32] = {};
  if (0 == PKCS5_PBKDF2_HMAC_SHA1(pass, strlen(pass), salt, 9, 1, 32, key))
  {
    return 0;
  }
  
  // TODO: Actually encrypt/write file, above is just generating key from passphrase

}