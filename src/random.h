#ifndef __RANDOM_H
#define __RANDOM_H

#include <stdio.h>
#include <stdint.h>
#include <gmp.h>

typedef struct {
  FILE *file;
} __random_struct;

typedef __random_struct random_t[1];

void random_create(random_t random);
void random_open(random_t random, char *file);
void random_bytes(random_t random, uint8_t *bytes, size_t length);
void random_number(random_t random, mpz_t number);
void random_free(random_t random);

#endif
