/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bind.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:10:06 by agimi             #+#    #+#             */
/*   Updated: 2024/02/16 12:09:54 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

wbs::Bind::Bind(int d, int s, int pro, int por, unsigned int i) : SSocket(d, s, pro, por, i)
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