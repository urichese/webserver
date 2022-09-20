/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Content.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:38:04 by msimon            #+#    #+#             */
/*   Updated: 2022/04/12 20:29:32 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_CONTENT_HPP
# define WEBSERV_CONTENT_HPP

# include "AContent.hpp"

class Content: public AContent
{
	public:
		virtual	~Content(){};
		
	private:
		virtual void	read(int fd, bool &f_soc_close) {(void) fd; (void) f_soc_close;};
		virtual void	read(std::string const &path) {(void) path;};
};

#endif