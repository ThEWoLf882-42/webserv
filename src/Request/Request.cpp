/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:22:07 by agimi             #+#    #+#             */
/*   Updated: 2024/02/21 14:31:13 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

wbs::Request::Request(Listen &s, const std::string &req) : serv(s), code(200)
{
	std::stringstream ss(req);
	std::string line;

	std::getline(ss, line);
	std::stringstream fir(line);
	fir >> meth >> loc >> ver;

	set_heads(ss, line);
	try
	{
		checkmeth();
		checkloc();
		checkver();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}

wbs::Request::Request(const Request &r) : serv(r.serv)
{
	*this = r;
}

wbs::Request &wbs::Request::operator=(const Request &r)
{
	if (this != &r)
	{
		meth = r.meth;
		loc = r.loc;
		ver = r.ver;
	}
	return *this;
}

wbs::Request::~Request()
{
}

void wbs::Request::set_heads(std::stringstream &ss, std::string &line)
{
	while (std::getline(ss, line))
	{
		if (line == "\r")
			break;
		std::stringstream sln(line);
		std::string key;
		std::string val;

		sln >> key;
		val = line.substr(key.size() + 1);
		cleankey(key);
		cleanval(val);

		heads.insert(std::make_pair(key, val));
	}
}

void wbs::Request::checkmeth()
{
	std::string alme[] = {"GET", "POST", "DELETE"};
	size_t i = 0;
	for (; i < sizeof(alme) / sizeof(alme[0]); i++)
	{
		if (alme[i] == meth)
			break;
	}
	if (i == sizeof(alme) / sizeof(alme[0]))
	{
		code = 501;
		throw std::runtime_error("501 Not Implemented");
	}
}

void wbs::Request::checkloc()
{
	std::string ro = serv.get_inf().get_root();
	std::vector<Location> locs = serv.get_inf().get_locations();

	if (loc == "/")
		loc = ro;
	else
	{
		size_t pos = loc.find('/');
		if (pos != std::string::npos)
			loc.replace(pos, 1, ro + "/");
	}

	for (std::vector<Location>::iterator it = locs.begin(); it != locs.end(); it++)
	{
		std::string lro = it->get_root() == "" ? it->get_path() : it->get_root();
		size_t pos = loc.find(it->get_path());
		if (pos != std::string::npos)
		{
			loc.replace(pos, lro.size(), lro);
			break;
		}
	}

	if (!opendir(loc.c_str()))
	{
		if (access(loc.c_str(), F_OK) == -1)
		{
			code = 404;
			throw std::runtime_error("404 Not Found");
		}
	}
}

void wbs::Request::checkver()
{
	if (ver != "HTTP/1.1" && ver != "HTTP/1.0")
	{
		code = 505;
		throw std::runtime_error("505 HTTP Version Not Supported");
	}
}
