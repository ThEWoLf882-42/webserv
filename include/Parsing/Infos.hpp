/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Infos.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:34:15 by mel-moun          #+#    #+#             */
/*   Updated: 2024/06/04 12:53:34 by agimi            ###   ########.fr       */
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
		std::map<std::string, Location> locations;
		std::vector<unsigned int> ports;
		std::string root;
		std::vector<int> duplicated;
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
		std::map<std::string, Location> &get_locations();
		std::vector<unsigned int> &get_ports();
		std::string get_root();
		unsigned int &get_host();

		void end_map();
		void port_host_set();
		void rootset();
		unsigned int stip(const std::string &);

		void set_error_pages(std::istream &);

		void print_error_pages();
		void check_duplicated(const std::vector<int> &vec, int num);

		std::map<int, std::string> &get_error_pages();
	};
}
