#include "server.hpp"

#include <iostream>

int main()
{
	ServerConfig serverConfig{};
	Server server(serverConfig);
	server.Start();

	return (0);
}