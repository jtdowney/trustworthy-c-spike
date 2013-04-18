#ifndef __TEST_SUITE_H
#define __TEST_SUITE_H

#include <check.h>
#include "test_helper.h"

Suite *make_crypto_aesctr_suite();
Suite *make_hkdf_suite();
Suite *make_master_key_suite();
Suite *make_random_suite();
Suite *make_subkey_suite();

#endif
