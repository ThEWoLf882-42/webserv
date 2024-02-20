/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:43:53 by agimi             #+#    #+#             */
/*   Updated: 2024/02/20 11:02:16 by mel-moun         ###   ########.fr       */
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

#define DEF_CONF "./config/default.conf"
#define RSIZE 4096
#define BLOG 1000
#define OUTREQ 1
#define OUTRES 0

struct hopo
{
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
#include "Socket/SSocket.hpp"
#include "Socket/Bind.hpp"
#include "Socket/Listen.hpp"
#include "Server/Server.hpp"

int checkEnd(const std::string&, const std::string&);
