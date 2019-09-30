#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_files.h"

#define ENCRYPTION_KEY 0xFACA
#define ENCRYPTION_KEY_LEN 6

/*******************************************************************************
 * Author: Oliver Windall Juhl
 * This function encrypts the password of the user. This is a very simple
 * encryption, in which we simple subtracts an encryption from every index of
 * the password array.
 * inputs:
 * - char pwd[]: a string containing the password for the user
*******************************************************************************/
void simple_encrypt(char pwd[])
{
  int counter;
  for (counter = 0; counter < strlen(pwd); ++counter)
  {
    pwd[counter] = pwd[counter] - ENCRYPTION_KEY;
  }
}

/*******************************************************************************
 * Author: Oliver Windall Juhl
 * This function decrypts the password, that was made by simple_encrypt. We
 * simply do the exact opposite: Add the encryption key to every index of the
 * password array.
 * inputs:
 * - char pwd[]: a string containing the password for the user
*******************************************************************************/
void simple_decrypt(char pwd[])
{
  int counter;
  for (counter = 0; counter < strlen(pwd); ++counter)
  {
    pwd[counter] = pwd[counter] + ENCRYPTION_KEY;
  }
}

/*******************************************************************************
 * Author: Oliver Windall Juhl
 * This function both encrypts and decrypts the password of the user. This is
 * done by using the XOR encryption algorithm.
 *
 * Explanation line 58 -> pwd[counter] ^ encr_key[counter % ENCRYPTION_KEY_LEN]:
 * This line of code uses the exclusive OR operator "^" to compare bits of the
 * characters in the password with the characters in the encryption key.
 *
 * Example of encrypting "oliver":
 * First, we convert "oliver" and the encryption key into binary, since is used
 * for the comparison of the XOR operator.
 * o -> 01101111        0 -> 00110000
 * l -> 01101100        x -> 01111000
 * i -> 01101001        F -> 01000110
 * v -> 01110110        A -> 01000001
 * e -> 01100101        C -> 01000011
 * r -> 01110010        A -> 01000001
 * The compare them using the XOR operator:
 * 01101111 ^ 00110000 = 01011111
 * 01101100 ^ 01111000 = 00010100
 * 01101001 ^ 01000110 = 00101111
 * 01110110 ^ 01000001 = 00110111
 * 01100101 ^ 01000011 = 00100110
 * 01110010 ^ 01000001 = 00110011
 *
 * Encrypted password: 01011111 00010100 00101111 00110111 00100110 00110011
 * Translated: _/7&3
 *
 * inputs:
 * - char pwd[]: a string containing the password for the user
*******************************************************************************/
void xor_encryption(char pwd[])
{
  /* First we convert our encryption key from int to char array */
  char encr_key[ENCRYPTION_KEY_LEN];
  sprintf(encr_key, "%i", ENCRYPTION_KEY);

  int counter;
  for (counter = 0; counter < strlen(pwd); counter++)
  {
    /* Exclusive OR operation to generate new encryption password */
    pwd[counter] = pwd[counter] ^ encr_key[counter % ENCRYPTION_KEY_LEN];
  }
}