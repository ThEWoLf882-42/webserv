/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:06:51 by agimi             #+#    #+#             */
/*   Updated: 2024/01/03 16:56:57 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

//(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10)

wbs::Server::Server(int d, int s, int pro, int por, u_long i, int b) : sock(NULL)
{
	set_sock(new Listen(d, s, pro, por, i, b));
	lanch();
}

wbs::Server::~Server()
{
	if (sock)
		delete sock;
}

void wbs::Server::set_sock(Listen *so)
{
	if (sock)
		delete sock;
	sock = so;
}

wbs::Listen *wbs::Server::get_sock()
{
	return sock;
}

void wbs::Server::accepter()
{
	sockaddr_in add = sock->get_add();
	int addl = sizeof(add);
	nsocket = accept(sock->get_sfd(), (sockaddr *)&add, (socklen_t *)&addl);
	recv(nsocket, buff, 30000, 0);
}

void wbs::Server::handler()
{
	std::stringstream	ss(buff);

	ss >> path >> path;
	std::cout << buff << std::endl;
	path == "/" ? path = "./index.html" : path = "." + path;
}

void wbs::Server::responder()
{
	r.ver = "HTTP/1.1 ";
	r.sta = "200 ";
	r.stamsg = "OK\n";
	// r.type = "Content-Type: text/plain\n";
	// r.type = "";
	r.len_str = "Content-Length: ";

	std::string bo;
	std::string h;

	// path == "./favicon.ico" ? r.type = "Content-Type: image/png\n" : r.type = "Content-Type: text/html\n";;
	bo.clear();
	readfile(bo, path, r);
	h += r.ver + r.sta + r.stamsg + r.type + "\n\n" + bo;

	write(nsocket, h.c_str(), h.size());
	close(nsocket);
}

void wbs::Server::lanch()
{
	while (1)
	{
		std::cout << "==== Started ====" << std::endl;
		accepter();
		handler();
		responder();
		std::cout << "==== DONE ====" << std::endl;
	}
}