#include "master_key.h"
#include "test_suite.h"

START_TEST(create_uses_a_random_slope_and_intercept) {
  random_t random;
  random_test_start(random);
  random_test_add_number_ul(random, 10);
  random_test_add_number_ul(random, 11);
  random_test_final(random);

  master_key_t master_key;
  master_key_create_with_random(master_key, random);

  fail_unless(mpz_cmp_ui(master_key->slope, 10) == 0);
  fail_unless(mpz_cmp_ui(master_key->intercept, 11) == 0);

  master_key_free(master_key);
  random_free(random);
}
END_TEST

START_TEST(create_from_keys_calculates_the_slope_and_intercept_given_two_keys) {
  subkey_t key1, key2;
  subkey_init(key1);
  subkey_init(key2);

  mpz_set_ui(key1->x, 2);
  mpz_set_ui(key1->y, 30);
  mpz_set_ui(key2->x, 5);
  mpz_set_ui(key2->y, 60);

  master_key_t master_key;
  master_key_create_from_keys(master_key, key1, key2);

  fail_unless(mpz_cmp_ui(master_key->slope, 10) == 0);
  fail_unless(mpz_cmp_ui(master_key->intercept, 10) == 0);

  master_key_free(master_key);
  subkey_free(key1);
  subkey_free(key2);
}
END_TEST

START_TEST(generate_generates_a_key) {
  master_key_t master_key;
  master_key_create(master_key);

  uint8_t key[16] = {};
  uint8_t zero_key[16] = {};
  master_key_generate(master_key, key, 16);

  fail_unless(memcmp(key, zero_key, 16) != 0);

  master_key_free(master_key);
}
END_TEST

Suite *make_master_key_suite(void) {
  Suite *suite = suite_create("Master Key");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, create_uses_a_random_slope_and_intercept);
  tcase_add_test(tc_core, create_from_keys_calculates_the_slope_and_intercept_given_two_keys);
  tcase_add_test(tc_core, generate_generates_a_key);
  suite_add_tcase(suite, tc_core);

  return suite;
}
