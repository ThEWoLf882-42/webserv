/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:43:53 by agimi             #+#    #+#             */
/*   Updated: 2024/01/03 17:24:54 by agimi            ###   ########.fr       */
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
#include <map>

struct respond
{
	std::string ver;
	std::string sta;
	std::string stamsg;
	std::string type;
	std::string len_str;
};

#include "Socket/SSocket.hpp"
#include "Socket/Bind.hpp"
#include "Socket/Listen.hpp"
#include "Server/Server.hpp"

void readfile(std::string &, const std::string, respond &);