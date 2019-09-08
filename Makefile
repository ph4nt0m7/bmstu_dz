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
	892498273 4987239847 92837498234
	rm ./a.out;
	clear;
