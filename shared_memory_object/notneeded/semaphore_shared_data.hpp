#include "boost/interprocess/sync/interprocess_semaphore.hpp"


struct ShmBuff {
	enum{SHM_SIZE=8192};
  ShmBuff(): writer(0), reader(0){
		chr = new char[SHM_SIZE]
	}
		
  unsigned int size(){
		return SHM_SIZE;
	}
  boost::interprocess::interprocess_semaphore writer;
  boost::interprocess::interprocess_semaphore reader;

  char* chr; 
};
