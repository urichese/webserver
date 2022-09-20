/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ContentFile.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:02:24 by msimon            #+#    #+#             */
/*   Updated: 2022/04/08 22:08:14 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ContentFile.hpp"

void	ContentFile::read(std::string const &path)
{
	struct stat			buf;
	std::ifstream		file;

	if (!stat(path.data(), &buf))
	{
		file.open(path.data());
		if (file.is_open())
		{
			if (_content)
			{
				delete[] _content;
				_len = 0;
				_content = NULL;
			}
			try {_content = new char[buf.st_size];}
			catch (std::exception &e)
			{
				_content = NULL;
				file.close();
				throw (std::runtime_error("500"));
			}
			file.read(_content, buf.st_size);
			if (file.rdstate() & std::ifstream::failbit || file.rdstate() & std::ifstream::badbit)
				throw (std::runtime_error("404"));//403
			_len = buf.st_size;
			file.close();
		}
		else
			throw (std::runtime_error("403"));//403
	}
	else
		throw (std::runtime_error("404"));
}