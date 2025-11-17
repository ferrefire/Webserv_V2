#include <sys/socket.h>
#include <sys/epoll.h>
#include <vector>

struct SocketConfig
{
	int domain = AF_INET;
	int type = SOCK_STREAM | SOCK_NONBLOCK;
	int protocol = 0;
	int port = 8080;
};

struct ServerConfig
{
	int maxEvents = 64;

	SocketConfig socketConfig{};
};

class Server
{
	private:
		ServerConfig config{};

		int socketFD = -1;
		int epollFD = -1;

		std::vector<int> clients;

		void CreateSocket();
		void CreateEpoll();

		void DestroySocket();
		void DestroyEpoll();

		void SetNonBlocking(const int& FD);
		void AddClient(const epoll_event& event);
		void RemoveClient(const int& clientFD);

		std::vector<char> ReadClient(const int& FD, const size_t size);

	public:
		static bool running;

		Server(const ServerConfig& serverConfig);
		~Server();

		void Destroy();

		void Start();
};