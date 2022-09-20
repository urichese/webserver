/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responce.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:14:46 by msimon            #+#    #+#             */
/*   Updated: 2022/04/21 12:01:15 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_RESPONCE_HPP
# define WEBSERV_RESPONCE_HPP

# include <sys/types.h>
# include <sys/socket.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include <fstream>
# include <string>
# include <cstdio>
# include <map>
# include <exception>
# include <cstdlib>
# include <ctime>
# include "Connect.hpp"
# include "AContent.hpp"
# include "Content.hpp"
# include "ContentFile.hpp"
# include "HandlerCGI.hpp"

class	Responce: public HandlerCGI
{
	public:
		Responce();
		~Responce();
		void				sending(Connect* conn, std::string const& http_code);
		std::string	const&	get_code(std::string const& code);

	private:
		std::string							_head;
		AContent							*_body;
		std::string							_server_name;
		std::map<std::string, std::string>	_code_error_text;
		std::map<std::string, std::string>	_mime_list;

		std::string	getExtension(std::string const& path);
		std::string	getType(std::string const& path);
		
		void		set_other_page(Connect* conn, std::string const& code, bool f_body = 1);
		void		set_redirection(Connect* conn);
		void		set_index_page(Connect* conn);
		void		set_directories(Connect* conn);
		void		set_load_file(Connect* conn);
		void		set_delete_file(Connect* conn);
		void		set_content_file(Connect* conn);
};

#endif