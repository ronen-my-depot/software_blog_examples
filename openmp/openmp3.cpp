#include <iostream>
#include "omp.h"

enum{ARRAY_SIZE=10};
int main()
{
	//~ int idx1;
	#pragma omp parallel num_threads(ARRAY_SIZE)
	int data[ARRAY_SIZE];

	{
		int idx1 = omp_get_thread_num();
		std::cout << idx1<<"\n";
		data[idx1] = idx1;
	}
	std::cout << "ss\n";
	for(int idx=0;idx < ARRAY_SIZE;idx++){
		//~ std::cout << data[idx] << "\n";
	}
	return 0;
}

