SUBDIRS = src po tests

@DX_RULES@

all-local:	doxygen-doc

http:	doxygen-doc
	python3 -m http.server --directory $</html

gcov:	check
	$(MAKE) $(MAKEFLAGS) -C src gcov

gitclean:
	git clean -xfd
