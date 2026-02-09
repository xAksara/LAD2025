.PHONY:	test all

range:	range.c
	cc -g -O0 $< $@

all:	range

test:	range
	echo "source script1.gdb" | gdb --quiet range | sed -n 's/.*@@@\(.*\)@@@.*/\1/p' | diff - ethalon1.txt; \
	echo "source script2.gdb" | gdb --quiet range | sed -n 's/.*@@@\(.*\)@@@.*/\1/p' | diff - ethalon2.txt

clean:
	rm range
