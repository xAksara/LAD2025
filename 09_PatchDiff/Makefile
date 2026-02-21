GENERATES = lab lab1* lab2* lab3*

all: lab lab1 lab2 lab3

run: lab lab1 lab2 lab3
	./lab;
	./lab1 10;
	./lab2 ".#" 5;
	./lab3 42 ".#" 5;

lab%: lab%.c
	cc $< -o $@

lab1.c: lab.c
	cp lab.c lab1.c;
	patch lab1.c < 1.patch;

lab2.c: lab1.c
	cp lab1.c lab2.c;
	patch lab2.c < 2.patch;

lab3.c: lab2.c
	cp lab2.c lab3.c
	patch lab3.c < 3.patch;

clean:
	rm -rf $(GENERATES)
