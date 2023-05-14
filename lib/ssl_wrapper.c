#include <stdio.h>
#include <stdlib.h>
#include <ssl_wrapper.h>

int encrypt(int key_len, char* key, int message_len, char* message, char *encoded_message)
{
  if (key_len <= 0 || message_len <= 0)
  {
    return -1;
  }

  return -1;
}