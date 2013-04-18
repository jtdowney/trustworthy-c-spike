#ifndef __CRYPTO_AESCTR_H
#define __CRYPTO_AESCTR_H

#include <openssl/aes.h>
#include <openssl/evp.h>
#include <stdint.h>

typedef struct {
  EVP_CIPHER_CTX ctx;
  uint8_t nonce[AES_BLOCK_SIZE];
  uint8_t block[AES_BLOCK_SIZE];
  uint8_t block_pos;
} __crypto_aesctr;

typedef __crypto_aesctr crypto_aesctr_t[1];

void crypto_aesctr_create(crypto_aesctr_t aes, uint8_t *key, size_t key_len, uint8_t *nonce);
void crypto_aesctr_stream(crypto_aesctr_t aes, const uint8_t *input, uint8_t *output, size_t length);
void crypto_aesctr_free(crypto_aesctr_t aes);

#endif
