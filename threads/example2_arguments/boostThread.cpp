#include <iostream>
#include <boost/thread.hpp>

void handle(int& dataIn){
	dataIn = 1;
	// might have done more than just a sleep...
	sleep(1);
}




int main(int argc, char* argv[])
{
	
  std::cout << "main: startup" << std::endl;

  int data[2];
  boost::thread worker1(handle, boost::ref(data[0]));
  boost::thread worker2(handle, boost::ref(data[1]));
  std::cout << "main: waiting for thread" << std::endl;
  worker1.join();
  worker2.join();
  std::cout << "data[0] "<< data[0]  << std::endl;
  std::cout << "data[1] "<< data[1]  << std::endl;
  std::cout << "main: done" << std::endl;
  return 0;
}
