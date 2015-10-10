#ifndef _SHM_SEM_H
#define _SHM_SEM_H

#include "boost/interprocess/sync/interprocess_semaphore.hpp"

class ShmSem{
	public:
		ShmSem() : client(0), server(0){}
		boost::interprocess::interprocess_semaphore client;
		boost::interprocess::interprocess_semaphore server;
};

#endif // _SHM_SEM_H
