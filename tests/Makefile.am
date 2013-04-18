TESTS = test_runner
check_PROGRAMS = $(TESTS)
test_runner_SOURCES = crypto_aesctr_tests.c \
											hkdf_tests.c \
											master_key_tests.c \
											random_tests.c \
											subkey_tests.c \
											test_helper.c \
											test_runner.c \
											$(top_builddir)/src/crypto_aesctr.c \
											$(top_builddir)/src/crypto_aesctr.h \
											$(top_builddir)/src/hkdf.c \
											$(top_builddir)/src/hkdf.h \
											$(top_builddir)/src/master_key.c \
											$(top_builddir)/src/master_key.h \
											$(top_builddir)/src/random.c \
											$(top_builddir)/src/random.h \
											$(top_builddir)/src/subkey.c \
											$(top_builddir)/src/subkey.h
test_runner_CFLAGS = $(CHECK_CFLAGS) $(CRYPTO_CFLAGS)
test_runner_LDADD = $(CHECK_LIBS) $(CRYPTO_LIBS)
