#include <iostream>
#include "omp.h"

enum{ARRAY_SIZE=10};
int main()
{
	int data[ARRAY_SIZE];
	#pragma omp parallel for 
	for(int idx=0; idx < 	ARRAY_SIZE; idx++){
		data[idx] = idx;
	}
	for(int idx=0;idx < ARRAY_SIZE;idx++){
		std::cout << data[idx] << "\n";
	}
	return 0;
}
