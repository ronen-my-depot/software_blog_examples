#include <iostream>
enum{ARRAY_SIZE=10};
int main()
{
	int data[ARRAY_SIZE];

	for(int idx=0; idx < 	ARRAY_SIZE; idx++){
		data[idx] = idx;
	}
	return 0;
}
