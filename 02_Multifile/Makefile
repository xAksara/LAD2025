GENERATES = prog prog-a prog-so README *.a *.so
OUTPUTFILES = *.output
TRASH = *.o *~ o.* $(OUTPUTFILES)
CFLAGS = -Wall

all:    README prog prog-a prog-so


liboutput_static.a:	fun.o const.o
	ar -rcs $@ $^

liboutput.so:	fun.o const.o
	cc $(CFLAGS) -shared -fPIC $^ -o $@

prog:	prog.o fun.o const.o
	cc $(CFLAGS) $^ -o $@

prog-a:	prog.o liboutput_static.a
	cc $(CFLAGS) -L. prog.o -loutput_static -o $@

prog-so:	prog.o liboutput.so
	cc $(CFLAGS) $^ -o $@

%.o:	%.c
	cc $(CFLAGS) -fPIC $< -c -o $@

README: prog
	./$< 2> $@

clean:
	rm -f $(TRASH)

distclean:      clean
	rm -rf $(GENERATES)

run-prog:	prog
	./$< > $<1.output 2>&1 
	./$< 123 > $<2.output 2>&1 
	./$< 123 456 789 > $<3.output 2>&1 

run-prog-a:	prog-a
	./$< > $<1.output 2>&1 
	./$< 123 > $<2.output 2>&1 
	./$< 123 456 789 > $<3.output 2>&1 

run-prog-so:	prog-so
	LD_LIBRARY_PATH=. ./$< > $<1.output 2>&1 
	LD_LIBRARY_PATH=. ./$< 123 > $<2.output 2>&1 
	LD_LIBRARY_PATH=. ./$< 123 456 789 > $<3.output 2>&1 

cmp:	run-prog run-prog-a run-prog-so
	cmp prog1.output prog-a1.output
	cmp prog1.output prog-so1.output
	cmp prog2.output prog-a2.output
	cmp prog2.output prog-so2.output
	cmp prog3.output prog-a3.output
	cmp prog3.output prog-so3.output


test:	cmp

