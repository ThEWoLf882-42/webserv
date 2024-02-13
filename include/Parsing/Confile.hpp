/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Confile.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:35:14 by mel-moun          #+#    #+#             */
/*   Updated: 2024/02/13 17:42:45 by agimi            ###   ########.fr       */
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
		Confile(const std::string &file);
		Confile &operator=(const Confile &ob);
		Confile(const Confile &ob);
		~Confile();

		// Main parsing
		void parsing();

		// Main parsing' functions
		void closed_brackets();

		// Parse
		void parse();
		void syntax_error();

		const std::string take_path(const std::string &input, const std::string &key);
		void check_semicolon();
		void count_semicolons(const std::string &str, int i);
	};
}
