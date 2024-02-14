/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:06:51 by agimi             #+#    #+#             */
/*   Updated: 2024/02/14 14:15:42 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

wbs::Server::Server() : c()
{
	set_socks(c.get_hop());
}

wbs::Server::Server(const std::string &file) : c(file)
{
	set_socks(c.get_hop());
}

wbs::Server::~Server()
{
	// for (std::vector<Listen *>::iterator it = sock.begin(); it != sock.end(); it++)
	// 	delete it;
		
}

void	wbs::Server::set_socks(std::vector<hopo> hop)
{
	for (std::vector<hopo>::iterator it = hop.begin(); it != hop.end(); it++)
		sock.push_back(new Listen(AF_INET, SOCK_STREAM, 0, it->po, it->ho, 10));
}

// void wbs::Server::accepter()
// {
// 	sockaddr_in add = sock->get_add();
// 	int addl = sizeof(add);
// 	nsocket = accept(sock->get_sfd(), (sockaddr *)&add, (socklen_t *)&addl);
// 	// nonblock();
// 	fcntl(nsocket, F_SETFL, O_NONBLOCK, FD_CLOEXEC);
// 	recv(nsocket, buff, 30000, 0);
// 	std::cout << "======REQ=====\n"
// 			  << buff << "======REQ END=====" << std::endl;
// }

// void wbs::Server::handler()
// {
// 	std::stringstream ss(buff);

// 	std::memset(buff, '\0', sizeof(buff));
// 	ss >> path >> path;
// 	path == "/" ? path = "/index.html" : path;
// }

// void wbs::Server::set_mime()
// {
// 	std::string dot;
// 	std::string type;
// 	std::ifstream file("./config/mime");
// 	if (!file.is_open())
// 	{
// 		std::cerr << "mime are zooooot" << std::endl;
// 		return;
// 	}
// 	std::string line;
// 	while (std::getline(file, line))
// 	{
// 		std::stringstream s(line);

// 		s >> type >> dot;
// 		mime.insert(std::pair<std::string, std::string>(dot, type));
// 	}
// }

// void wbs::Server::responder()
// {
// 	set_res();

// 	std::string bo;
// 	std::string h;

// 	readfile(bo);

// 	h += r.ver + r.sta + r.stamsg + r.type + "\r\n\r\n" + bo;
// 	send(nsocket, h.c_str(), h.size(), 0);
// 	bo.clear();
// 	close(nsocket);
// }

// void wbs::Server::lanch()
// {
// 	fd_set tfset;

// 	set_mime();
// 	while (sig == 1)
// 	{
// 		tfset = fset;
// 		// sock->c_test(select(FD_SETSIZE, &tfset, NULL, NULL, NULL));
// 		accepter();
// 		handler();
// 		responder();
// 	}
// }

// void wbs::Server::readfile(std::string &bo)
// {
// 	std::ifstream file("." + path, std::ios::binary);

// 	if (!file.is_open())
// 	{
// 		set400();
// 		path = "/404.html";
// 		readfile(bo);
// 		return;
// 	}

// 	try
// 	{
// 		file.seekg(0, std::ios::end);
// 		std::streampos fileSize = file.tellg();
// 		file.seekg(0, std::ios::beg);

// 		bo.reserve(fileSize);

// 		const size_t bufferSize = 1024 * 64;
// 		std::vector<char> buffer(bufferSize);

// 		while (!file.eof())
// 		{
// 			file.read(buffer.data(), bufferSize);
// 			bo.append(buffer.data(), file.gcount());
// 		}
// 	}
// 	catch (const std::exception &e)
// 	{
// 		set500();
// 		return;
// 	}
// }

// void wbs::Server::nonblock()
// {
// 	int o;

// 	o = fcntl(nsocket, F_GETFL);
// 	sock->c_test(o);
// 	o = (o | O_NONBLOCK);
// 	sock->c_test(fcntl(nsocket, F_SETFL, o));
// }