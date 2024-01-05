/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:08:13 by agimi             #+#    #+#             */
/*   Updated: 2024/01/05 09:19:30 by agimi            ###   ########.fr       */
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
		std::string path;
		std::string ftype;
		std::map<std::string, std::string> mime;

		void accepter();
		void handler();
		void responder();
		void readfile(std::string &bo);

	public:
		Server(int, int, int, int, u_long, int);
		~Server();

		static int sig;

		void set_sock(Listen *);
		void set_mime();
		void lanch();
		void set_res();
		Listen *get_sock();
	};
}
