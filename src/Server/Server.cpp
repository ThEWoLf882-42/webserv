/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:06:51 by agimi             #+#    #+#             */
/*   Updated: 2024/02/13 16:34:30 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>
/*
int wbs::Server::sig = 1;

wbs::Server::Server() : c()
{
	// set_sock(new Listen(d, s, pro, por, i, b));
	FD_ZERO(&fset);
	FD_SET(sock->get_sfd(), &fset);
	lanch();
}

wbs::Server::Server(std::string file) : c(file)
{
	// set_sock(new Listen(d, s, pro, por, i, b));
	FD_ZERO(&fset);
	FD_SET(sock->get_sfd(), &fset);
	lanch();
}

wbs::Server::~Server()
{
	// if (sock)
	// 	delete sock;
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

void wbs::Server::set200()
{
	r.ver = "HTTP/1.1 ";
	r.sta = "200 ";
	r.stamsg = "OK\r\n";
}

void wbs::Server::set400()
{
	r.sta = "404 ";
	r.stamsg = "Not Found\r\n";
	r.type = "content-type: text/html";
}

void wbs::Server::set500()
{
	r.sta = "500 ";
	r.stamsg = "Internal Server Error\r\n";
	r.type = "content-type: text/html";
}

void wbs::Server::accepter()
{
	sockaddr_in add = sock->get_add();
	int addl = sizeof(add);
	nsocket = accept(sock->get_sfd(), (sockaddr *)&add, (socklen_t *)&addl);
	// nonblock();
	fcntl(nsocket, F_SETFL, O_NONBLOCK, FD_CLOEXEC);
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
	set200();

	if (path.find_last_of('.') != std::string::npos)
		ftype = path.substr(path.find_last_of('.'), path.size());
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
	std::ifstream file("./config/mime");
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

	h += r.ver + r.sta + r.stamsg + r.type + "\r\n\r\n" + bo;
	send(nsocket, h.c_str(), h.size(), 0);
	bo.clear();
	close(nsocket);
}

void wbs::Server::lanch()
{
	fd_set tfset;

	set_mime();
	while (sig == 1)	
	{
		tfset = fset;
		// sock->c_test(select(FD_SETSIZE, &tfset, NULL, NULL, NULL));
		accepter();
		handler();
		responder();
	}
}

void wbs::Server::readfile(std::string &bo)
{
	std::ifstream file("." + path, std::ios::binary);

	if (!file.is_open())
	{
		set400();
		path = "/404.html";
		readfile(bo);
		return;
	}

	try
	{
		file.seekg(0, std::ios::end);
		std::streampos fileSize = file.tellg();
		file.seekg(0, std::ios::beg);

		bo.reserve(fileSize);

		const size_t bufferSize = 1024 * 64;
		std::vector<char> buffer(bufferSize);

		while (!file.eof())
		{
			file.read(buffer.data(), bufferSize);
			bo.append(buffer.data(), file.gcount());
		}
	}
	catch (const std::exception &e)
	{
		set500();
		return;
	}
}

void wbs::Server::nonblock()
{
	int o;

	o = fcntl(nsocket, F_GETFL);
	sock->c_test(o);
	o = (o | O_NONBLOCK);
	sock->c_test(fcntl(nsocket, F_SETFL, o));
}*/