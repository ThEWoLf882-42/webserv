/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responce.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:21:15 by fbelahse          #+#    #+#             */
/*   Updated: 2024/04/29 13:21:50 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

wbs::Response::Response() : ver(1.1),
							code(200),
							stat("OK"),
							con_len(0),
							tst("application/html"),
							meth("GET"),
							url_tst("/Users/fbelahse/Desktop/webserv/src/Response/aaa.html"),
							con_ty(NULL)
{
}

wbs::Response::~Response()
{
}

void wbs::Response::get_cont_ty()
{
	std::string ext;
	std::string url_tst("/Users/fbelahse/Desktop/webserv/src/Response/aaa.html");
	std::string token;
	std::string delim = "/";
	size_t pos;
	while ((pos != url_tst.find(delim)) != std::string::npos)
	{
		token = url_tst.substr(0, pos);
		url_tst.erase(0, pos + delim.length());
	}
}

void wbs::Response::count_size()
{
	std::string line;
	if (tst == "application/html")
	{
		std::ifstream file("aaa.html");
		if (file.is_open())
		{
			while (std::getline(file, line))
			{
				con_len += line.size();
			}
		}
	}
}

void wbs::Response::GetResp()
{
	count_size();
}

std::string wbs::Response::GenRes()
{
	if (meth == "GET")
	{
		GetResp();
	}
}
