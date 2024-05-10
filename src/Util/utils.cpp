/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:01:06 by agimi             #+#    #+#             */
/*   Updated: 2024/05/10 17:11:14 by agimi            ###   ########.fr       */
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
		type = ".html";
	if (wbs::Server::mime.find(type) != wbs::Server::mime.end())
		return wbs::Server::mime.find(type)->second;
	else
		return wbs::Server::mime.find(".html")->second;
}

bool AllowedChars(const std::string &str)
{
	const std::string allowedChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%";
	return str.find_first_not_of(allowedChars) == std::string::npos;
}

std::vector<std::string> list_directory(const std::string &directory)
{
	std::vector<std::string> files;
	DIR *dirp = opendir(directory.c_str());
	if (dirp != NULL)
	{
		struct dirent *dp;
		while ((dp = readdir(dirp)) != NULL)
		{
			if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
				files.push_back(dp->d_name);
		}
		closedir(dirp);
	}
	return files;
}

std::string autoindex(const std::string &directory)
{
	std::string html = "<!DOCTYPE html><html><head><title>Index of ";

	html += directory;

	html += "</title></head><body><h1>Index of ";

	html += directory;

	html += "</h1><hr><ul><li><a href=\".\">.</a></li><li><a href=\"../\">..</a></li>";

	std::vector<std::string> files = list_directory(directory); // Call list_directory

	// Traditional for loop
	for (unsigned int i = 0; i < files.size(); ++i)
	{
		const std::string &file = files[i];
		html += "<li><a href='" + file + "'>" + file + "</a></li>";
	}

	html += "</ul><hr></body></html>";

	return html;
}
