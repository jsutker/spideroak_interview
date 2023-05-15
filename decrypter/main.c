#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include <ssl_wrapper.h>

int main(int argc, char **argv)
{
  /**
   * Process flags/arguments to be encrypted
   * @param argc Argument count
   * @param argv The arguments given
   * @return     A potential error code (1 if a problem arose, 0 if successful)
   */
  int flag;
  char* key = NULL;
  char* message = NULL;
  char* input_filepath = NULL;

  while ((flag = getopt(argc, argv, "hk:i:")) != -1)
  {
    switch (flag)
    {
    case 'k':
      key = optarg;
      break;
    case 'i':
      input_filepath = optarg;
    case 'h':
      printf("Possible options:\n\
  -h    The help menu (this output)\n\
  -k    The key to encode with\n\
  -i    The path of the input file (./encrypted_message if left blank)\n");
      return 1;
    default:
      abort();
    }
  }

  if (key == NULL)
  {
    printf("Failed to decrypt: Must provide key\n");
    return 1;
  }
  if (input_filepath == NULL)
  {
    input_filepath = "encrypted_message";
  }

  if (decrypt_from_file(key, &message, input_filepath))
  {
    printf("%s\n", message);
    return 0;
  }
  else
  {
    printf("Failed to decrypt\n");
    return 1;
  }
}