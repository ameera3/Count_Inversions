/* 
 * Filename: countInversions.cpp
 * Usage: ./countInversions File
 * Description: The command line program countInversions.cpp 
 *              takes in one parameter, an input filename. 
 *              The input file specified by the input filename 
 *              should contain the numbers 1 through n in some 
 *              order, each on a new line. The program will 
 *		output the number of inversions.
 */

#include <iostream>
#include <string.h>
#include <fstream>

// argv index of input file
#define IN_IDX 1 

// expected number of arguments
#define EXPECTED_ARGS 2

using namespace std;

// counts the number of lines in inputfile
unsigned int countLines(const char* filename) 
{

	// used to get each line from input file
	string line;
	
	ifstream * in = new ifstream(filename);

    	unsigned int lineCount = 0;

    	// count the number of lines
    	while (getline(*in, line)) {
        	++lineCount;
	}

	return lineCount;
}

// merges the left and right subarrays and returns the
// number of split inversions.
unsigned int mergeCount(unsigned int arr[], unsigned int l, 
		unsigned int m, unsigned int r)
{
	unsigned int i, j, k;

	// number of split inversions
	unsigned int count = 0;
	
	// size of left subarray
	unsigned int n1 = m - l + 1;

	// size of right subarray
	unsigned int n2 = r - m;

	/* dynamically allocate temp arrays */
        unsigned int* L = new unsigned int[n1];
	unsigned int* R = new unsigned int[n2];

	/* Copy data to temp arrays L[] and R[] */
	for(i = 0; i < n1; i++){
		L[i] = arr[l + i];
	}
	for(j = 0; j < n2; j++){
		R[j] = arr[m + 1 + j];
	}

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2)
	{
		if (L[i] < R[j]){
			arr[k++] = L[i++];
		}
		else{
			arr[k++] = R[j++];
			// number of split inversions
			// involving R[j]
			count = count + (n1 - i);
		}
	}

	/* Copy the remaining elements of L[], if there 
	   are any */
	while (i < n1)
		arr[k++] = L[i++];

	/* Copy the remaining elements of R[], if there 
	   are any */
	while(j < n2)
		arr[k++] = R[j++];

	// no memory leaks here
        delete[] L;
	delete[] R;

	return count;
}

/* Recursive mergeSort algorithm for array
 * l is for left index and r is right index of the 
 * sub-array of arr to be sorted 
 */
unsigned int mergeSort(unsigned int arr[], unsigned int l, unsigned int r)
{
	// number of inversions in left half
	unsigned int x = 0;
	
	// number of inversions in right half
	unsigned int y = 0;

	// number of split inversions
	unsigned int z = 0;

	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for 
		// large l and r 
		unsigned int m = l + (r - l) / 2;

		// Sort and count the number of inversions
                // in the left and right half. Then merge
                // the left and right half while counting
		// the number of split inversions.  
		x = mergeSort(arr, l, m);
		y = mergeSort(arr, m + 1, r);
		z = mergeCount(arr, l, m, r);
	}

	// total number of inversions
	return x+y+z;

}

unsigned int countInversions(const char* inFile, int n)
{

	// dynamically allocate an array with n entries
	unsigned int* arr = (unsigned int*) 
        	malloc(n * sizeof(unsigned int));

	bool more_input = true; 
	unsigned int i;

	// open input file 
    	FILE *in = fopen(inFile, "r"); 
 
	// read the integers in the input file into the array
    	while (more_input) 
    	{ 
        	// write n elements into arr from input file 
        	for (i = 0; i < n; ++i) 
        	{ 
            		if (fscanf(in, "%d\n", &arr[i]) != 1) 
            		{ 
                		more_input = false; 
                		break; 
            		} 
        	}
	}
	
	// count the number of inversions
	unsigned int numberInversions = mergeSort(arr, 0, n-1);

	// no memory leaks here
        delete[] arr;

	// close input file 
	fclose(in);

	return numberInversions;
	
} 

// Main Driver
int main(int argc, char** argv) 
{

	//Check for Arguments
	if (argc != EXPECTED_ARGS){
		cout << "This program requires 2 arguments!" << endl;
		return -1;
	}

	/* The input file contains the numbers 1 through n
         * in some order, each on a new line.
         */  
	unsigned int n = countLines(argv[IN_IDX]);

	// cout << "n: " << n << endl;

	// count the number of inversions
	unsigned int inversionNumber = 
		countInversions(argv[IN_IDX], n);

	cout << "The number of inversions is: " << 
                inversionNumber << endl;
} 

