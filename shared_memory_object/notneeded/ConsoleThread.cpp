#include <unistd.h>
#include <boost/format.hpp>


#include "Server.h"

using namespace std;
using namespace cwd;
using namespace boost::interprocess;


Server::Server(){
	m_exit = false;
	loop();
}

Server::~Server(){
  m_data->writer.post(); 
	m_exit = true;
}

void Server::loop(){
	try {
		boost::interprocess::permissions permtest;
		permtest.set_unrestricted();
		//open shared memory. Create a new one if does not exist:
		shared_memory_object shm(open_or_create, "shmName", read_write, permtest);
		//set the size of the memory object
		shm.truncate(sizeof(ShmBuff));
		//map the whole shared memory in this process
		mapped_region region(shm,read_write);
		//get the region address
		void * addr = region.get_address();
		//create a shared memory buffer in memory
		m_data = new (addr) ShmBuff;

		while (!m_exit) {
			m_data->writer.wait();
			m_line=(std::string)m_data->chr;
			int cmp = m_line.compare(0,4,"exit");
			if(0==cmp){
				m_exit = true;
				std::cout << "exit!!\n";
			}
			std::cout << "Received line: " << m_line << "\n";
			// echo back:
			string consoleOutput = m_line + " Ok!";
			memset(m_data->chr,0,sizeof(m_data->chr));
			
									std::cout << "sizeof(m_data->chr): " << sizeof(m_data->chr) << "\n";

			int replySize = (m_data->getShmSize() < consoleOutput.size()) ? m_data->getShmSize() : consoleOutput.size();
						std::cout << "replySize: " << replySize << "\n";

			memcpy(m_data->chr, consoleOutput.c_str(), replySize);
			m_data->reader.post();
		
		}
	}catch(boost::interprocess::interprocess_exception &e){
		std::cout << "Server::workFunctiom: Caught boost::interprocess::interprocess_exception: " << e.what() << endl;
	//throw;
	}
	std::cout << "out!!\n";

}

int main(){
	Server* consoleThread = new Server();
}
