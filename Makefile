all:
	clang main.c -lm;
	clear;
	-./a.out;
	rm ./a.out;
	clear;
clean:
	-rm ./a.out;
	clear;

test: 
	clang main.c -lm;
	clear;
	-./a.out;
	rm ./a.out;
	clear;
