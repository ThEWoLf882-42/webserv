/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:22:07 by agimi             #+#    #+#             */
/*   Updated: 2024/06/04 11:46:12 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

wbs::Request::Request(Listen &s, const std::string &req) : serv(s), mloc(NULL), inf(serv.get_inf()), code(200)
{
	std::stringstream ss(req);
	std::string line;

	std::getline(ss, line);
	std::stringstream fir(line);
	fir >> meth >> loc >> ver;

	oloc = loc;
	set_heads(ss, line);
	try
	{
		checkencoding();
		checkbodysize();
		checkmeth();
		checkloc();
		checkver();
		set_body(req);
		chunked();
	}
	catch (const std::exception &e)
	{
		codemsg = e.what();
	}
}

wbs::Request::Request(const Request &r) : serv(r.serv), inf(serv.get_inf())
{
	*this = r;
}

wbs::Request &wbs::Request::operator=(const Request &r)
{
	if (this != &r)
	{
		meth = r.meth;
		loc = r.loc;
		oloc = r.oloc;
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

void wbs::Request::checkencoding()
{
	if (heads.find("Transfer-Encoding") != heads.end() && heads.find("Transfer-Encoding")->second != "chunked")
	{
		code = 501;
		throw std::runtime_error(" Not Implemented");
	}
	if (heads.find("Transfer-Encoding") == heads.end() && heads.find("Content-Length") == heads.end() && meth == "POST")
	{
		code = 400;
		throw std::runtime_error(" Bad Request");
	}
	if (!AllowedChars(loc))
	{
		code = 400;
		throw std::runtime_error(" Bad Request");
	}
	if (loc.size() > 2048)
	{
		code = 414;
		throw std::runtime_error(" URI Too Long");
	}
}

void wbs::Request::checkbodysize()
{
	std::string bodys("-69");

	if (serv.get_inf().get_directives().find("client_body_size") != serv.get_inf().get_directives().end())
		bodys = serv.get_inf().get_directives().find("client_body_size")->second.front();
	std::stringstream ss(bodys);
	long size;
	long clen;
	ss >> size;
	ss.clear();
	if (heads.find("Content-Length") != heads.end())
		ss.str(heads.find("Content-Length")->second);
	else
		ss.str("0");
	ss >> clen;
	if (size != -69 && clen > size)
	{
		code = 413;
		throw std::runtime_error(" Content Too Large");
	}
}

void wbs::Request::checkmeth()
{
	std::array<std::string, 3> alme = {{"GET", "POST", "DELETE"}};

	if (std::find(alme.begin(), alme.end(), meth) == alme.end())
	{
		code = 501;
		throw std::runtime_error(" Not Implemented");
	}
}

void wbs::Request::checkloc()
{
	setquery();

	std::string ro = serv.get_inf().get_root();
	std::map<std::string, Location> &locs = serv.get_inf().get_locations();

	std::map<std::string, Location>::iterator it = locs.find(loc);
	if (it == locs.end())
	{
		size_t pos = loc.back();
		for (pos = loc.find_last_of('/', pos - 1); pos != std::string::npos; pos--)
		{
			it = locs.find(loc.substr(0, pos));
			if (it != locs.end())
			{
				loc = it->second.get_root() + loc.substr(pos, loc.back());
				mloc = &it->second;
				break;
			}
			if (!pos)
				loc = ro + loc;
		}
	}
	else
	{
		loc = it->second.get_root();
		mloc = &it->second;
	}
	checkreturn();
	if (!opendir(loc.c_str()))
	{
		if (access(loc.c_str(), F_OK) == -1)
		{
			code = 404;
			throw std::runtime_error(" Not Found");
		}
	}
}

void wbs::Request::setquery()
{
	size_t pos = loc.find('?');
	if (pos != std::string::npos)
	{
		query = loc.substr(pos + 1, loc.size());
		loc = loc.substr(0, pos);
	}
}

void wbs::Request::checkver()
{
	if (ver != "HTTP/1.1" && ver != "HTTP/1.0")
	{
		code = 505;
		throw std::runtime_error(" HTTP Version Not Supported");
	}
}

void wbs::Request::checkreturn()
{
	if (mloc)
	{
		if (mloc->get_params().find("return") != mloc->get_params().end())
		{
			std::vector<std::string> ret = mloc->get_params().find("return")->second;
			std::string c = ret[0];
			std::string loc = ret[1];
			std::stringstream ss(c);
			ss >> code;
			throw std::runtime_error(" Moved Permanently\r\nLocation: " + loc);
		}
	}
}

void wbs::Request::chunked()
{
	if (heads.find("Transfer-Encoding") != heads.end() && heads.find("Transfer-Encoding")->second == "chunked")
	{
		std::string ch = body.substr(0, 100);
		std::string b = "";
		size_t i = 0;
		int s = strtol(ch.c_str(), NULL, 16);

		while (s)
		{
			i = body.find("\r\n", i) + 2;
			b += body.substr(i, s);
			i += s + 2;
			ch = body.substr(i, 100);
			s = strtol(ch.c_str(), NULL, 16);
		}
		body = b;
	}
}

std::map<std::string, std::string> wbs::Request::get_heads()
{
	return heads;
}

wbs::Listen &wbs::Request::get_serv()
{
	return serv;
}
wbs::Infos &wbs::Request::get_inf()
{
	return inf;
}

wbs::Location *wbs::Request::get_mloc()
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

std::string wbs::Request::get_oloc()
{
	return oloc;
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

std::string wbs::Request::get_query()
{
	return query;
}

std::string wbs::Request::get_up_dir()
{
	if (mloc)
	{
		if (mloc->get_params().find("upload_dir") != mloc->get_params().end())
			up_dir = mloc->get_params().find("upload_dir")->second.front();
	}
	else if (inf.get_directives().find("upload_dir") != inf.get_directives().end())
		up_dir = inf.get_directives().find("upload_dir")->second.front();

	return up_dir;
}

int wbs::Request::get_code()
{
	return code;
}
