/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Confile.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:35:17 by mel-moun          #+#    #+#             */
/*   Updated: 2024/02/14 12:07:42 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

/********************** Orthodox Form ****************************************/

wbs::Confile::Confile()
{
	infile.open(DEF_CONF);
	if (!infile.is_open())
		throw std::runtime_error("Error occured while opening the config file.");
	parsing();
}

wbs::Confile::Confile(const std::string &file)
{
	infile.open(file);
	if (!infile.is_open())
		throw std::runtime_error("Error occured while opening the config file.");
	parsing();
}

wbs::Confile &wbs::Confile::operator=(const Confile &ob)
{
	if (this != &ob)
	{
		input = ob.input;
	}
	return *this;
}

wbs::Confile::Confile(const Confile &ob)
{
	*this = ob;
}

wbs::Confile::~Confile()
{
}

/********************** Main Parsing's functions *****************************/

void wbs::Confile::parsing()
{
	closed_brackets();
	syntax_error();
	parse();
	check_semicolon();
	for (std::vector<Infos>::iterator it = servers.begin(); it != servers.end(); it++)
		it->port_host_set();
}

/********************** Parsing's functions **********************************/

void wbs::Confile::closed_brackets()
{
	int opened = 0;
	int closed = 0;

	while (std::getline(infile, input))
	{
		for (int i = 0; input[i]; i++)
		{
			if (input[i] == '{')
				opened++;
			else if (input[i] == '}')
			{
				if (opened != 0)
					opened--;
				else
					throw std::runtime_error("Brackets are not closed.");
			}
		}
	}
	if (!(opened == 0 && closed == 0))
		throw std::runtime_error("Brackets are not closed.");
}

// void wbs::Confile::print_directives()
// {
// 	static int i = 1;
// 	std::cout << "------------ Server: " << i << " --------------" << std::endl;
// 	i++;
// 	std::cout << "Directives: ******** " << std::endl;
// 	if (directives.empty())
// 		std::cout << "Empty Directives" << std::endl;
// 	else
// 	{
// 		std::map<std::string, std::vector<std::string> >::iterator it = directives.begin();
// 		for (; it != directives.end(); it++)
// 		{
// 			std::cout << "Key: " << it->first << std::endl;
// 			std::vector<std::string>::iterator vec = it->second.begin();
// 			std::cout << "Values: ";
// 			for (; vec != it->second.end(); vec++)
// 				std::cout << "[" << *vec << "] ";
// 			std::cout << std::endl
// 					  << std::endl;
// 		}
// 	}

// 	std::cout << "Locations: ********" << std::endl;
// 	int j = 1;
// 	if (locations.empty())
// 		std::cout << "EMPTY\n";
// 	else
// 	{
// 		std::vector<Location>::iterator loc = locations.begin();
// 		for (; loc != locations.end(); loc++)
// 		{
// 			std::cout << "Location " << j++ << std::endl;
// 			std::cout << "Path: " << loc->path << std::endl;
// 			std::map<std::string, std::vector<std::string> >::iterator mini = loc->params.begin();
// 			for (; mini != loc->params.end(); mini++)
// 			{
// 				std::cout << "Key: " << mini->first << std::endl;
// 				std::vector<std::string>::iterator vec = mini->second.begin();
// 				std::cout << "Values: ";
// 				for (; vec != mini->second.end(); vec++)
// 					std::cout << "[" << *vec << "] ";
// 				std::cout << std::endl
// 						  << std::endl;
// 			}
// 		}
// 	}
// }

int only_spaces(const std::string &str)
{
	for (size_t i = 0; i < str.length(); ++i)
		if (str[i] != ' ')
			return 0;
	return 1;
}

void wbs::Confile::parse()
{
	std::string key;
	std::string value;
	std::vector<std::string> values;

	infile.clear();
	infile.seekg(0, std::ios::beg);
	while (std::getline(infile, input))
	{
		std::stringstream ss(input);
		ss >> key;
		if (key == "server")
		{
			take_path(input, key);
			Infos object;
			std::getline(infile, input);
			while (std::getline(infile, input))
			{
				if (input.empty() || only_spaces(input))
					continue;
				std::istringstream ss(input);
				ss >> key;
				if (key != "location" && key != "}" && key != ";")
				{
					while (ss >> value)
					{
						values.push_back(value);
					}
					object.directives.insert(std::make_pair(key, values));
					values.clear();
					ss.clear();
				}
				else if (key == "location")
				{
					Location ob_location;
					ob_location.path = take_path(input, key);
					std::getline(infile, input);
					while (std::getline(infile, input))
					{
						if (input.empty() || only_spaces(input))
							continue;
						std::istringstream ss(input);
						ss >> key;
						if (key == "}")
						{
							object.locations.push_back(ob_location);
							break;
						}
						while (ss >> value)
						{
							values.push_back(value);
						}
						ob_location.params.insert(std::make_pair(key, values));
						values.clear();
						ss.clear();
					}
				}
				else if (key == "}")
				{
					servers.push_back(object);
					break;
				}
			}
		}
		else if (input.empty() || only_spaces(input))
			continue;
	}
}

const std::string wbs::Confile::take_path(const std::string &input, const std::string &key)
{
	std::stringstream ss(input);
	std::string value;
	int count = 0;

	while (ss >> value)
		count++;
	if (key == "location")
	{
		if (count != 2)
			throw std::runtime_error("Location have more than one argument.");
	}
	else if (count != 1)
		throw std::runtime_error("Server shouldn't have an argument.");
	return value;
}

void wbs::Confile::check_semicolon()
{
	std::vector<Infos>::iterator it = servers.begin();
	for (; it != servers.end(); it++)
	{
		it->end_map(it->directives);
		for (std::vector<Location>::iterator loc = it->locations.begin(); loc != it->locations.end(); loc++)
		{
			loc->end_map_location(loc->params);
		}
	}
}

// void wbs::Confile::end_map(std::map<std::string, std::vector<std::string> > &map)
// {
// 	std::map<std::string, std::vector<std::string> >::iterator it = map.begin();
// 	for (; it != map.end(); it++)
// 		if (it->second.back() != ";")
// 			throw std::runtime_error("ERROR ;");
// }

void wbs::Confile::syntax_error()
{
	std::string key;
	std::string value;

	infile.clear();
	infile.seekg(0, std::ios::beg);
	while (std::getline(infile, input))
	{
		std::stringstream ss(input);
		ss >> key;
		if (key == "server")
		{
			std::getline(infile, input);
			if (input != "{")
				throw std::runtime_error("After server it should be {");
			while (std::getline(infile, input))
			{
				if (input.empty() || only_spaces(input))
					continue;
				std::istringstream ss(input);
				ss >> key;
				if (key != "location" && key != "}" && key != ";")
					count_semicolons(input, 1);
				else if (key == "location")
				{
					count_semicolons(input, 0);
					std::getline(infile, input);
					ss.str(input);
					ss >> value;
					if (value != "{")
						throw std::runtime_error("Syntax Error in location");
					while (std::getline(infile, input))
					{
						if (input.empty() || only_spaces(input))
							continue;
						std::istringstream ss(input);
						ss >> key;
						if (key == "}")
							break;
						else if (key == ";")
							throw std::runtime_error("; Should not be in a single line");
						count_semicolons(input, 1);
					}
				}
				else if (key == ";")
					throw std::runtime_error("; Should not be in a single line");
				else if (key == "}")
					break;
			}
		}
		else if (input.empty() || only_spaces(input))
			continue;
		else
			throw(std::runtime_error("Garbagge"));
	}
}

void wbs::Confile::count_semicolons(const std::string &str, int i)
{
	int count = std::count(str.begin(), str.end(), ';');
	if (count != i)
		throw std::runtime_error("It should have only one ;");
}
