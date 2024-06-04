/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:00:57 by mel-moun          #+#    #+#             */
/*   Updated: 2024/06/04 13:37:01 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <webserv.hpp>

namespace wbs
{
	class Response;
	
	class CGI
	{
		private:
			std::string	_path;
			std::string	_binary_path;
		
			int pid;
			const char* args[3];
			// char **env;
			int r;
			char c;
			std::string content;
			// int ext;
			
			// an7taj l env, yesu
			// binary path so aykhsni location
			// path li kiji f request
			
			wbs::Response& _response;

			int	std_out;
			int std_in;

		public:
			// CGI();
			CGI(const CGI &ob);
			CGI &operator=(const CGI &ob);
			~CGI();

			void valid_extension();
			void binary_path();
			void execution();
			void take_output();

			void	execute_cgi();
			
			CGI(Response&);

			void	setup_files();

			std::string &get_content();
	};
}

//check duplicate location's path
