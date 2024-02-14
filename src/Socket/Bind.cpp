/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bind.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:10:06 by agimi             #+#    #+#             */
/*   Updated: 2024/02/14 12:13:03 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

wbs::Bind::Bind(int d, int s, int pro, int por, u_long i) : SSocket(d, s, pro, por, i)
{
	cfd = connect();
	c_test(cfd);
}

wbs::Bind::Bind(const Bind &b)
{
	*this = b;
}

wbs::Bind &wbs::Bind::operator=(const Bind &b)
{
	if (this != &b)
		cfd = b.cfd;
	return *this;
}

wbs::Bind::~Bind()
{
	close(cfd);
}

int wbs::Bind::connect()
{
	int sfd = get_sfd();
	sockaddr_in add = get_add();

	return bind(sfd, (sockaddr *)&add, sizeof(add));
}