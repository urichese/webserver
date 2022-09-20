/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ContentFile.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:01:03 by msimon            #+#    #+#             */
/*   Updated: 2022/04/12 20:29:28 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_CONTENTFILE_HPP
# define WEBSERV_CONTENTFILE_HPP

# include <fstream>
# include <sys/stat.h>
# include "AContent.hpp"

class ContentFile: public AContent
{
	public:
		virtual			~ContentFile(){};	
		virtual void	read(std::string const &path);

	private:
		virtual void	read(int fd, bool &f_soc_close) {(void) fd; (void) f_soc_close;};
};

#endif