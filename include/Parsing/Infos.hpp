/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Infos.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:34:15 by mel-moun          #+#    #+#             */
/*   Updated: 2024/02/14 11:32:39 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <webserv.hpp>

namespace wbs
{
	class Infos
	{
	public:
		std::map<std::string, std::vector<std::string> > directives;
		std::vector<Location> locations;

		unsigned int host;
		std::vector<unsigned int> ports;

	public:
		Infos();
		Infos(const Infos &ob);
		Infos &operator=(const Infos &ob);
		~Infos();

		void print_directives();
		void end_map(std::map<std::string, std::vector<std::string> > &map);
		void port_host_set();
		unsigned int stip(const std::string &);
	};
}
