#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <vector>
#include <map>
#include "Connections.hpp"
#include "ServerConfig.hpp"
#include "ConfigParser.hpp"
#include <csignal>
#include "utils.hpp"

#define TIME_OUT 600 //Время ожидания в секундах

int	find_connections(std::pair<in_addr_t, int> addr, std::map<int, std::pair<in_addr_t, int> > &addr_servers)
{
	for(std::map<int, std::pair<in_addr_t, int> >::iterator it = addr_servers.begin();
		it != addr_servers.end();++it)
	{
		if (addr.second == it->second.second)
		{
			if (addr.first == it->second.first)
				return it->first;
			else if(it->second.first == 0)
				return it->first;
			else if(addr.first == 0)
				return it->first;
		}
	}
	return -1;
}

void	init_servers(const std::vector<ServerConfig>& configs, std::map<int, std::vector<const ServerConfig*> >& servers)
{
	std::vector<ServerConfig>::const_iterator	it = configs.begin();
	std::map<int, std::pair<in_addr_t, int> >	addr_servers;
	int	fd_conn;


    while (it != configs.end())
	{
		for(std::vector<std::pair<in_addr_t, int> >::const_iterator it_addr =
				it->getVectorOfAddresses().begin();
				it_addr != it->getVectorOfAddresses().end();
				++it_addr)
		{
			if ((fd_conn = find_connections(std::pair<in_addr_t, int>(it_addr->first, it_addr->second), addr_servers)) == -1)
			{
				struct sockaddr_in	address;
				int	server_fd;

				if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
					{perror("socket failed"); exit(EXIT_FAILURE);}
				
				int	temp = 1;
				if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &temp, sizeof(int)) < 0)
					{perror("socket reinit error"); exit(EXIT_FAILURE);}
                temp = 1;
                if (setsockopt(server_fd, SOL_SOCKET, SO_NOSIGPIPE, &temp, sizeof(int)) < 0)
                    {perror("socket nosigpipe error"); exit(EXIT_FAILURE);}

				address.sin_family = AF_INET;
				address.sin_addr.s_addr = it_addr->first;
				address.sin_port = htons(it_addr->second);

				if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0)
					{perror("bind failed"); exit(EXIT_FAILURE);}

				if (listen(server_fd, SOMAXCONN) < 0)
					{perror("listen");exit(EXIT_FAILURE);}
				servers[server_fd].push_back(&(*it));
				addr_servers[server_fd] = std::pair<in_addr_t, int>(it_addr->first, it_addr->second);
			}
			else
			{
				std::vector<const ServerConfig*>::iterator it_serv = servers[fd_conn].begin();
				while (it_serv != servers[fd_conn].end())
				{
					if (&(*it) == *it_serv)
						break ;
					it_serv++;
				}
				if (it_serv == servers[fd_conn].end())
					servers[fd_conn].push_back(&(*it));
			}
		}
		it++;
	}
}

void	close_connections(std::vector<int> arr_conn, fd_set* fdset)
{
	std::vector<int>::iterator	it = arr_conn.begin();

	while (it != arr_conn.end())
	{
		FD_CLR(*it, fdset);
		close(*it);
		it++;
	}
}

int main(int argc, char **argv)
{
	int					socket_fd;
	fd_set				readfds;
	fd_set				b_readfds;
	fd_set 				b_writefds;
	Connections			connects;
	std::map<int, std::vector<const ServerConfig*> >	servers;
	
	if (argc == 1) {
		std::cerr << "There is no config file" << std::endl;
		return 1;
	}
	if (argc > 2) {
		std::cerr << "Only one config file needed" << std::endl;
		return 1;
	}
	ConfigParser config = ConfigParser(argv[1]);
	try {
		config.ParsingProcess();
	}
	catch (std::logic_error& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	init_servers(config.getVectorOfServers(), servers);

	FD_ZERO(&readfds);

	std::map<int, std::vector<const ServerConfig*>*>	client_fds;
	std::map<int, std::vector<const ServerConfig*>*>::iterator	find_client_fds;
	std::map<int, std::vector<const ServerConfig*> >::iterator	serv_it = servers.begin();
	while (serv_it != servers.end())
	{
		FD_SET(serv_it->first, &readfds);
		serv_it++;
	}

	int				res_select;
	struct timeval	tv; tv.tv_sec = TIME_OUT + 1; tv.tv_usec = 0;
	while (1)
	{
		b_writefds = readfds;
		b_readfds = readfds;
		res_select = select(FD_SETSIZE, &b_readfds, &b_writefds, NULL, &tv);
		if (res_select == 0) {
            close_connections(connects.checkTime(TIME_OUT), &readfds);
        }
		else if (res_select > 0)
		{
			for (int i = 0; i < FD_SETSIZE; i++)
			{
				if (FD_ISSET(i, &b_readfds))
				{
					find_client_fds = client_fds.find(i);
					if (find_client_fds == client_fds.end())
					{
						if ((socket_fd = accept(i, NULL, NULL)) < 0)
							{ perror("accept"); exit(EXIT_FAILURE);}
						FD_SET(socket_fd, &readfds);
						client_fds[socket_fd] = &(servers[i]);
					}
					else if (connects.read_request(i, *(find_client_fds->second)))
					{
						FD_CLR(i, &readfds);
						close(i);
					}
				}
			}
		}
	}
}