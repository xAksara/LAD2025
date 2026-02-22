SUBDIRS=src tests
AM_CFLAGS=-Wall

gcov:	check
	$(MAKE) $(MAKEFLAGS) -C src gcov

gitclean:
	git clean -xfd
