/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SSocket.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:02:05 by agimi             #+#    #+#             */
/*   Updated: 2024/01/03 10:24:32 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SSocket.hpp>

wbs::SSocket::SSocket(int d, int s, int p, u_long i)
{
	add.sin_family = d;
	add.sin_port = htons(p);
	add.sin_addr.s_addr = htonl(i);

	sfd = socket(d, s, p);
	c_test(sfd);
}

void wbs::SSocket::c_test(int tst)
{
	if (tst < 0)
	{
		perror("Connection Failed 😞");
		exit(EXIT_FAILURE);
	}
}

sockaddr_in wbs::SSocket::get_add()
{
	return add;
}

int wbs::SSocket::get_sfd()
{
	return sfd;
}

int wbs::SSocket::get_cfd()
{
	return cfd;
}

void wbs::SSocket::set_cfd(int fd)
{
	cfd = fd;
}