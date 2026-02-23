#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([guesser], [1.0.0], [a@a.a])
AM_INIT_AUTOMAKE([foreign])
DX_INIT_DOXYGEN([guesser])
LT_INIT([disable-static])
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_REQUIRE_VERSION(0.21)

AC_CONFIG_SRCDIR([src/guesser.c])
AC_CONFIG_HEADERS([config.h])


ALL_LINGUAS="ru"

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
PKG_CHECK_MODULES([CHECK],[check])

# Checks for header files.
AC_CHECK_HEADERS([libintl.h])

AC_ARG_ENABLE([gcov],
              [AS_HELP_STRING([--enable-gcov], [use Gcov to test the test suite])],
              [], [enable_gcov=no])
AM_CONDITIONAL([COND_GCOV],[test '!' "$enable_gcov" = no])


# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([setlocale])

AC_CONFIG_FILES([Makefile po/Makefile.in src/Makefile Doxyfile tests/Makefile])
AC_OUTPUT
