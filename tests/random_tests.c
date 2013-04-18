#include "test_suite.h"
#include "random.h"

START_TEST(random_number_returns_a_random_number) {
  random_t random;
  random_create(random);

  mpz_t a, b;
  mpz_inits(a, b, NULL);

  random_number(random, a);
  random_number(random, b);

  fail_unless(mpz_cmp(a, b) != 0);

  mpz_clears(a, b, NULL);
  random_free(random);
}
END_TEST

START_TEST(random_bytes_returns_random_bytes) {
  random_t random;
  random_create(random);

  uint8_t a[16] = {};
  uint8_t b[16] = {};

  random_bytes(random, a, 16);
  random_bytes(random, b, 16);

  fail_unless(memcmp(a, b, 16) != 0);

  random_free(random);
}
END_TEST

Suite *make_random_suite(void) {
  Suite *suite = suite_create("Random");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, random_number_returns_a_random_number);
  tcase_add_test(tc_core, random_bytes_returns_random_bytes);
  suite_add_tcase(suite, tc_core);

  return suite;
}
