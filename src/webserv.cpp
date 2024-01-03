/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:44:51 by agimi             #+#    #+#             */
/*   Updated: 2024/01/03 20:46:13 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

void readfile(std::string &bo, const std::string path, respond &r)
{
	std::ifstream file("." + path);
	std::stringstream buf;

	if (!file.is_open())
	{
		r.sta = "404 ";
		r.stamsg = "Not Found ";
		r.type = "";
		readfile(bo, "/404.html", r);
		return;
	}

	buf << file.rdbuf();
	bo = buf.str();

	file.close();
}

int main()
{
	wbs::Server s(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10);
}