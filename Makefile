#
# 'make'        build executable file 'main'
# 'make clean'  removes all .o and executable files
#

# define the Cpp compiler to use
CXX = g++

# define any compile-time flags
CXXFLAGS	:= -std=c++17 -Wall -Werror


all: myfind

myfind:
	 $(CXX) $(CXXFLAGS) myfind.cpp main.cpp -o myfind

clean:
	rm -f myfind

run: all
	./myfind