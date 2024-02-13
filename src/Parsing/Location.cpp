/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:18:32 by mel-moun          #+#    #+#             */
/*   Updated: 2024/02/13 17:48:43 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

wbs::Location::Location()
{
}

wbs::Location::~Location()
{
}

wbs::Location::Location(const Location &ob)
{
	*this = ob;
}

wbs::Location &wbs::Location::operator=(const Location &ob)
{
	if (this != &ob)
	{
		this->path = ob.path;
		this->params = ob.params;
	}
	return (*this);
}

void wbs::Location::end_map_location(std::map<std::string, std::vector<std::string> > &map)
{
	std::map<std::string, std::vector<std::string> >::iterator it = map.begin();
	for (; it != map.end(); it++)
	{
		if (it->second.back() != ";")
			throw std::runtime_error("ERROR ;");
	}
}
