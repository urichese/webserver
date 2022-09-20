/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:57:20 by msimon            #+#    #+#             */
/*   Updated: 2022/04/25 21:29:49 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_CONNECTIONS_HPP
# define WEBSERV_CONNECTIONS_HPP

# include <map>
# include <vector>
# include <cstdlib>
# include <ctime>
# include "Connect.hpp"
# include "Request.hpp"
# include "Responce.hpp"
# include "GetServer.hpp"

class	Connections: public Request, public Responce, public GetServer
{
	public:
		Connections() {};
		~Connections() {};
		int					read_request(int fds, std::vector<const ServerConfig*> const &srvs_config);
		std::vector<int>	checkTime(time_t time_out);

	private:
		std::map<int, Connect>	_connections;
		Connect*				getConnect(int fds);
		void					delConnect(int fds);
};

#endif