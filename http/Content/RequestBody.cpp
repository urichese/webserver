/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestBody.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 10:06:31 by msimon            #+#    #+#             */
/*   Updated: 2022/04/19 15:50:09 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "RequestBody.hpp"

RequestBody::~RequestBody()
{
	std::vector<Content*>::iterator	it = _data.begin();

	while (it != _data.end())
	{
		delete (*it);
		it++;
	}
}

RequestBody::RequestBody(RequestBody const &obj)
{
	*this = obj;
}

RequestBody	&RequestBody::operator=(RequestBody const &obj)
{
	if (this != &obj)
	{
		std::vector<Content*>::iterator it = _data.begin();

		while (it != _data.end())
		{
			delete (*it);
			it++;
		}
		_data.clear();
		
		for (size_t	i = 0; i < obj._data.size(); i++)
			_data.push_back(obj._data[i]);
		_len = obj._len;
	}
	return (*this);
}

void	RequestBody::add(char const* src, size_t const &len)
{
	if (_data.size() == 0)
	{
		_data.push_back(new Content());
		_len = 0;
	}
	_data[_data.size() - 1]->push_back(src, len);
	_len += len;
	if (_data[_data.size() - 1]->len() > MAX_SIZE_REQUESTBODY_HPP)
		_data.push_back(new Content());
}

void	RequestBody::add(std::string const& str)
{
	if (_data.size() == 0)
	{
		_data.push_back(new Content());
		_len = 0;
	}
	_data[_data.size() - 1]->push_back(str);
	_len += str.length();
	if (_data[_data.size() - 1]->len() > MAX_SIZE_REQUESTBODY_HPP)
		_data.push_back(new Content());
}

void	RequestBody::write_data(std::ofstream &file)
{
	std::vector<Content*>::iterator	it = _data.begin();

	while (it != _data.end())
	{
		file.write((*it)->get_content(), (*it)->len());
		it++;
	}
}

size_t	RequestBody::len()
{
	return _len;
}

void	RequestBody::clean()
{
	std::vector<Content*>::iterator	it = _data.begin();

	while (it != _data.end())
	{
		delete (*it);
		it++;
	}
	_data.clear();
	_len = 0;
}

void	RequestBody::print(size_t n)
{
	if (n == std::string::npos)
	{
		std::vector<Content*>::iterator	it = _data.begin();

		while (it != _data.end())
		{
			(*it)->print();
			it++;
		}
	}
	else if (n < _data.size())
		_data[n]->print();

}

void	RequestBody::write_data(AContent* cont)
{
	cont->init(_len);
	size_t	pos = 0;
	std::vector<Content*>::iterator	it = _data.begin();

	while (it != _data.end())
	{
		std::memcpy(cont->get_content() + pos, (*it)->get_content(), (*it)->len());
		pos += (*it)->len();
		it++;
	}
}

Content*	RequestBody::get_content(size_t index)
{
	if (index < _data.size())
		return _data[index];
	return NULL;
}

void		RequestBody::cut(size_t index, size_t beg, size_t end)
{
	if (index < _data.size())
	{
		size_t	buf_len = _data[index]->len();
		_data[index]->cut(beg, end);
		_len = _len - buf_len + _data[index]->len();
	}
}