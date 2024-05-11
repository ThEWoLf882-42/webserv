/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:15:55 by mel-moun          #+#    #+#             */
/*   Updated: 2024/05/10 18:26:55 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <webserv.hpp>

namespace wbs
{
	class Location
	{
	private:
		std::map<std::string, std::vector<std::string> > params;
		std::string path;
		std::string root;

	public:
		Location();
		Location(const Location &);
		Location &operator=(const Location &);
		~Location();

		void insert(const std::pair<std::string, std::vector<std::string> > &);
		void set_path(const std::string &);
		std::string get_path() const;
		std::string get_root() const;
		std::map<std::string, std::vector<std::string> > &get_params();

		void end_map_location();
		void rootset();
	};
}