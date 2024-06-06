/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:00:57 by mel-moun          #+#    #+#             */
/*   Updated: 2024/06/05 13:08:35 by agimi            ###   ########.fr       */
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
			std::string content;
			wbs::Response& _response;

			int	std_out;
			int std_in;

		public:
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
