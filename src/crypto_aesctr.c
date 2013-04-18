#include <string.h>
#include <stdio.h>
#include "crypto_aesctr.h"

void crypto_aesctr_create(crypto_aesctr_t aes, uint8_t *key, size_t key_len, uint8_t *nonce) {
  const EVP_CIPHER *cipher = NULL;
  switch (key_len) {
    case 16:
      cipher = EVP_aes_128_ecb();
      break;
    case 24:
      cipher = EVP_aes_192_ecb();
      break;
    case 32:
      cipher = EVP_aes_256_ecb();
      break;
    default:
      return;
  }

  EVP_CIPHER_CTX_init(&aes->ctx);
  EVP_EncryptInit_ex(&aes->ctx, cipher, NULL, key, NULL);
  EVP_CIPHER_CTX_set_padding(&aes->ctx, 0);

  aes->block_pos = 0;
  memcpy(aes->nonce, nonce, AES_BLOCK_SIZE);
}

void crypto_aesctr_inc_nonce(crypto_aesctr_t aes) {
  for (int i = AES_BLOCK_SIZE - 1; i >= 0; i--) {
    aes->nonce[i]++;
    if (aes->nonce[i] > 0) {
      break;
    }
  }
}

void crypto_aesctr_stream(crypto_aesctr_t aes, const uint8_t *input, uint8_t *output, size_t length) {
  for (size_t i = 0; i < length; i++) {
    if (aes->block_pos == 0) {
      int ret;
      EVP_EncryptUpdate(&aes->ctx, aes->block, &ret, aes->nonce, AES_BLOCK_SIZE);
      crypto_aesctr_inc_nonce(aes);
    }

    output[i] = input[i] ^ aes->block[aes->block_pos];
    aes->block_pos = (aes->block_pos + 1) % 16;
  }
}

void crypto_aesctr_free(crypto_aesctr_t aes) {
  EVP_CIPHER_CTX_cleanup(&aes->ctx);
  aes->block_pos = 0;
  memset(aes->nonce, 0, 16);
  memset(aes->block, 0, 16);
}
