/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:01:06 by agimi             #+#    #+#             */
/*   Updated: 2024/05/10 15:54:37 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

int checkEnd(const std::string &str, const std::string &end)
{
	if (str.size() < end.size())
		return 1;

	return str.compare(str.size() - end.size(), end.size(), end) != 0;
}

void cleankey(std::string &key)
{
	if (key[key.size() - 1] == ':')
		key.erase(key.size() - 1);
}

void cleanval(std::string &val)
{
	if (val[val.size() - 1] == '\r')
		val.erase(val.size() - 1);
}

std::string readfile(std::string path)
{
	std::string bo;
	std::ifstream file(path, std::ios::binary);

	if (!file.is_open())
	{
		return "";
	}

	try
	{
		file.seekg(0, std::ios::end);
		std::streampos fileSize = file.tellg();
		file.seekg(0, std::ios::beg);

		bo.reserve(fileSize);

		const size_t bufferSize = 1024 * 64;
		std::vector<char> buffer(bufferSize);

		while (!file.eof())
		{
			file.read(buffer.data(), bufferSize);
			bo.append(buffer.data(), file.gcount());
		}
	}
	catch (const std::exception &e)
	{
		return "";
	}
	return bo;
}

std::map<std::string, std::string> set_mime()
{
	std::map<std::string, std::string> mime;
	std::string dot;
	std::string type;
	std::ifstream file("./config/mime");
	if (!file.is_open())
	{
		std::cerr << "mime are zooooot" << std::endl;
		return mime;
	}
	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream s(line);

		s >> type >> dot;
		mime.insert(std::pair<std::string, std::string>(dot, type));
	}
	return mime;
}

std::string get_mime(const std::string &pat)
{
	std::string type;

	if (pat.find_last_of('.') != std::string::npos)
		type = pat.substr(pat.find_last_of('.'), pat.size());
	else
		type = ".text";
	if (wbs::Server::mime.find(type) != wbs::Server::mime.end())
		return wbs::Server::mime.find(type)->second;
	else
		return wbs::Server::mime.find(".text")->second;
}

bool AllowedChars(const std::string &str)
{
	const std::string allowedChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%";
	return str.find_first_not_of(allowedChars) == std::string::npos;
}