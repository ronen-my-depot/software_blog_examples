#include <iostream>
#include <thread>
#include <vector>
#include <atomic>


class Work{
	public:
		Work(){
			acc = 0;
			accAtomic = 0;
		}
		void handle(){
			acc++;
			accAtomic++;
		}
		int acc;
		std::atomic<int> accAtomic;

};

int main(int argc, char* argv[])
{
	enum{NUM_OF_THREADS = 10000};
	Work* work1 = new Work();
	std::vector<std::thread*> workers;

	for(int idx = 0; idx < NUM_OF_THREADS; idx++){
		workers.push_back(new std::thread(std::bind(&Work::handle, work1)));
	}
	for(auto worker : workers){
		worker->join();
		delete worker;
	}
	// print acc:
	std::cout << "acc = " << work1->acc << std::endl;
	std::cout << "accAtomic = " << work1->accAtomic << std::endl;
	return 0;
}
