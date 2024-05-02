/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Infos.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:34:15 by mel-moun          #+#    #+#             */
/*   Updated: 2024/05/02 10:08:52 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <webserv.hpp>

namespace wbs
{
	class Infos
	{
	private:
		std::map<std::string, std::vector<std::string> > directives;
		std::vector<Location> locations;
		std::vector<unsigned int> ports;
		std::string root;
		unsigned int host;

		std::map<int, std::string> error_pages;
		
	public:
		Infos();
		Infos(const Infos &);
		Infos &operator=(const Infos &);
		~Infos();

		void set_directives(const std::string &key, const std::vector<std::string> &array);
		void set_locations(const Location &location);
		void print_directives();

		std::map<std::string, std::vector<std::string> > &get_directives();
		std::vector<Location> &get_locations();
		std::vector<unsigned int> &get_ports();
		std::string get_root();
		unsigned int &get_host();

		void end_map();
		void port_host_set();
		void rootset();
		unsigned int stip(const std::string &);

		void set_error_pages(const std::string&, const std::string&);

		void print_error_pages();
	};
}
