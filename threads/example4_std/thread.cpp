#include <iostream>
#include <thread>
#include <string>
#include <boost/lexical_cast.hpp>


class Work{
	public:
	void handle(std::string& dataIn){
		dataIn = boost::lexical_cast<std::string>(std::this_thread::get_id());
		sleep(1);
	}
};


int main(int argc, char* argv[])
{
	std::cout << "main: startup" << std::endl;
	Work* work1 = new Work();
	Work* work2 = new Work();

	std::string data[2];
	
  std::thread worker1(std::bind(&Work::handle, work1,  std::ref(data[0])));
  std::thread worker2(std::bind(&Work::handle, work2,  std::ref(data[1])));  

  std::cout << "main: waiting for thread" << std::endl;
  worker1.join();
  worker2.join();
  
  std::cout << "data[0] "<< data[0]  << std::endl;
  std::cout << "data[1] "<< data[1]  << std::endl;

  std::cout << "main: done" << std::endl;
  return 0;
}
