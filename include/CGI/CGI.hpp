/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:00:57 by mel-moun          #+#    #+#             */
/*   Updated: 2024/06/09 11:57:49 by mel-moun         ###   ########.fr       */
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
			wbs::Response&	_response;
			std::string		_path;
			std::string		_binary_path;
			std::string		content;
			int				pid;
			int				std_out;
			int 			std_in;

			CGI(const CGI &ob);
			CGI &operator=(const CGI &ob);

		public:
			CGI(Response&);
			~CGI();

			void		valid_extension();
			void		binary_path();
			void		execution();
			void		take_output();
			void		execute_cgi();
			void		setup_files();
			std::string	&get_content();
	};
}
