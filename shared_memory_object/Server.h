#ifndef _SERVER_H_
#define _SERVER_H_
class ShmSem;
class Server{
	public:
		Server();
		~Server();
	private:
		void loop();
		std::string	m_line;
		ShmSem* m_sema;
		bool	m_exit;
};

#endif // _SERVER_H_
