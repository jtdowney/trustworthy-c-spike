#include "random.h"

void random_create(random_t random) {
  random_open(random, "/dev/urandom");
}

void random_open(random_t random, char *filename) {
  random->file = fopen(filename, "w+");
  if (!random->file) {
    perror("random_open");
  }
}

void random_bytes(random_t random, uint8_t *bytes, size_t length) {
  if (!fread(bytes, length, 1, random->file)) {
    perror("random_bytes");
  }
}

void random_number(random_t random, mpz_t number) {
  uint8_t data[32];
  random_bytes(random, data, 32);
  mpz_import(number, 1, 1, 32, 1, 0, data);
}

void random_free(random_t random) {
  fclose(random->file);
}
