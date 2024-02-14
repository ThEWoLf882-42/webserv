/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:08:13 by agimi             #+#    #+#             */
/*   Updated: 2024/02/14 14:28:10 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <webserv.hpp>

namespace wbs
{
	class Server
	{
	private:
		std::vector<Listen *> sock;
		std::map<std::string, std::string> mime;
		Confile c;
		respond r;
		fd_set fset;
		char buff[30000];
		int nsocket;

		// unsigned int fsize;
		// long fmax;

		void readfile(std::string &);


		Server(const Server &);
		Server &operator=(const Server &);

	public:
		Server();
		Server(const std::string &);
		~Server();

		void set_socks(std::vector<hopo> hop);

		void set_mime();
	};
}
