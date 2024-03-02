/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:08:13 by agimi             #+#    #+#             */
/*   Updated: 2024/02/22 15:50:41 by agimi            ###   ########.fr       */
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
		std::vector<long> done;
		Confile c;

		fd_set fset;
		unsigned int fdsize;
		long fdmax;

		Server(const Server &);
		Server &operator=(const Server &);

	public:
		static const std::map<std::string, std::string> mime;
		Server();
		Server(const std::string &);
		~Server();

		void set_socks(std::vector<hopo>);
		void accept(fd_set &, int &);
		void recv(fd_set &, int &);
		void send(fd_set &, fd_set &, int &);
		void start();
		void closesockets();
		void resetfd();
	};
}
