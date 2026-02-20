#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([rhasher], [0.0], [aaaa@a.a])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([rhash], [rhash_library_init], [],
             [AC_MSG_ERROR([rhash required])])

# Checks for header files.
AC_CHECK_HEADER([rhash.h], [], [AC_MSG_ERROR([rhash.h required])])
# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strcasecmp])


AC_ARG_ENABLE([readline], AS_HELP_STRING([--enable-readline], [use readline]),
            [AS_IF([test "x$enable_readline" = xyes], 
                  [AC_CHECK_LIB([readline], [readline],
                               [AC_DEFINE([USE_READLINE], [1], [use readline])
                               LIBS="$LIBS -lreadline"], [])])])





AC_OUTPUT
