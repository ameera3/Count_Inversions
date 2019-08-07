# Change the CXX variable assignment at your own risk.
CXX ?= g++ 
CXXFLAGS=-std=c++11 -Wall -O2
LDFLAGS=-g

all: countInversions 

countInversions: countInversions.cpp 

clean:
	rm -f countInversions *.o core* *~

