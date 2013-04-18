#ifndef __KEY_H
#define __KEY_H

#include <gmp.h>
#include "random.h"

typedef struct {
  mpz_t x, y;
} __subkey_struct;

typedef __subkey_struct subkey_t[1];

#include "master_key.h"

void subkey_init(subkey_t key);
void subkey_create(subkey_t key, master_key_t master_key);
void subkey_create_with_random(subkey_t key, master_key_t master_key, random_t random);
void subkey_free(subkey_t key);

#endif
