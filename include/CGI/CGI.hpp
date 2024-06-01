/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:00:57 by mel-moun          #+#    #+#             */
/*   Updated: 2024/06/01 10:13:40 by mel-moun         ###   ########.fr       */
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
			std::string	binary_path;
			int fd[2];
			int pid;
			const char **args;
			char **env;
			int r;
			char c;
			std::string content;
			int ext;
			
			// an7taj l env, yesu
			// binary path so aykhsni location
			// path li kiji f request
			
			wbs::Response& _response;

		public:
			// CGI();
			CGI(const CGI &ob);
			CGI &operator=(const CGI &ob);
			~CGI();

			CGI(const std::string&);
			void valid_extension(const std::string&);
			void check_binary_path();
			void execution();
			void take_output();

			void execute_cgi(const std::string&);
			void	default_binary_path();
			CGI(Response&);
	};
}

//check duplicate location's path
