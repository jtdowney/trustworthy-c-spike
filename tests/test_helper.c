#include <assert.h>
#include <stdio.h>
#include "test_helper.h"

void random_test_start(random_t random) {
  random->file = tmpfile();
}

void random_test_final(random_t random) {
  rewind(random->file);
}

void random_test_add_number(random_t random, mpz_t number) {
  size_t length = (mpz_sizeinbase(number, 2) + 7) / 8;
  assert(length <= 32);
  uint8_t bytes[32] = {};

  mpz_export(bytes, NULL, 1, 32, 1, 0, number);
  random_test_add_bytes(random, bytes, 32);
}

void random_test_add_number_ul(random_t random, unsigned long number) {
  mpz_t random_number;
  mpz_init_set_ui(random_number, number);
  random_test_add_number(random, random_number);
  mpz_clear(random_number);
}

void random_test_add_bytes(random_t random, uint8_t *bytes, size_t length) {
  if (fwrite(bytes, 1, length, random->file) != length) {
    perror("random_test_add_bytes");
  }
}
