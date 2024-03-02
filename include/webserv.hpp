/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:43:53 by agimi             #+#    #+#             */
/*   Updated: 2024/03/02 16:05:06 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdint.h>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <istream>
#include <algorithm>
#include <map>
#include <vector>
#include <sys/select.h>
#include <csignal>
#include <fcntl.h>
#include <cstring>
#include <dirent.h>

#define DEF_CONF "./config/default.conf"
#define RSIZE 4096
#define BLOG 1000
#define OUTREQ 1
#define OUTRES 0

namespace wbs
{
	class Infos;
	class Listen;
}

struct hopo
{
	wbs::Infos *inf;
	unsigned int ho;
	unsigned int po;
};

struct respond
{
	std::string ver;
	std::string sta;
	std::string stamsg;
	std::string type;
	std::string len_str;
};

#include "Parsing/Location.hpp"
#include "Parsing/Infos.hpp"
#include "Parsing/Confile.hpp"
#include "CGI/CGI.hpp"
#include "Request/Request.hpp"
#include "Socket/SSocket.hpp"
#include "Socket/Bind.hpp"
#include "Socket/Listen.hpp"
#include "Server/Server.hpp"
#include "Response/Response.hpp"

int checkEnd(const std::string &, const std::string &);
void cleankey(std::string &);
void cleanval(std::string &);
std::string readfile(std::string);
std::map<std::string, std::string> set_mime();
std::string get_mime(const std::string &pat);