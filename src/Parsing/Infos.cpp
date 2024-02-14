/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Infos.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:37:01 by mel-moun          #+#    #+#             */
/*   Updated: 2024/02/14 11:43:08 by agimi            ###   ########.fr       */
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

unsigned int wbs::Infos::stip(const std::string &str)
{
	if (str == "localhost")
		return 0x7F000001;

	unsigned int ip = 0;
	size_t start = 0;

	for (size_t i = 0; i < 4; ++i)
	{
		size_t sep = str.find('.', start);
		if (sep == std::string::npos)
			sep = str.length();

		std::string octetStr = str.substr(start, sep - start);
		int octetValue = atoi(octetStr.c_str());

		if (octetValue < 0 || octetValue > 255)
			throw std::invalid_argument("Invalid IP address");

		ip |= (octetValue << ((3 - i) * 8));

		if (sep == str.length())
			break;

		start = sep + 1;
	}

	return ip;
}

void wbs::Infos::port_host_set()
{
	std::map<std::string, std::vector<std::string> >::iterator it = directives.find("host");
	std::vector<std::string> d;

	if (it != directives.end())
		host = stip(it->second[0]);
	else
		host = INADDR_ANY;
	std::cout << "host: " << host << std::endl;

	it = directives.find("listen");
	if (it != directives.end())
	{
		d = it->second;
		for (std::vector<std::string>::iterator itv = d.begin(); itv != d.end() - 1; itv++)
		{
			unsigned int por;
			std::stringstream s(*itv);

			s >> por;
			std::cout << "	port: " << por << std::endl;
			ports.push_back(por);
		}
	}
}