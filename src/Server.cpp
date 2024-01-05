/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:06:51 by agimi             #+#    #+#             */
/*   Updated: 2024/01/05 11:02:08 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

int wbs::Server::sig = 1;

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
	// int flags = fcntl(nsocket, F_GETFL, 0);
	// fcntl(nsocket, F_SETFL, flags | O_NONBLOCK);
	recv(nsocket, buff, 30000, 0);
	std::cout << "======REQ=====\n"
			  << buff << "======REQ END=====" << std::endl;
}

void wbs::Server::handler()
{
	std::stringstream ss(buff);

	std::memset(buff, '\0', sizeof(buff));
	ss >> path >> path;
	path == "/" ? path = "/index.html" : path;
}

void wbs::Server::set_res()
{
	r.ver = "HTTP/1.1 ";
	r.sta = "200 ";
	r.stamsg = "OK\r\n";
	r.len_str = "Content-Length: ";

	if (path.find('.') != std::string::npos)
		ftype = path.substr(path.find('.'), path.size());
	else
		ftype = ".text";
	if (mime.find(ftype) != mime.end())
		r.type = "content-type: " + mime.find(ftype)->second;
	else
		r.type = "content-type: " + mime.find(".text")->second;
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

	readfile(bo);

	h += r.ver + r.sta + r.stamsg + r.type + "\r\n\r\n";
	send(nsocket, h.c_str(), h.size(), 0);
	send(nsocket, bo.c_str(), bo.size(), 0);
	close(nsocket);
}

void wbs::Server::lanch()
{
	set_mime();
	while (sig == 1)
	{
		accepter();
		handler();
		responder();
	}
}

void wbs::Server::readfile(std::string &bo)
{
	std::ifstream file("." + path);
	std::stringstream buf;

	if (!file.is_open())
	{
		r.sta = "404 ";
		r.stamsg = "Not Found ";
		r.type = "";
		path = "/404.html";
		readfile(bo);
		return;
	}

	buf << file.rdbuf();
	bo = buf.str();

	file.close();
}