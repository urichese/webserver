/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestBody.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 22:23:12 by msimon            #+#    #+#             */
/*   Updated: 2022/04/19 15:50:26 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_REQUESTBODY_HPP
# define WEBSERV_REQUESTBODY_HPP

# include <string>
# include <vector>
# include <fstream>
# include <unistd.h>
# include "AContent.hpp"
# include "Content.hpp"

# define MAX_SIZE_REQUESTBODY_HPP 65536

class	RequestBody
{
	public:
		RequestBody() {_len = 0;};
		~RequestBody();
		RequestBody(RequestBody const &obj);
		RequestBody	&operator=(RequestBody const &obj);
		void	add(char const* src, size_t const &len);
		void	add(std::string const& str);
		void	write_data(std::ofstream &file);
		void	write_data(AContent* cont);
		Content*	get_content(size_t index);
		void		cut(size_t index, size_t beg, size_t end);
		size_t	len();
		void	clean();
		void	print(size_t n = std::string::npos);

	private:
		std::vector<Content*>	_data;
		size_t					_len;
};

#endif
