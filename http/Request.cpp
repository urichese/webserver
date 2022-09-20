/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 09:08:21 by msimon            #+#    #+#             */
/*   Updated: 2022/04/20 16:46:04 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

int	Request::parse_head(Connect* conn)
{
	size_t		pos = conn->buffer.find("\r\n\r\n");
	size_t		line_pos = 0;

	if (pos == std::string::npos)
		return 0;
	while (line_pos < pos)
	{
		if (line_pos == 0)
			parse_first_line_head(conn, conn->buffer.get_line(line_pos));
		else
			parse_line_head(conn, conn->buffer.get_line(line_pos));
		line_pos = conn->buffer.find("\r\n", line_pos) + 2;
	}
	conn->buffer.cut(0, pos + 4);
	return 1;
}

void	Request::parse_first_line_head(Connect* conn, std::string str)
{
	size_t		pos;
	std::string	uri;
	size_t		pos_get_data;

	pos = str.find(" ");
	conn->head.add("method", str.substr(0, pos));
	if (pos == std::string::npos)
		return ;
	str = str.substr(pos + 1);
	pos = str.find(" ");
	uri = str.substr(0, pos);
	pos_get_data = uri.find("?");
	conn->head.add("uri", uri.substr(0, pos_get_data));
	if (pos_get_data != std::string::npos)
		conn->get_str = uri.substr(pos_get_data + 1);
	if (pos == std::string::npos)
		return ;
	conn->head.add("http", str.substr(pos + 1));
}

void	Request::parse_line_head(Connect* conn, std::string str)
{
	size_t				pos;

	pos = str.find(": ");
	if (pos != std::string::npos)
		conn->head.add(Connect::down_str(str.substr(0, pos)), str.substr(pos + 2));
	else
		conn->head.add(Connect::down_str(str.substr(0, pos)), "");
}

bool	Request::all_body_read(Connect* conn)
{
	size_t		cont_len = (size_t)std::atol(conn->head.get("content-length").data());
	std::string	encoding = Connect::down_str(conn->head.get("transfer-encoding"));
	if (encoding == "chunked")
	{
		size_t		pos = 0;
		size_t		size = 0;

		while (1)
		{
			pos = conn->buffer.find("\r\n");
			if (pos == std::string::npos)
				return 0;
			size = (size_t)std::strtoul(std::string(conn->buffer.get_content(), pos).data(), NULL, 16);
			pos += 2;
			if (conn->buffer.len() < (pos + size + 2))
				return 0;
			conn->body.add(conn->buffer.get_content() + pos, size);
			conn->buffer.cut(0, pos + size + 2);
			if (size == 0)
			{
				conn->statusReq = 2;
				return 1;
			}
		}
	}
	else if (cont_len > 0)
	{
		if (conn->body.len() + conn->buffer.len() >= cont_len)
		{
			size_t	len = conn->body.len();
			conn->body.add(conn->buffer.get_content(), cont_len - len);
			conn->buffer.cut(0, cont_len - len);
			conn->statusReq = 2;
			return 1;			
		}
		else
		{
			conn->body.add(conn->buffer.get_content(), conn->buffer.len());
			conn->buffer.clean();			
		}		
	}
	else
	{
		conn->statusReq = 2;		
		return 1;
	}
	return 0;
}
