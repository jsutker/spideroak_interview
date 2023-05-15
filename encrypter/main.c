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
  char* output_filepath = NULL;

  while ((flag = getopt(argc, argv, "hk:m:o:")) != -1)
  {
    switch (flag)
    {
    case 'k':
      key = optarg;
      break;
    case 'm':
      message = optarg;
      break;
    case 'o':
      output_filepath = optarg;
    case 'h':
      printf("Possible options:\n\
  -h    The help menu (this output)\n\
  -k    The key to encode with\n\
  -m    The message to encode\n\
  -o    The path of the output file (./encrypted_message if left blank)\n");
      return 1;
    default:
      abort();
    }
  }

  if (message == NULL || key == NULL)
  {
    printf("Failed to encrypt: Must provide both key and message\n");
    return 1;
  }
  if (output_filepath == NULL)
  {
    output_filepath = "encrypted_message";
  }

  if (encrypt_to_file(key, message, output_filepath))
  {
    printf("Successfully encrypted to file: %s\n", output_filepath);
    return 0;
  }
  else
  {
    printf("Failed to encrypt\n");
    return 1;
  }
}