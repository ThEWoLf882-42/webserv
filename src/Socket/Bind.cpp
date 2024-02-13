/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bind.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:10:06 by agimi             #+#    #+#             */
/*   Updated: 2024/02/13 17:38:10 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

wbs::Bind::Bind(int d, int s, int pro, int por, u_long i) : SSocket(d, s, pro, por, i)
{
	cfd = connect();
	c_test(cfd);
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