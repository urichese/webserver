/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AContent.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 18:28:33 by msimon            #+#    #+#             */
/*   Updated: 2022/04/21 08:13:06 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AContent.hpp"

AContent::~AContent()
{
	if (_content)
		delete[] _content;
}

AContent::AContent(AContent const &obj): _content(NULL), _len(0)
{
	*this = obj;
}

AContent	&AContent::operator=(AContent const &obj)
{
	if (this != &obj)
	{
		if (_content)
			delete[] _content;
		if (obj.len())
		{
			try {_content = new char[obj.len()];}
			catch (std::exception &e) {
				_content = NULL;
				_len = 0;
				throw (std::runtime_error("500"));
			}
			_len = obj.len();
			std::memcpy(_content, obj.get_content(), _len);
		}
		else
		{
			_content = NULL;
			_len = 0;
		}
	}
	return (*this);
}

size_t AContent::find(std::string const& str, size_t beg)
{
	if (_len < str.length())
		return std::string::npos;

	for (size_t i = beg; i <= _len - str.length(); i++)
		if (!std::memcmp(_content + i, str.data(), str.length()))
			return i;
	return std::string::npos;
}

void	AContent::cut(size_t beg, size_t end)
{
	if (end > _len)
		end = _len;
	if (end <= beg)
		return ;
	if (end - beg == _len)
	{
		if (_content)
		 	delete[] _content;
		_content = NULL;
		_len = 0;
		return ;
	}
	char*	n_content;

	try {n_content = new char[_len - (end - beg)];}
	catch (std::exception &e) {throw (std::runtime_error("500"));}
	std::memcpy(n_content, _content, beg);
	std::memcpy(n_content + beg, _content + end, _len - end);
	if (_content)
		delete[] _content;
	_len = _len - (end - beg);
	_content = n_content;
}

void	AContent::clean()
{
	if (_content)
	 	delete[] _content;
	_content = NULL;
	_len = 0;
}

void	AContent::init(size_t len)
{
	this->clean();
	if (len)
	{
		_content = new char[len];
		_len = len;
	}
}

void	AContent::print()
{
	for (size_t i = 0; i < _len; i++)
		std::cout << _content[i];
}

void	AContent::push_back(char const* src, size_t const &len)
{
	char*	n_content;

	try {n_content = new char[_len + len];}
	catch (std::exception &e) {throw (std::runtime_error("500"));}
	std::memcpy(n_content, _content, _len);
	std::memcpy(n_content + _len, src, len);
	_len = _len + len;
	if (_content)
		delete[] _content;
	_content = n_content;
}

void	AContent::push_back(std::string const& str)
{
	char*	n_content;

	try {n_content = new char[_len + str.length()];}
	catch (std::exception &e) {throw (std::runtime_error("500"));}
	std::memcpy(n_content, _content, _len);
	std::memcpy(n_content + _len, str.data(), str.length());
	_len = _len + str.length();
	if (_content)
		delete[] _content;
	_content = n_content;
}

void	AContent::push_front(char const* src, size_t const &len)
{
	char*	n_content;

	try {n_content = new char[_len + len];}
	catch (std::exception &e) {throw (std::runtime_error("500"));}
	std::memcpy(n_content, src, len);
	std::memcpy(n_content +len, _content, _len);
	_len = _len + len;
	if (_content)
		delete[] _content;
	_content = n_content;	
}

void	AContent::push_front(std::string const& str)
{
	char*	n_content;

	try {n_content = new char[_len + str.length()];}
	catch (std::exception &e) {throw (std::runtime_error("500"));}
	std::memcpy(n_content, str.data(), str.length());
	std::memcpy(n_content + str.length(), _content, _len);
	_len = _len + str.length();
	if (_content)
		delete[] _content;
	_content = n_content;	
}

std::string		AContent::get_line(size_t pos)
{
	std::string	res;
	size_t		f_pos = find("\r\n", pos);

	if (f_pos == std::string::npos)
	{
		if (_len < pos)
			return std::string("");
		return std::string(_content + pos, _len - pos);
	}
	else
		return std::string(_content + pos, f_pos - pos);
}
