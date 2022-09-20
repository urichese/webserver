/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:37:26 by msimon            #+#    #+#             */
/*   Updated: 2022/04/27 15:34:09 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connections.hpp"

int	Connections::read_request(int fds, std::vector<const ServerConfig*> const &srvs_config)
{
	Connect*	conn = getConnect(fds);

	if (!conn)
	{
		_connections.insert(std::pair<int, Connect> (fds, Connect(fds)));
		conn = getConnect(fds);
		if (!conn)
		{
			Responce::sending(conn, "500");
			return 0;
		}
	}
	try {
		bool f_conn_close;
		conn->buffer.read(fds, f_conn_close);		
		if (f_conn_close)
		{
			delConnect(fds);
			return 1;
		}
		conn->timeReq = std::time(NULL);
		if (conn->statusReq == 0 && Request::parse_head(conn))
			conn->statusReq = 1;
		if (conn->statusReq == 1 && Request::all_body_read(conn))
			conn->statusReq = 2;
		if (conn->statusReq == 2)
		{
			GetServer::getConfigInformation(conn, srvs_config);
			Responce::sending(conn, "200");
			conn->clean();
		}
	}
	catch (std::exception &e) {
        if (std::string(e.what()) == "900")
        {
            delConnect(fds);
            return 1;
        }
        Responce::sending(conn, e.what());
		if (Responce::get_code(e.what()) == "500")
		{
			delConnect(fds);
			return 1;
		}			
		else
			conn->clean();
	}
	return 0;
}

std::vector<int>	Connections::checkTime(time_t time_out)
{
	std::vector<int>					res;
	std::map<int, Connect>::iterator	it = _connections.begin();
	time_t								now = time(NULL);

	while (it != _connections.end())
	{
		if (now - it->second.timeReq > time_out)
		{
			res.push_back(it->first);
			it = _connections.erase(it);
		}
		else
			it++;
	}
	return res;	
}

Connect*	Connections::getConnect(int fds)
{
	std::map<int, Connect>::iterator	it;

	it = _connections.find(fds);
	if (it != _connections.end())
		return &(it->second);
	return NULL;
}

void	Connections::delConnect(int fds)
{
	std::map<int, Connect>::iterator	it;

	it = _connections.find(fds);
	if (it != _connections.end())
	{
		it->second.clean();		
		it->second.buffer.clean();
		_connections.erase(it);
	}
}
