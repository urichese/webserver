/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ContentSocket.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:39:32 by msimon            #+#    #+#             */
/*   Updated: 2022/04/21 08:14:24 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ContentSocket.hpp"

void	ContentSocket::read(int fd, bool &f_soc_close)
{
	char*	buffer;
	ssize_t	read_len;

	f_soc_close = 0;
	try {buffer = new char[BUFFER_SIZE_CONTENTSOCKET_HPP];}
	catch (std::exception &e) {throw (std::runtime_error("500"));}
	read_len = recv(fd, buffer, BUFFER_SIZE_CONTENTSOCKET_HPP, 0);
	if (read_len < 0)
	{
		delete[] buffer;
		throw (std::runtime_error("900"));
	}
	if (read_len == 0)
	{
		delete[] buffer;
		f_soc_close = 1;
		return ;
	}
	while (read_len == BUFFER_SIZE_CONTENTSOCKET_HPP)
	{
		this->push_back(buffer, read_len);
		read_len = recv(fd , buffer, BUFFER_SIZE_CONTENTSOCKET_HPP, 0);
		if (read_len < 0)
		{
			delete[] buffer;
			throw (std::runtime_error("900"));
		}
	}
	this->push_back(buffer, read_len);
	delete[] buffer;
}
