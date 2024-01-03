/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bind.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:10:06 by agimi             #+#    #+#             */
/*   Updated: 2024/01/03 10:21:29 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Bind.hpp>

wbs::Bind::Bind(int d, int s, int p, u_long i) : SSocket(d, s, p, i)
{
	set_cfd(connect());
	c_test(get_cfd());
}

int wbs::Bind::connect()
{
	int sfd = get_sfd();
	sockaddr_in add = get_add();

	return bind(sfd, (sockaddr *)&add, sizeof(add));
}