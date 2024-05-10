/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Infos.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:37:01 by mel-moun          #+#    #+#             */
/*   Updated: 2024/05/02 13:13:19 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

wbs::Infos::Infos()
{
}

wbs::Infos::Infos(const Infos &ob)
{
	*this = ob;
}

wbs::Infos &wbs::Infos::operator=(const Infos &ob)
{
	if (this != &ob)
	{
		directives = ob.directives;
		locations = ob.locations;
	}
	return *this;
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
			std::cout << "Path: " << loc->get_path() << std::endl;
			std::map<std::string, std::vector<std::string> >::iterator mini = loc->get_params().begin();
			for (; mini != loc->get_params().end(); mini++)
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

void wbs::Infos::end_map()
{
	std::map<std::string, std::vector<std::string> >::iterator it = directives.begin();
	for (; it != directives.end(); it++)
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
		std::istringstream iss(octetStr);
		int octetValue;
		if (!(iss >> octetValue) || octetValue < 0 || octetValue > 255)
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
	// std::cout << "host: " << host << std::endl;

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

void wbs::Infos::rootset()
{
	std::map<std::string, std::vector<std::string> >::iterator it = directives.find("root");

	if (it != directives.end())
		root = it->second[0];
	else
		root = "./";
	for (std::vector<Location>::iterator lit = locations.begin(); lit != locations.end(); lit++)
		lit->rootset();
}

void wbs::Infos::set_directives(const std::string &key, const std::vector<std::string> &array)
{
	this->directives.insert(std::make_pair(key, array));
}

void wbs::Infos::set_locations(const Location &location)
{
	this->locations.push_back(location);
}

std::map<std::string, std::vector<std::string> > &wbs::Infos::get_directives()
{
	return this->directives;
}

std::vector<wbs::Location> &wbs::Infos::get_locations()
{
	return this->locations;
}

std::vector<unsigned int> &wbs::Infos::get_ports()
{
	return ports;
}

std::string wbs::Infos::get_root()
{
	return root;
}

unsigned int &wbs::Infos::get_host()
{
	return host;
}

void wbs::Infos::set_error_pages(std::istream& ss) 
{
	std::string	test, key;
	char	*ptr;
	int		count = 0, num;

	ss >> key;
	num = std::strtod(key.c_str(), &ptr);
	if (num <= 0)
		throw std::runtime_error("Error Pages");
	if (ptr[0] != '\0')
		throw std::runtime_error("Error Pages");
	check_duplicated(duplicated, num);
	std::string value;
	ss >> value;
	while (ss >> test)
	{
		count++;
	}
	if ((count != 1 || count == 1) && test != ";")
		throw std::runtime_error("Error Pages");
	error_pages[num] = value;
	duplicated.push_back(num);
}

void	wbs::Infos::print_error_pages()
{
	std::map<int, std::string>::iterator it = error_pages.begin();

	for (; it != error_pages.end(); it++)
	{
		std::cout <<  "key=> " << it->first << " value=> " << it->second << std::endl;
	}
}

void	wbs::Infos::check_duplicated(const std::vector<int>& vec, int num)
{
	std::vector<int>::const_iterator it = find(vec.begin(), vec.end(), num);
	if (it != vec.end())
		throw std::runtime_error("Error code is duplicated");
}
