/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AContent.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 18:05:58 by msimon            #+#    #+#             */
/*   Updated: 2022/04/14 21:34:54 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_ACONTENT_HPP
# define WEBSERV_ACONTENT_HPP

# include <iostream>
# include <string>
# include <cstring>
# include <exception>

class	AContent
{
	public:
		AContent(): _content(NULL), _len(0) {};
		virtual ~AContent();
		AContent(AContent const &obj);
		AContent	&operator=(AContent const &obj);
		
		char*			get_content() const {return _content;};
		std::string		get_line(size_t pos);
		size_t const&	len() const {return _len;};
		size_t 			find(std::string const& str, size_t beg = 0);
		void			cut(size_t beg, size_t end);
		void			init(size_t len);
		void			clean();
		void			print();
		void			push_back(char const* src, size_t const &len);
		void			push_back(std::string const& str);
		void			push_front(char const* src, size_t const &len);
		void			push_front(std::string const& str);
		virtual void	read(int fd, bool &f_soc_close) = 0;
		virtual void	read(std::string const &path) = 0;

	protected:
		char*	_content;
		size_t	_len;
};

#endif