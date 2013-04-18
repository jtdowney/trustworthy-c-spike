#include <stdlib.h>
#include "test_suite.h"
#include "crypto_aesctr.h"
#include "master_key.h"

START_TEST(stream_encrypts_and_decrypts) {
  uint8_t key[32] = {};
  uint8_t nonce[16] = {};

  crypto_aesctr_t aes;
  crypto_aesctr_create(aes, key, 32, nonce);

  uint8_t plaintext[] = "The quick brown fox jumps over the lazy dog";
  size_t plaintext_len = strlen((char*) plaintext);

  uint8_t *ciphertext = (uint8_t*) malloc(plaintext_len);
  crypto_aesctr_stream(aes, plaintext, ciphertext, plaintext_len);

  crypto_aesctr_free(aes);
  crypto_aesctr_create(aes, key, 32, nonce);

  uint8_t *decrypted_plaintext = (uint8_t*) malloc(plaintext_len);
  crypto_aesctr_stream(aes, ciphertext, decrypted_plaintext, plaintext_len);

  fail_unless(memcmp(plaintext, decrypted_plaintext, plaintext_len) == 0);

  free(ciphertext);
  free(decrypted_plaintext);
  crypto_aesctr_free(aes);
}
END_TEST

START_TEST(stream_encrypts_and_decrypts_in_parts) {
  uint8_t key[32] = {};
  uint8_t nonce[16] = {};

  crypto_aesctr_t aes;
  crypto_aesctr_create(aes, key, 32, nonce);

  uint8_t plaintext1[] = "The quick brown fox jumps";
  uint8_t plaintext2[] = " over the lazy dog";
  size_t plaintext1_len = strlen((char*) plaintext1);
  size_t plaintext2_len = strlen((char*) plaintext2);

  uint8_t *ciphertext1 = (uint8_t*) malloc(plaintext1_len);
  crypto_aesctr_stream(aes, plaintext1, ciphertext1, plaintext1_len);

  uint8_t *ciphertext2 = (uint8_t*) malloc(plaintext2_len);
  crypto_aesctr_stream(aes, plaintext2, ciphertext2, plaintext2_len);

  crypto_aesctr_free(aes);
  crypto_aesctr_create(aes, key, 32, nonce);

  uint8_t plaintext_combined[] = "The quick brown fox jumps over the lazy dog";
  size_t plaintext_combined_len = strlen((char*) plaintext_combined);

  uint8_t *ciphertext_combined = (uint8_t*) malloc(plaintext_combined_len);
  memcpy(ciphertext_combined, ciphertext1, plaintext1_len);
  memcpy(ciphertext_combined + plaintext1_len, ciphertext2, plaintext2_len);

  uint8_t *decrypted_plaintext = (uint8_t*) malloc(plaintext_combined_len);
  crypto_aesctr_stream(aes, ciphertext_combined, decrypted_plaintext, plaintext_combined_len);

  fail_unless(memcmp(plaintext_combined, decrypted_plaintext, plaintext_combined_len) == 0);

  free(ciphertext1);
  free(ciphertext2);
  free(ciphertext_combined);
  free(decrypted_plaintext);
  crypto_aesctr_free(aes);
}
END_TEST

Suite *make_crypto_aesctr_suite() {
  Suite *suite = suite_create("AES CTR");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, stream_encrypts_and_decrypts);
  tcase_add_test(tc_core, stream_encrypts_and_decrypts_in_parts);
  suite_add_tcase(suite, tc_core);

  return suite;
}
