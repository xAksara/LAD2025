esub:	esub.c
	cc -O2 $< -o $@

clean:
	rm -f esub esub.out

all:	esub

test:	esub 
	./esub "abc" "xyz" "123abc789" > esub.out ; \
	echo "123abc789" | sed -E 's/abc/xyz/' | diff esub.out - ; \
	./esub "([0-9]+)-([0-9]+)" "\\2-\\1" "123-456" > esub.out ; \
	echo "123-456" | sed -E 's/([0-9]+)-([0-9]+)/\2-\1/' | diff esub.out - ; \
	./esub "(.)(.)(.)" "3:\\3 2:\\2 1:\\1" "abc" > esub.out ; \
	echo "abc" | sed -E 's/(.)(.)(.)/3:\3 2:\2 1:\1/' | diff esub.out - ; \
	./esub "xyz" "replacement" "abcabc" > esub.out ; \
	echo "abcabc" | sed -E 's/xyz/replacement/' | diff esub.out - ; \
