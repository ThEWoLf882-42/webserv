/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:00:57 by mel-moun          #+#    #+#             */
/*   Updated: 2024/05/30 18:25:44 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <webserv.hpp>

namespace wbs
{
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
			
			// an7taj l env
			// binary path so aykhsni location
			// path li kiji f request
			
		public:
			CGI();
			CGI(const CGI &ob);
			CGI &operator=(const CGI &ob);
			~CGI();

			CGI(const std::string&);
			void valid_extension(const std::string&);
			void check_binary_path();
			void execution();
			void take_output();

			void execute_cgi(const std::string&);
	};
}
