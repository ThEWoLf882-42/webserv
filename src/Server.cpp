/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:06:51 by agimi             #+#    #+#             */
/*   Updated: 2024/01/03 21:26:55 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

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
	std::stringstream ss(buff);

	ss >> path >> path;
	std::cout << buff << std::endl;
	path == "/" ? path = "/index.html" : path;
}

void wbs::Server::set_res()
{
	r.ver = "HTTP/1.1 ";
	r.sta = "200 ";
	r.stamsg = "OK\r\n";
	r.len_str = "Content-Length: ";
}

void wbs::Server::set_mime()
{
	std::string dot;
	std::string type;
	std::ifstream file("./mime");
	if (!file.is_open())
	{
		std::cerr << "mime are zooooot" << std::endl;
		return;
	}
	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream s(line);

		s >> type >> dot;
		mime.insert(std::pair<std::string, std::string>(dot, type));
	}
}

void wbs::Server::responder()
{
	set_res();
	std::string bo;
	std::string h;

	readfile(bo, path, r);

	if (path.find('.') != std::string::npos)
		ftype = path.substr(path.find('.'), path.size());
	else
		ftype = ".text";
	r.type = "content-type: " + mime.find(ftype)->second;
	h += r.ver + r.sta + r.stamsg + r.type + "\r\n\r\n" + bo;
	send(nsocket, h.c_str(), h.size(), 0);
	close(nsocket);
}

void wbs::Server::lanch()
{
	set_mime();
	while (1)
	{
		std::cout << "==== Started ====" << std::endl;
		accepter();
		handler();
		responder();
		std::cout << "==== DONE ====" << std::endl;
	}
}