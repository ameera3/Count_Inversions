# Count_Inversions

## Usage 

To compile, type "make". To run the program, type "./countInversions inputFile".

## Introduction

The command line program countInversions.cpp takes in one parameter, an input filename.
The input file specified by the input filename should contain the numbers 1 through n in some
order, each on a new line. The program will output the number of inversions.

The algorithm runs in O(n log n) time by piggybacking on merge sort.
