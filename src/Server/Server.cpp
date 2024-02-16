/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:06:51 by agimi             #+#    #+#             */
/*   Updated: 2024/02/16 10:43:43 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

wbs::Server::Server() : c(), fdmax(0)
{
	set_socks(c.get_hop());
}

wbs::Server::Server(const std::string &file) : c(file), fdmax(0)
{
	set_socks(c.get_hop());
}

wbs::Server::~Server()
{
	for (std::map<long, Listen *>::iterator it = serv.begin(); it != serv.end(); it++)
	{
		delete it->second;
		serv.erase(it);
	}
}

void wbs::Server::set_socks(std::vector<hopo> hop)
{
	Listen *l;

	FD_ZERO(&fset);
	for (std::vector<hopo>::iterator it = hop.begin(); it != hop.end(); it++)
	{
		l = new Listen(AF_INET, SOCK_STREAM, 0, it->po, it->ho, 1000);
		long fd = l->get_sfd();
		serv.insert(std::make_pair(fd, l));
		FD_SET(fd, &fset);
		if (fd > fdmax)
			fdmax = fd;
	}
	fdsize = hop.size();
}

void wbs::Server::accept(fd_set &reads, fd_set &writs)
{
	for (std::map<long, Listen *>::iterator it = serv.begin(); it != serv.end(); it++)
	{
		Listen *l = it->second;
		long fd = it->first;
		long soc;

		if (FD_ISSET(fd, &reads))
		{
			soc = ::accept(fd, NULL, NULL);
			if (soc == -1)
				std::cerr << "Could not create socket. " << strerror(errno) << std::endl;
			else
			{
				fcntl(soc, F_SETFL, O_NONBLOCK);
				l->add_req(soc);
				sockets.insert(std::make_pair(soc, l));
				FD_SET(soc, &fset);
				if (soc > fdmax)
					fdmax = soc;
			}
			break;
		}
	}
}

void wbs::Server::recv(fd_set &reads, fd_set &writs)
{
	for (std::map<long, Listen *>::iterator it = sockets.begin(); it != serv.end(); it++)
	{
		long soc = it->first;

		if (FD_ISSET(soc, &reads))
		{
			
		}
	}
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