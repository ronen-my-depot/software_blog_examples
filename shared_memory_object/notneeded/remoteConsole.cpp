#include <iostream>     // std::cout, std::endl

#include "boost/interprocess/shared_memory_object.hpp"
#include "boost/interprocess/mapped_region.hpp"
#include "boost/interprocess/sync/interprocess_semaphore.hpp"
#include "semaphore_shared_data.hpp"

using namespace boost::interprocess;

enum{lineCmdBuffSize=200};
int main (int argc, char **argv){
  //create a shared memory object.
  shared_memory_object shm(open_only, "shmName",read_write);
  mapped_region region(shm,read_write);
  //get the region address
  void * addr = region.get_address();
  //Obtain the shared structure
  ShmBuff* data = static_cast<ShmBuff*>(addr);
  
  // if executed with argument, set command and return:
  if(argc > 1){
		std::string argLine= "";
		// append oall argumentsL
		for (int i=1;i<argc;i++) argLine.append(std::string(argv[i]).append(" "));
		
			memset(data->chr,0,sizeof(data->chr));

		memcpy(data->chr,  argLine.c_str(), argLine.size());
		
				std::cout << argLine.size() << "\n";

		data->writer.post(); 
		data->reader.wait();
		usleep(1000);
		std::cout << data->chr << "\n";

	}
  return 0;
}

	
