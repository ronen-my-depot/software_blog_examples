#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include "boost/interprocess/shared_memory_object.hpp"
#include "boost/interprocess/mapped_region.hpp"
#include "iostream"
#include "boost/interprocess/sync/interprocess_semaphore.hpp"
#include "semaphore_shared_data.hpp"


#ifndef _CONSOLE_THREAD_
#define _CONSOLE_THREAD_


namespace cwd{
	class ConsoleThread{
		public:

		//new
			ConsoleThread();
			~ConsoleThread();
	
		private:
			void loop();
			std::string	m_line;
			shared_memory_buffer* m_data;
			bool	m_exit;
	};
}

#endif // _CONSOLE_THREAD_
