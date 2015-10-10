#ifndef _SHM_SEM_H
#define _SHM_SEM_H

#include "boost/interprocess/sync/interprocess_semaphore.hpp"

struct ShmSem{
  ShmSem() : writer(0), reader(0){}
  boost::interprocess::interprocess_semaphore writer;
  boost::interprocess::interprocess_semaphore reader;
};


#endif // _SHM_SEM_H
