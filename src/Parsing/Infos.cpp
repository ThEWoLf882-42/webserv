/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Infos.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:37:01 by mel-moun          #+#    #+#             */
/*   Updated: 2024/02/14 10:31:33 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

wbs::Infos::Infos()
{
}

wbs::Infos::Infos(const Infos &ob) : directives(ob.directives), locations(ob.locations)
{
}

wbs::Infos &wbs::Infos::operator=(const Infos &ob)
{
	if (this != &ob)
	{
		directives = ob.directives;
		locations = ob.locations;
	}
	return (*this);
}

wbs::Infos::~Infos()
{
}

void wbs::Infos::print_directives()
{
	static int i = 1;
	std::cout << "------------ Server: " << i << " --------------" << std::endl;
	i++;
	std::cout << "Directives: ******** " << std::endl;
	if (directives.empty())
		std::cout << "Empty Directives" << std::endl;
	else
	{
		std::map<std::string, std::vector<std::string> >::iterator it = directives.begin();
		for (; it != directives.end(); it++)
		{
			std::cout << "Key: " << it->first << std::endl;
			std::vector<std::string>::iterator vec = it->second.begin();
			std::cout << "Values: ";
			for (; vec != it->second.end(); vec++)
				std::cout << "[" << *vec << "] ";
			std::cout << std::endl
					  << std::endl;
		}
	}

	std::cout << "Locations: ********" << std::endl;
	int j = 1;
	if (locations.empty())
		std::cout << "EMPTY\n";
	else
	{
		std::vector<Location>::iterator loc = locations.begin();
		for (; loc != locations.end(); loc++)
		{
			std::cout << "Location " << j++ << std::endl;
			std::cout << "Path: " << loc->path << std::endl;
			std::map<std::string, std::vector<std::string> >::iterator mini = loc->params.begin();
			for (; mini != loc->params.end(); mini++)
			{
				std::cout << "Key: " << mini->first << std::endl;
				std::vector<std::string>::iterator vec = mini->second.begin();
				std::cout << "Values: ";
				for (; vec != mini->second.end(); vec++)
					std::cout << "[" << *vec << "] ";
				std::cout << std::endl
						  << std::endl;
			}
		}
	}
}

// void	Confile::check_semicolon()
// {
// 	std::vector<Infos>::iterator it = servers.begin();
// 	for (; it != servers.end(); it++)
// 	{
// 		it->end_map(it->directives);
// 		for (std::vector<Location>::iterator loc = it->locations.begin(); loc != it->locations.end(); loc++)
// 		{
// 			loc->end_map_location(loc->params);
// 		}
// 	}
// }

void wbs::Infos::end_map(std::map<std::string, std::vector<std::string> > &map)
{
	std::map<std::string, std::vector<std::string> >::iterator it = map.begin();
	for (; it != map.end(); it++)
	{
		if (it->second.back() != ";")
			throw std::runtime_error("ERROR ;");
	}
}

void wbs::Infos::port_host_set()
{
	std::map<std::string, std::vector<std::string> >::iterator it = directives.find("server_name");
	std::vector<std::string> d;

	if (it != directives.end())
		host = it->second[0];
	// std::cout << "server_name: " << host << std::endl;

	it = directives.find("listen");
	if (it != directives.end())
	{
		d = it->second;
		for (std::vector<std::string>::iterator itv = d.begin(); itv != d.end() - 1; itv++)
		{
			unsigned int por;
			std::stringstream s(*itv);

			s >> por;
			// std::cout << "	port: " << por << std::endl;
			ports.push_back(por);
		}
	}
}