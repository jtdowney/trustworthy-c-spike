#include <stdio.h>
#include <stdint.h>
#include "hkdf.h"
#include "master_key.h"

void master_key_init(master_key_t master_key) {
  mpz_init2(master_key->slope, 256);
  mpz_init2(master_key->intercept, 256);
}

void master_key_create(master_key_t master_key) {
  random_t random;
  random_create(random);
  master_key_create_with_random(master_key, random);
  random_free(random);
}

void master_key_create_with_random(master_key_t master_key, random_t random) {
  master_key_init(master_key);

  random_number(random, master_key->slope);
  random_number(random, master_key->intercept);
}

void master_key_create_from_keys(master_key_t master_key, subkey_t key1, subkey_t key2) {
  master_key_init(master_key);

  mpz_t xt, yt;
  mpz_inits(xt, yt, NULL);

  mpz_sub(xt, key2->x, key1->x);
  mpz_sub(yt, key2->y, key1->y);
  mpz_divexact(master_key->slope, yt, xt);
  mpz_mul(xt, master_key->slope, key1->x);
  mpz_sub(master_key->intercept, key1->y, xt);

  mpz_clears(xt, yt, NULL);
}

int master_key_generate(master_key_t master_key, uint8_t *bytes, size_t length) {
  size_t size = (mpz_sizeinbase(master_key->intercept, 2) + 7) / 8;
  if (size > 32) {
    return -1;
  }

  uint8_t ikm[32];
  mpz_export(ikm, NULL, 1, 32, 1, 0, master_key->intercept);

  return hkdf_sha256(ikm, 32, NULL, 0, NULL, 0, bytes, length);
}

void master_key_free(master_key_t master_key) {
  mpz_clear(master_key->slope);
  mpz_clear(master_key->intercept);
}
