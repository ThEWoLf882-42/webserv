/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:18:32 by mel-moun          #+#    #+#             */
/*   Updated: 2024/06/01 10:48:20 by agimi            ###   ########.fr       */
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
		path = ob.path;
		params = ob.params;
		root = ob.root;
	}
	return *this;
}

void wbs::Location::insert(const std::pair<std::string, std::vector<std::string> > &p)
{
	params.insert(p);
}

void wbs::Location::set_path(const std::string &p)
{
	path = p;
}

std::string wbs::Location::get_path() const
{
	return path;
}

std::string wbs::Location::get_root() const
{
	return root;
}

std::map<std::string, std::vector<std::string> > &wbs::Location::get_params()
{
	return params;
}

void wbs::Location::end_map_location()
{
	std::map<std::string, std::vector<std::string> >::iterator it = params.begin();
	for (; it != params.end(); it++)
	{
		if (it->second.back() != ";")
			throw std::runtime_error("ERROR ;");
	}
}

void wbs::Location::rootset()
{
	std::map<std::string, std::vector<std::string> >::iterator it = params.find("root");

	if (it != params.end())
		root = it->second[0];
	else
		root = "";
}
