CC = gcc
CFLAGS = -O3
GENERATES = move remove.so infile outfile

All: move remove.so

move: move.c
	$(CC) $(CFLAGS) $< -o $@

remove.so: remove.c
	$(CC) $(CFLAGS) -fPIC -shared -ldl $< -o $@

test: move remove.so
	@echo "Running test 1: 'Cant open file'";
	@strace -P "nothing.txt" -e inject=fopen ./move nothing.txt nowhere.txt 2> /dev/null || echo "Test 1 ok";

	@echo "Running test 2: 'Read error'";
	@echo "test" > infile
	@strace -e inject=read:error=EIO ./move infile outfile 2> /dev/null || echo "Test 2 ok";

	@echo "Running test 3: 'Write error'";
	@echo "test" > infile
	@strace -e inject=write:error=EIO ./move infile outfile 2> /dev/null || echo "Test 3 ok";

	@echo "Running test 4: 'Close error'";
	@echo "test" > infile
	@strace -e inject=close:error=EIO ./move infile outfile 2> /dev/null || echo "Test 4 ok";

	@echo "Running test 5: 'Dont remove PROTECT file'";
	@LD_PRELOAD=./remove.so ./move tePROTECT.txt test_2.txt && test -f test_2.txt || echo "Test 6 ok";

clean:
	rm -rf $(GENERATES)