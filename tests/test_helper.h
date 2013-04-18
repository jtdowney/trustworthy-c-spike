#ifndef __TEST_HELPER_H
#define __TEST_HELPER_H

#include <stdint.h>
#include <gmp.h>
#include "random.h"

void random_test_start(random_t random);
void random_test_final(random_t random);
void random_test_add_number(random_t random, mpz_t number);
void random_test_add_number_ul(random_t random, unsigned long number);
void random_test_add_bytes(random_t random, uint8_t *bytes, size_t length);

#endif
