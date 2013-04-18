#ifndef __MASTER_KEY_H
#define __MASTER_KEY_H

#include <gmp.h>

typedef struct {
  mpz_t slope, intercept;
} __master_key_struct;

typedef __master_key_struct master_key_t[1];

#include "subkey.h"
#include "random.h"

void master_key_init(master_key_t master_key);
void master_key_create(master_key_t master_key);
void master_key_create_with_random(master_key_t master_key, random_t random);
void master_key_create_from_keys(master_key_t master_key, subkey_t key1, subkey_t key2);
int master_key_generate(master_key_t master_key, uint8_t *bytes, size_t length);
void master_key_free(master_key_t master_key);

#endif
