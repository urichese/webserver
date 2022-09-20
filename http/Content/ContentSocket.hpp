/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ContentSocket.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:32:39 by msimon            #+#    #+#             */
/*   Updated: 2022/04/14 13:16:30 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_CONTENTSOCKET_HPP
# define WEBSERV_CONTENTSOCKET_HPP

# include <sys/socket.h>
# include "AContent.hpp"

# define BUFFER_SIZE_CONTENTSOCKET_HPP 131072

class ContentSocket: public AContent
{
	public:
		virtual 		~ContentSocket(){};
		virtual void	read(int fd, bool &f_soc_close);

	private:
		virtual void	read(std::string const &path) {(void) path;};
};

#endif