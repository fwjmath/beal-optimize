# Makefile for Cygwin64 using mingw64. If you are on another platform, please modify the makefile appropriately.

# Compiler: using mingw64 g++
CXX = x86_64-w64-mingw32-g++

# Compiler flag: optimized for speed
CFLAGS = -O3 -static -std=c++11

# MPIR Libraries
MPIR_LIB = mpir/mingw64/libmpir.a

all: bealopt

bealopt: bealopt.cpp
	cp mpir/mingw64/*.h mpir/
	$(CXX) $(CFLAGS) -o bealopt bealopt.cpp $(MPIR_LIB)

clean:
	rm bealopt

