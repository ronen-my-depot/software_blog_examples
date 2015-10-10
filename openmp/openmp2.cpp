#include <iostream>
#include "omp.h"

enum{ARRAY_SIZE=10};
int main()
{
	int data[ARRAY_SIZE];
	#pragma omp parallel num_threads(ARRAY_SIZE)
	{
		int idx = omp_get_thread_num();
		data[idx] = idx;
	}
	for(int idx=0;idx < ARRAY_SIZE;idx++){
		std::cout << data[idx] << "\n";
	}
	return 0;
}

