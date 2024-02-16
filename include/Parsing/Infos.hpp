/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Infos.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:34:15 by mel-moun          #+#    #+#             */
/*   Updated: 2024/02/16 12:12:55 by mel-moun         ###   ########.fr       */
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


	public:
		unsigned int host;
		std::vector<unsigned int> ports;
		
		Infos();
		Infos(const Infos &);
		Infos &operator=(const Infos &);
		~Infos();

		void	set_directives(const std::string& key, const std::vector<std::string>& array);
		void	set_locations(const Location& location);
		void	print_directives();

		std::map<std::string, std::vector<std::string> >& get_directives();
		std::vector<Location>& get_locations();

		void end_map(std::map<std::string, std::vector<std::string> > &);
		void port_host_set();
		unsigned int stip(const std::string &);
	};
}
