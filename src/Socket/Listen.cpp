/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Listen.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:35:32 by agimi             #+#    #+#             */
/*   Updated: 2024/02/16 11:38:20 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

wbs::Listen::Listen(int d, int s, int pro, int por, unsigned int i, int b) : Bind(d, s, pro, por, i), blog(b)
{
	listning();
	c_test(list);
}

wbs::Listen::~Listen()
{
	::close(list);
}

void wbs::Listen::listning()
{
	list = listen(get_sfd(), blog);
}

void wbs::Listen::add_req(long soc)
{
	reqs.insert(std::make_pair(soc, ""));
}

void wbs::Listen::close(long soc)
{
	if (soc > 0)
		::close(soc);
	reqs.erase(soc);
}

int wbs::Listen::recv(long soc)
{
	char buffer[RSIZE] = {0};
	int ret = ::recv(soc, buffer, RSIZE - 1, 0);

	if (ret == 0 || ret == -1)
	{
		close(soc);
		if (!ret)
			std::cout << "\rConnection was closed by client.\n"
					  << std::endl;
		else
			std::cout << "\rRead error, closing connection.\n"
					  << std::endl;
		return -1;
	}

	reqs[soc].append(buffer, ret);

	size_t i = reqs[soc].find("\r\n\r\n");
	if (i != std::string::npos)
	{
		if (reqs[soc].find("Content-Length: ") == std::string::npos)
		{
			if (reqs[soc].find("Transfer-Encoding: chunked") != std::string::npos)
				return checkEnd(reqs[soc], "0\r\n\r\n");
			else
				return 0;
		}

		size_t pos = reqs[soc].find("Content-Length: ") + 16;
		size_t len = std::atoi(reqs[soc].substr(pos, 10).c_str());
		return reqs[soc].size() >= len + i + 4 ? 0 : 1;
	}

	return 1;
}

int wbs::Listen::send(long soc)
{
	
}