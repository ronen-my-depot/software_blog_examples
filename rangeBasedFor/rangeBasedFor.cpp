#include <iostream>
#include <vector>

int main(){
	int array[] = {0, 1, 2, 3};
	std::vector<int> vec;
	// iterate over a regular c array:
	for(int& element : array){
	  std::cout << element << std::endl;
	  vec.push_back(element);
	}
	// iterate over an stla vector:
	for(int& element : vec){
	  std::cout << element << std::endl;
	}
}
