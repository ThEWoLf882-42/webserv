/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:22:07 by agimi             #+#    #+#             */
/*   Updated: 2024/04/29 13:04:38 by agimi            ###   ########.fr       */
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
		codemsg = e.what();
		std::cerr << e.what() << std::endl;
	}
	set_body(req);
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
		body = r.body;
		code = r.code;
		mloc = r.mloc;
		heads = r.heads;
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

void wbs::Request::set_body(const std::string &req)
{
	size_t pos = req.find("\r\n\r\n") + 4;

	body = req.substr(pos, req.size() - pos);
}

void wbs::Request::checkmeth()
{
	std::array<std::string, 3> alme = {{"GET", "POST", "DELETE"}};

	if (std::find(alme.begin(), alme.end(), meth) == alme.end())
	{
		code = 501;
		throw std::runtime_error("501 Not Implemented");
	}
}

void wbs::Request::checkloc()
{
	std::string ro = serv.get_inf().get_root();
	std::vector<Location> &locs = serv.get_inf().get_locations();

	if (loc == "/")
		loc = ro;
	else
	{
		std::vector<Location>::iterator it;
		for (it = locs.begin(); it != locs.end(); it++)
		{
			std::string lro = it->get_root() == "" ? it->get_path() : it->get_root();
			size_t pos = loc.find(it->get_path());
			if (pos != std::string::npos)
			{
				loc.replace(pos, lro.size(), lro);
				mloc = *it;
				if (it->get_params().find("return") != it->get_params().end())
				{
					code = 301;
					throw std::runtime_error("301 " + *++(it->get_params().find("return")->second.begin()));
				}
				break;
			}
		}
		if (it == locs.end())
		{
			size_t pos = loc.find('/');
			if (pos != std::string::npos)
				loc.replace(pos, 1, ro + "/");
		}
	}

	// std::cout << "loc: " << loc << std::endl;

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

wbs::Location &wbs::Request::get_mloc()
{
	return mloc;
}

std::string wbs::Request::get_meth()
{
	return meth;
}

std::string wbs::Request::get_loc()
{
	return loc;
}

std::string wbs::Request::get_ver()
{
	return ver;
}

std::string wbs::Request::get_body()
{
	return body;
}

std::string wbs::Request::get_codemsg()
{
	return codemsg;
}

int wbs::Request::get_code()
{
	return code;
}