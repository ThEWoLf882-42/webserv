/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:08:13 by agimi             #+#    #+#             */
/*   Updated: 2024/02/12 10:33:25 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <webserv.hpp>

namespace wbs
{
	class Server
	{
	private:
		char buff[30000];
		int nsocket;
		Listen *sock;
		respond r;

		fd_set fset;
		// unsigned int fsize;
		// long fmax;

		std::string path;
		std::string ftype;
		std::map<std::string, std::string> mime;

		void accepter();
		void handler();
		void responder();
		void readfile(std::string &bo);
		void nonblock();

	public:
		Server(int, int, int, int, u_long, int);
		~Server();

		static int sig;

		void set_sock(Listen *);
		void set_mime();
		void lanch();
		void set_res();
		void set200();
		void set400();
		void set500();
		Listen *get_sock();
	};
}
