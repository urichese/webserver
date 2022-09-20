/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connect.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:44:34 by msimon            #+#    #+#             */
/*   Updated: 2022/04/20 12:05:22 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_CONNECT_HPP
# define WEBSERV_CONNECT_HPP

# include <ctime>
# include "RequestData.hpp"
# include "Route.hpp"
# include "ContentSocket.hpp"
# include "Content.hpp"
# include "RequestBody.hpp"

class Connect {
	public:
		Connect(int _fds): fds(_fds), timeReq(time(NULL)), statusReq(0), location(NULL) {};
		~Connect() {};
		int				fds;
		time_t			timeReq;
		int				statusReq;
		const Route*	location;
		ContentSocket	buffer;
		RequestBody		body;
		RequestData		head;
		std::string		get_str;
		std::string		full_file_path;
		
		void				clean();
		static std::string	down_str(std::string str);
		static std::string	key_to_cgi(std::string str);

	private:
		Connect();
};

#endif