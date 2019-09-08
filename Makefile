all:
	CXXFLAGS = -Og -Wall -Wextra

	GCC_CXXFLAGS = -DMESSAGE='"Compiled with GCC"'
	CLANG_CXXFLAGS = -DMESSAGE='"Compiled with Clang"'
	UNKNOWN_CXXFLAGS = -DMESSAGE='"Compiled with an unknown compiler"'

	ifeq ($(CXX),clang)
		clang main.c -lm;
		clear;
		-./a.out;
		rm ./a.out;
		clear;
	else ifeq ($(CXX),g++)
		gcc main.c -lm;
		clear;
		-./a.out;
		rm ./a.out;
		clear;
	else
		clear;
	endif

clean:
	-rm ./a.out;
	clear;

test: 
	ifeq ($(CXX),clang)
		clang main.c -lm;
		clear;
		-./a.out;
		rm ./a.out;
		clear;
	else ifeq ($(CXX),g++)
		gcc main.c -lm;
		clear;
		-./a.out;
		rm ./a.out;
		clear;
	else
		clear;
	endif
