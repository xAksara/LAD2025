CFLAGS = -Wall
if COND_GCOV
CFLAGS  += -O0 -g -fprofile-arcs -ftest-coverage
else
CFLAGS  += -O3 -g3
endif

lib_LTLIBRARIES=libguesserlib.la
libguesserlib_la_SOURCES=guesserlib.c guesserlib.h
libguesserlib_la_LDFLAGS=-version-info 1:0:0

bin_PROGRAMS=guesser
guesser_SOURCES=guesser.c
guesser_LDADD=libguesserlib.la


AM_CFLAGS=-D'LOCALE_PATH="$(localedir)"' 

gcov:
	gcov -o .libs guesserlib.c -t -k -b | egrep -v '[[:digit:]]:[ /][*]'
