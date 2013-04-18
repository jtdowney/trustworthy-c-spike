#include <stdio.h>
#include <stdint.h>
#include "subkey.h"

void subkey_init(subkey_t key) {
  mpz_init(key->x);
  mpz_init(key->y);
}

void subkey_create(subkey_t key, master_key_t master_key) {
  random_t random;
  random_create(random);
  subkey_create_with_random(key, master_key, random);
  random_free(random);
}

void subkey_create_with_random(subkey_t key, master_key_t master_key, random_t random) {
  subkey_init(key);

  random_number(random, key->x);

  mpz_mul(key->y, master_key->slope, key->x);
  mpz_add(key->y, master_key->intercept, key->y);
}

void subkey_free(subkey_t key) {
  mpz_clear(key->x);
  mpz_clear(key->y);
}
