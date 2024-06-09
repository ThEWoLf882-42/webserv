/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Confile.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:35:14 by mel-moun          #+#    #+#             */
/*   Updated: 2024/06/09 11:53:35 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <webserv.hpp>

namespace wbs
{
	class Confile
	{
	private:
		std::vector<Infos> 	servers;
		std::vector<hopo> 	hop;
		std::ifstream		infile;
		std::string			input;
	
		Confile &operator=(const Confile &);
		Confile(const Confile &);

	public:
		Confile();
		Confile(const std::string &);
		~Confile();

		void	parsing();
		void	closed_brackets();
		void	parse();
		void	syntax_error();
		const std::string take_path(const std::string &, const std::string &);
		void	check_semicolon();
		void	count_semicolons(const std::string &, int);
		void	the_list();
		void	key_duplicated(std::vector<std::string>&, const std::string&);
		void	key_invalid(const std::string&);
		void	directives_arguments(const std::vector<std::string>& value);
		void	check_locations(std::vector<std::string>& locs_path, const std::string& path);
		void	check_return(std::map<std::string, std::vector<std::string> >&);
		void	check_cgi_extension(const std::string& str, std::vector<std::string>& values);
		std::vector<hopo> get_hop();
	};
}
