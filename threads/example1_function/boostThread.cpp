#include <iostream>
#include <boost/thread.hpp>

void handle(){
	// might have done more than just a sleep...
	sleep(1);
}



int main(int argc, char* argv[])
{
  std::cout << "main: start" << std::endl;
  int data[2];
  boost::thread worker1(handle);
  boost::thread worker2(handle);
  std::cout << "main: waiting for thread" << std::endl;
  worker1.join();
  worker2.join();
  std::cout << "main: done" << std::endl;
  return 0;
}
