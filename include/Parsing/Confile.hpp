/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Confile.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:35:14 by mel-moun          #+#    #+#             */
/*   Updated: 2024/05/02 16:47:52 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <webserv.hpp>

namespace wbs
{
	class Confile
	{
	private:
		std::vector<Infos> servers;
		std::vector<hopo> hop;

		std::ifstream infile;
		std::string input;
	
	public:
		Confile();
		Confile(const std::string &);
		Confile &operator=(const Confile &);
		Confile(const Confile &);
		~Confile();

		std::vector<hopo> get_hop();

		// Main parsing
		void parsing();

		// Main parsing' functions
		void closed_brackets();

		// Parse
		void parse();
		void syntax_error();

		const std::string take_path(const std::string &, const std::string &);
		void check_semicolon();
		void count_semicolons(const std::string &, int);

		void the_list();
		void	key_duplicated(std::vector<std::string>&, const std::string&);
		void	key_invalid(const std::string&);
	};
}
