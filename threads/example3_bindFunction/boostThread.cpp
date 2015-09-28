#include <iostream>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>



class Work1{
	public:
	void handle(std::string& dataIn){
		dataIn = boost::lexical_cast<std::string>(boost::this_thread::get_id());
		sleep(1);
	}
};


int main(int argc, char* argv[])
{
	std::cout << "main: startup" << std::endl;
	Work1* work1 = new Work1();
	Work1* work2 = new Work1();

	std::string data[2];
	
  boost::thread worker1(boost::bind(&Work1::handle, work1,  boost::ref(data[0])));
  boost::thread worker2(boost::bind(&Work1::handle, work1,  boost::ref(data[1])));  

  std::cout << "main: waiting for thread" << std::endl;
  worker1.join();
  worker2.join();
  
  std::cout << "data[0] "<< data[0]  << std::endl;
  std::cout << "data[1] "<< data[1]  << std::endl;

  std::cout << "main: done" << std::endl;
  return 0;
}
