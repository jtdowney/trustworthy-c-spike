AC_PREREQ(2.61)
AC_INIT([trustworthy], [0.1.0], [trustworthy@jtdowney.com])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADER([src/config.h])
AC_PROG_CC_C99
AM_INIT_AUTOMAKE([-Wall foreign dist-bzip2])
AC_CHECK_LIB([gmp], [__gmpz_init], , AC_MSG_ERROR([gmp library not found]))
PKG_CHECK_MODULES([CHECK], [check >= 0.9.4])
PKG_CHECK_MODULES([CRYPTO], [libcrypto >= 0.9.8])
AC_CONFIG_FILES([Makefile src/Makefile tests/Makefile])
AC_OUTPUT
