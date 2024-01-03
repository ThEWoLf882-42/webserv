/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:08:13 by agimi             #+#    #+#             */
/*   Updated: 2024/01/03 17:26:16 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <webserv.hpp>

struct respond;

namespace wbs
{
	class Server
	{
	private:
		char buff[30000];
		int nsocket;
		Listen *sock;
		void accepter();
		void handler();
		void responder();
		respond r;
		std::string path;
		std::map<std::string, std::string> mime;

	public:
		Server(int, int, int, int, u_long, int);
		~Server();

		void set_sock(Listen *);
		void set_mime();
		void lanch();
		void set_res();
		Listen *get_sock();
	};
}
