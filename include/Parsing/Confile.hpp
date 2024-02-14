/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Confile.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:35:14 by mel-moun          #+#    #+#             */
/*   Updated: 2024/02/14 11:56:14 by agimi            ###   ########.fr       */
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

		std::ifstream infile;
		std::string input;

	public:
		Confile();
		Confile(const std::string &);
		Confile &operator=(const Confile &);
		Confile(const Confile &);
		~Confile();

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
	};
}
