#
# 'make'        build executable file 'main'
# 'make clean'  removes all .o and executable files
#

# define the Cpp compiler to use
CXX = g++

# define any compile-time flags
CXXFLAGS	:= -std=c++17 -Wall -Werror

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
# here we would set the -lpthread flag
LFLAGS =


all: myfind

myfind:
	 $(CXX) $(CXXFLAGS) myfind.cpp -o myfind

clean:
	rm -f myfind

run: all
	./myfind

testrun: all
	./myfind test.txt -i myfind.pdf -R