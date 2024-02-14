/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:15:55 by mel-moun          #+#    #+#             */
/*   Updated: 2024/02/14 11:56:28 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <webserv.hpp>

namespace wbs
{
	class Location
	{
	public:
		std::string path;
		std::map<std::string, std::vector<std::string> > params;

	public:
		Location();
		Location(const Location &);
		Location &operator=(const Location &);
		~Location();

		void end_map_location(std::map<std::string, std::vector<std::string> > &);
	};
}