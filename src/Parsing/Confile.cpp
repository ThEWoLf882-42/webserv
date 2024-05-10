/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Confile.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:35:17 by mel-moun          #+#    #+#             */
/*   Updated: 2024/05/02 17:01:02 by mel-moun         ###   ########.fr       */
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
		input = ob.input;
	return *this;
}

wbs::Confile::Confile(const Confile &ob)
{
	*this = ob;
}

wbs::Confile::~Confile()
{
}

std::vector<hopo> wbs::Confile::get_hop()
{
	return hop;
}

/********************** Main Parsing's functions *****************************/

void wbs::Confile::parsing()
{
	closed_brackets();
	syntax_error();
	parse();
	check_semicolon();

	for (std::vector<Infos>::iterator it = servers.begin(); it != servers.end(); it++)
	{
		it->port_host_set();
		it->rootset();
	}
	the_list();
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
					if (key == "error_pages" || key == "error_page")
						object.set_error_pages(ss);			
					else
					{
						while (ss >> value)
						{
							values.push_back(value);
						}
						object.set_directives(key, values);
					}
					values.clear();
					ss.clear();
				}
				else if (key == "location")
				{
					Location ob_location;
					ob_location.set_path(take_path(input, key));
					std::getline(infile, input);
					while (std::getline(infile, input))
					{
						if (input.empty() || only_spaces(input))
							continue;
						std::istringstream ss(input);
						ss >> key;
						if (key == "}")
						{
							object.set_locations(ob_location);
							break;
						}
						while (ss >> value)
						{
							values.push_back(value);
						}
						ob_location.insert(std::make_pair(key, values));
						values.clear();
						ss.clear();
					}
				}
				else if (key == "}")
				{
					servers.push_back(object);
					// object.print_directives();
					// object.print_error_pages();
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
		it->end_map();
		for (std::vector<Location>::iterator loc = it->get_locations().begin(); loc != it->get_locations().end(); loc++)
			loc->end_map_location();
	}
}

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
			std::vector<std::string> all_keys;

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
				{
					if (key != "error_page" && key != "error_pages")
						key_duplicated(all_keys, key);
					// CHECK WECH DUPLICATED
					// CHECK WECH NOT VALID
					count_semicolons(input, 1);
					key_invalid(key);
				}
				else if (key == "location")
				{
					std::vector<std::string> loc_keys;
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
						else
						{
							key_invalid(key);
							key_duplicated(loc_keys, key);
						}
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

void wbs::Confile::the_list()
{
	for (std::vector<Infos>::iterator hoit = servers.begin(); hoit != servers.end(); hoit++)
	{
		for (std::vector<unsigned int>::iterator poit = hoit->get_ports().begin(); poit != hoit->get_ports().end(); poit++)
		{
			hopo hp;
			hp.inf = &(*hoit);
			hp.ho = hoit->get_host();
			hp.po = *poit;
			hop.push_back(hp);
		}
	}
	int i = 0;
	for (std::vector<hopo>::iterator it = hop.begin(); it != hop.end(); it++)
	{
		std::cout << "number: " << ++i << std::endl
				  << "	host: " << it->ho << std::endl
				  << "	port: " << it->po << std::endl;
	}
}

void	wbs::Confile::key_duplicated(std::vector<std::string>& all_keys, const std::string& value)
{
	std::vector<std::string>::iterator it = find(all_keys.begin(), all_keys.end(), value);
	if (it != all_keys.end())
		throw std::runtime_error("Duplicated key");
	all_keys.push_back(value);
}

void	wbs::Confile::key_invalid(const std::string& value) // SEE WHAT U CAN ADD
{
	std::vector<std::string> valid;
	valid.push_back("listen");
	valid.push_back("server_name");
	valid.push_back("error_page");
	valid.push_back("error_pages");
	valid.push_back("client_body_size");
	valid.push_back("root");
	valid.push_back("autoindex");
	valid.push_back("cgi_extension");
	valid.push_back("cgi_bin");
	valid.push_back("methods");
	valid.push_back("return");
	valid.push_back("default_file");

	std::vector<std::string>::iterator it = find(valid.begin(), valid.end(), value);
	if (it == valid.end())
		throw std::runtime_error("Invalid key");
}
