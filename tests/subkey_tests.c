#include "subkey.h"
#include "test_helper.h"
#include "test_suite.h"

START_TEST(create_makes_key_along_slope) {
  master_key_t master_key;
  subkey_t key;

  master_key_init(master_key);
  mpz_set_ui(master_key->slope, 6);
  mpz_set_ui(master_key->intercept, 24);

  random_t random;
  random_test_start(random);
  random_test_add_number_ul(random, 10);
  random_test_final(random);

  subkey_create_with_random(key, master_key, random);
  fail_unless(mpz_cmp_ui(key->y, 84) == 0);
  subkey_free(key);

  random_free(random);
  master_key_free(master_key);
}
END_TEST

Suite *make_subkey_suite(void) {
  Suite *suite = suite_create("Subkey");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, create_makes_key_along_slope);
  suite_add_tcase(suite, tc_core);

  return suite;
}

