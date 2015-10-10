#include <iostream>  
#include "boost/interprocess/shared_memory_object.hpp"
#include "boost/interprocess/mapped_region.hpp"
#include "ShmSem.h"

using namespace boost::interprocess;

int main (int argc, char **argv){
  // create a shared memory object - actually open only:.
  shared_memory_object shm(open_only, "shmName",read_write);
  mapped_region region(shm,read_write);
  //get the region address
  void * addr = region.get_address();
  // Set a pointer to the shared semaphore structure
  ShmSem* data = static_cast<ShmSem*>(addr);  
  // Set a pointer to the shared message buffer:
  char* data2 = static_cast<char*>(addr) + sizeof(ShmSem);
  // if executed withput  an argument, set command and return:
  if(argc > 1){
		std::string argLine= "";
		// append oall argumentsL
		for(int i=1;i<argc;i++) argLine.append(std::string(argv[i]).append(" "));
		
		unsigned int buffSize = region.get_size() - sizeof(ShmSem);
		memset(data2, 0, buffSize);
		memcpy(data2, argLine.c_str(), argLine.size());
		std::cout << argLine.size() << "\n";
		data->client.post(); 
		data->server.wait();
		std::cout << data2 << "\n";
	}
  return 0;
}

	
