#include <iostream>  
#include "boost/interprocess/shared_memory_object.hpp"
#include "boost/interprocess/mapped_region.hpp"
#include "ShmSem.h"

using namespace boost::interprocess;

int main (int argc, char **argv){
 if(argc < 2){
	 std::cout << "Command's argument is missing. expected format: " << argv[0] << " <message> " << std::endl;
	 std::cout << "Terminating " << std::endl;
 }else{
  // create a shared memory object - actually open only:.
	shared_memory_object shm(open_only, "shmName",read_write);
	mapped_region region(shm,read_write);
	//get the region address
	void * addr = region.get_address();
	// Set a pointer to the shared semaphore structure
	ShmSem* shmSem = static_cast<ShmSem*>(addr);  
	// Set a pointer to the shared message buffer:
	char* buff = static_cast<char*>(addr) + sizeof(ShmSem);
	// if executed withput  an argument, set command and return:
		std::string argLine= "";
		// append all arguments to a string:
		for(int idx=1; idx < argc ;idx++) argLine.append(std::string(argv[idx]).append(" "));
		
		unsigned int buffSize = region.get_size() - sizeof(ShmSem);
		memset(buff, 0, buffSize);
		memcpy(buff, argLine.c_str(), argLine.size());
		std::cout << argLine.size() << "\n";
		shmSem->client.post(); 
		shmSem->server.wait();
		std::cout << buff << "\n";
	}
	return 0;
}

	
