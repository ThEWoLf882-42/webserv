/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:43:53 by agimi             #+#    #+#             */
/*   Updated: 2024/01/03 13:21:06 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Socket/Bind.hpp"
#include "Socket/Listen.hpp"
#include "Socket/SSocket.hpp"
#include "Server/Server.hpp"

struct respond
{
	std::string ver;
	std::string sta;
	std::string stamsg;
	std::string type;
	std::string len_str;
};
