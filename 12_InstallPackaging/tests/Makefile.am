TESTS=libguesserlib
check_PROGRAMS=libguesserlib

.ts.c:
	checkmk $< > $@

AM_CFLAGS=-I$(top_builddir)/src @CHECK_CFLAGS@
LDADD=$(top_builddir)/src/libguesserlib.la @CHECK_LIBS@
