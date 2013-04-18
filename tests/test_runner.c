#include <stdlib.h>
#include "test_suite.h"

int main(void) {
  SRunner *runner = srunner_create(make_hkdf_suite());
  srunner_add_suite(runner, make_crypto_aesctr_suite());
  srunner_add_suite(runner, make_master_key_suite());
  srunner_add_suite(runner, make_random_suite());
  srunner_add_suite(runner, make_subkey_suite());
  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
