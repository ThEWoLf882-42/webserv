/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Listen.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:35:32 by agimi             #+#    #+#             */
/*   Updated: 2024/05/10 17:13:57 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

wbs::Listen::Listen(int d, int s, int pro, int por, unsigned int i, int b, Infos &inf) : Bind(d, s, pro, por, i), inf(inf), blog(b)
{
	listning();
	c_test(list);
}

wbs::Listen::~Listen()
{
	::close(list);
}

wbs::Infos &wbs::Listen::get_inf()
{
	return inf;
}

void wbs::Listen::listning()
{
	list = listen(get_sfd(), blog);
}

void wbs::Listen::close(long soc)
{
	if (soc > 0)
		::close(soc);
	reqs.erase(soc);
}

long wbs::Listen::accept()
{
	long soc;
	int fd = get_sfd();

	soc = ::accept(fd, NULL, NULL);
	if (soc == -1)
		std::cerr << "Could not create socket. " << strerror(errno) << std::endl;
	else
	{
		fcntl(soc, F_SETFL, O_NONBLOCK);
		reqs.insert(std::make_pair(soc, ""));
	}
	return soc;
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
	static std::map<long, size_t> sen;

	if (sen.find(soc) == sen.end())
		sen[soc] = 0;

	if (OUTRES && sen[soc] == 0)
	{
		std::string response = reqs[soc].size() < 1000 ? reqs[soc] : reqs[soc].substr(0, 1000) + "..." + reqs[soc].substr(reqs[soc].size() - 10, 15);
		std::cout << "\rResponse :                \n[" << response << "]\n"
				  << std::endl;
	}

	size_t rem = reqs[soc].size() - sen[soc];
	size_t sen_size = std::min(static_cast<size_t>(RSIZE), rem);
	int ret = ::send(soc, reqs[soc].c_str() + sen[soc], sen_size, 0);

	if (ret == -1)
	{
		close(soc);
		sen[soc] = 0;
		return -1;
	}
	else
	{
		sen[soc] += ret;
		if (sen[soc] >= reqs[soc].size())
		{
			reqs.erase(soc);
			sen[soc] = 0;
			return 0;
		}
		else
			return 1;
	}
}

void wbs::Listen::proc(long soc)
{
	if (reqs[soc] != "")
	{
		Request r(*this, reqs[soc]);
		std::string str = "HTTP/1.1 200 OK\r\nContent-Type: ";
		str += get_mime(r.get_loc()) + "\r\nContent-Length: ";
		std::string body = readfile(r.get_loc());
		std::stringstream s;

		s << body.size();
		std::string size = s.str();
		str += size + "\r\n\r\n";
		str += body;

		if (OUTREQ)
		{
			std::string req = reqs[soc].size() < 1000 ? reqs[soc] : reqs[soc].substr(0, 1000) + "..." + reqs[soc].substr(reqs[soc].size() - 10, 15);
			std::cout << "\nRequest :" << std::endl
					  << "[" << req << "]" << std::endl;
		}
		reqs.erase(soc);
		reqs.insert(std::make_pair(soc, str));
	}
}