/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SSocket.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:02:05 by agimi             #+#    #+#             */
/*   Updated: 2024/02/29 15:43:55 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

wbs::SSocket::SSocket(int d, int s, int pro, int por, unsigned int i)
{
	int reuse = 1;
	add.sin_family = d;
	add.sin_port = htons(por);
	add.sin_addr.s_addr = htonl(i);

	sfd = socket(d, s, pro);
	c_test(sfd);
	c_test(setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)));
}

wbs::SSocket::~SSocket()
{
	close(sfd);
}

void wbs::SSocket::c_test(int tst)
{
	if (tst < 0)
	{
		perror("Connection Failed 😞");
		// exit(EXIT_FAILURE);
	}
}

sockaddr_in wbs::SSocket::get_add()
{
	return add;
}

long wbs::SSocket::get_sfd()
{
	return sfd;
}