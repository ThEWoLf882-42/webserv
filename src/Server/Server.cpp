/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:06:51 by agimi             #+#    #+#             */
/*   Updated: 2024/02/17 14:57:50 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

wbs::Server::Server() : c(), fdmax(0)
{
	set_socks(c.get_hop());
	start();
}

wbs::Server::Server(const std::string &file) : c(file), fdmax(0)
{
	set_socks(c.get_hop());
	start();
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
		l = new Listen(AF_INET, SOCK_STREAM, 0, it->po, it->ho, BLOG);
		long fd = l->get_sfd();
		FD_SET(fd, &fset);
		serv.insert(std::make_pair(fd, l));
		if (fd > fdmax)
			fdmax = fd;
	}
	fdsize = hop.size();
}

void wbs::Server::accept(fd_set &reads, int &ret)
{
	for (std::map<long, Listen *>::iterator it = serv.begin(); ret && it != serv.end(); it++)
	{
		long fd = it->first;

		if (FD_ISSET(fd, &reads))
		{
			long soc = it->second->accept();
			if (soc != -1)
			{
				FD_SET(soc, &fset);
				sockets.insert(std::make_pair(soc, it->second));
				if (soc > fdmax)
					fdmax = soc;
			}
			ret = 0;
			break;
		}
	}
}

void wbs::Server::recv(fd_set &reads, int &ret)
{

	for (std::map<long, Listen *>::iterator it = sockets.begin(); ret && it != sockets.end(); it++)
	{
		long soc = it->first;

		if (FD_ISSET(soc, &reads))
		{
			long ret = it->second->recv(soc);
			if (ret == 0)
			{
				it->second->proc(soc);
				done.push_back(soc);
			}
			else if (ret == -1)
			{
				FD_CLR(soc, &fset);
				FD_CLR(soc, &reads);
				sockets.erase(soc);
				it = sockets.begin();
			}
			ret = 0;
			break;
		}
	}
}

void wbs::Server::send(fd_set &reads, fd_set &writs, int &ret)
{
	for (std::vector<long>::iterator it = done.begin(); ret && it != done.end(); it++)
	{
		if (FD_ISSET(*it, &writs))
		{
			long ret = sockets[*it]->send(*it);

			if (ret == 0)
				done.erase(it);
			else if (ret == -1)
			{
				FD_CLR(*it, &fset);
				FD_CLR(*it, &reads);
				sockets.erase(*it);
				done.erase(it);
			}
			ret = 0;
			break;
		}
	}
}

void wbs::Server::start()
{
	while (1)
	{
		fd_set reads;
		fd_set writs;
		struct timeval tmout;
		int ret = 0;

		while (ret == 0)
		{
			tmout.tv_sec = 1;
			tmout.tv_usec = 0;

			memcpy(&reads, &fset, sizeof(fset));
			FD_ZERO(&writs);
			for (std::vector<long>::iterator it = done.begin(); it != done.end(); it++)
				FD_SET(*it, &writs);

			ret = select(fdmax + 1, &reads, &writs, NULL, &tmout);
		}
		if (ret > 0)
		{
			send(reads, writs, ret);
			recv(reads, ret);
			accept(reads, ret);
		}
		else
		{
			closesockets();
			resetfd();
		}
	}
}

void wbs::Server::closesockets()
{
	for (std::map<long, Listen *>::iterator it = sockets.begin(); it != sockets.end(); it++)
		it->second->close(it->first);
	sockets.clear();
	done.clear();
}

void wbs::Server::resetfd()
{
	FD_ZERO(&fset);
	for (std::map<long, Listen *>::iterator it = serv.begin(); it != serv.end(); it++)
		FD_SET(it->first, &fset);
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