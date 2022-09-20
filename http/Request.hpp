/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 08:53:28 by msimon            #+#    #+#             */
/*   Updated: 2022/04/13 14:05:23 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_REQUEST_HPP
# define WEBSERV_REQUEST_HPP

# include <string>
# include <vector>
# include "Connect.hpp"

class	Request
{
	public:
		Request() {};
		~Request() {};
		int		parse_head(Connect* conn);
		bool	all_body_read(Connect* conn);
	
	private:
		void	parse_first_line_head(Connect* conn, std::string str);
		void	parse_line_head(Connect* conn, std::string str);
};

#endif
