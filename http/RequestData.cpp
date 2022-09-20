/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestData.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:58:30 by msimon            #+#    #+#             */
/*   Updated: 2022/04/21 06:20:26 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestData.hpp"

void	RequestData::add(std::string name, std::string val)
{
	del(name);
	_data.insert(std::pair<std::string, std::string> (name, val));
}

std::string	RequestData::get(std::string name)
{
	std::map<std::string, std::string>::iterator	it;

	it = _data.find(name);
	if (it != _data.end())
		return it->second;
	return std::string("");
}

void	RequestData::print()
{
	std::map<std::string, std::string>::iterator	it = _data.begin();
	
	while (it != _data.end())
	{
		std::cout << it->first << ": " << it->second << "\n";
		it++;
	}
}

void	RequestData::del(std::string name)
{
	std::map<std::string, std::string>::iterator	it;

	it = _data.find(name);
	if (it != _data.end())
		_data.erase(it);
}

void	RequestData::clean()
{
	_data.clear();
}