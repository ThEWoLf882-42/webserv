/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:08:13 by agimi             #+#    #+#             */
/*   Updated: 2024/02/16 11:19:59 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <webserv.hpp>

namespace wbs
{
	class Server
	{
	private:
		std::map<long, Listen *> serv;
		std::map<long, Listen *> sockets;
		std::map<std::string, std::string> mime;
		std::vector<long> done;
		Confile c;

		fd_set fset;

		unsigned int fdsize;
		long fdmax;

		Server(const Server &);
		Server &operator=(const Server &);

	public:
		Server();
		Server(const std::string &);
		~Server();

		void set_socks(std::vector<hopo> hop);
		void accept(fd_set &, fd_set &);
		void recv(fd_set &, fd_set &);

		void set_mime();
	};
}
