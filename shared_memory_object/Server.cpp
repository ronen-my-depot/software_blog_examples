#include "boost/interprocess/shared_memory_object.hpp"
#include "boost/interprocess/mapped_region.hpp"
#include <iostream>  

#include "Server.h"
#include "ShmSem.h"

using namespace boost::interprocess;
enum{BUFF_SIZE = 1000};


Server::Server(){
	m_exit = false;
	loop();
}

Server::~Server(){
  m_sema->client.post(); 
	m_exit = true;
}

void Server::loop(){
	char* buff;
	try {
		boost::interprocess::permissions permissions;
		permissions.set_unrestricted();
		// Create a shared memory object:
		shared_memory_object shm(open_or_create, "shmName", read_write, permissions);
		// set the size of the memory object
		shm.truncate(sizeof(ShmSem) + BUFF_SIZE);
		// map the whole shared memory in this process
		mapped_region region(shm,read_write);
		
		if(region.get_size() != (sizeof(ShmSem) + BUFF_SIZE)){
			std::cout << "Allocation problem. exit!!\n";
			exit(1);
		}
		//get the region address
		void* addr = region.get_address();
		// allocate memory for the semaphores att addr:
		m_sema = new (addr) ShmSem;
		// allocate memory for the message buffer at addr + offset of ShmSem:
		buff = new (static_cast<char*>(addr) + sizeof(ShmSem)) char[BUFF_SIZE];
		// loop on receiving messages:
		while (!m_exit) {
			// wait on semaphore, till client's message is ready:
			m_sema->client.wait();
			// take the reveived message as a string:
			m_line=(std::string)buff;
			// message "exit" terminates the wait-receive loop:
			if(0== m_line.compare(0, 4, "exit")){
				m_exit = true;
				std::cout << "exit!!\n";
			}
			std::cout << "Received line: " <<  m_line << "\n";
			// echo back:
			std::string response = m_line + " Ok!";
			// clean buffer:
			memset(buff, 0, BUFF_SIZE);		
			// limit message size to buffer size:
			int responseSize =  sizeof(BUFF_SIZE) < response.size() ? BUFF_SIZE : response.size();
			// copy response to the share memory buffer:
			memcpy(buff, response.c_str(), responseSize);
			// set the semaphore:
			m_sema->server.post();
		
		}
	}catch(boost::interprocess::interprocess_exception &e){
		std::cout << "Server::workFunctiom: Caught boost::interprocess::interprocess_exception: " << e.what() << std::endl;
	//throw;
	}
	delete[] buff;
	std::cout << "out!!\n";

}

