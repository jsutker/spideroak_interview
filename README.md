# Technical Problem for SpiderOak Interview Process

This repo contains 2 basic programs, written in C. The programs use a shared library and a symmetrical key, and both implement a CLI. The Encrypter takes a message and a key (or passphrase) as input, encrypting the message using the key and outputting a success message. The Decrypter takes a key as input and outputs the decrypted message on success (or an error message on failure). The cryptographic logic is contained in a shared library, used by both the Encrypter and Decrypter.

The programs are built with the following from the directory of the repository:

```
$ cmake .
$ make
```

The programs are called as follows:

```
$ encrypter -k <key> -m <message> -o <optional outfile>
$ decrypter -k <key> -i <optional infile>
```

### Requirements

In order to build properly, this requires gcc, cmake, and openssl.
