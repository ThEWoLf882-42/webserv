/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:08:13 by agimi             #+#    #+#             */
/*   Updated: 2024/01/03 15:20:44 by agimi            ###   ########.fr       */
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
		char	buff[30000];
		int		nsocket;
		Listen *sock;
		void accepter();
		void handler();
		void responder();
		respond r;
		std::string	path;
	public:
		Server(int, int, int, int, u_long, int);
		~Server();

		void set_sock(Listen *);
		void lanch();
		Listen	*get_sock();
	};

} // namespace wbs
