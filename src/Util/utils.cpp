/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:01:06 by agimi             #+#    #+#             */
/*   Updated: 2024/02/20 20:47:48 by agimi            ###   ########.fr       */
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
		// set400();
		// path = "/404.html";
		// readfile(bo);
		return NULL;
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
		return NULL;
	}
	return bo;
}