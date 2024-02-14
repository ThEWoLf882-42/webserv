/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Listen.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:35:32 by agimi             #+#    #+#             */
/*   Updated: 2024/02/14 12:16:36 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

wbs::Listen::Listen(int d, int s, int pro, int por, u_long i, int b) : Bind(d, s, pro, por, i), blog(b)
{
	listning();
	c_test(list);
}

wbs::Listen::Listen(const Listen &l)
{
	*this = l;
}

wbs::Listen &wbs::Listen::operator=(const Listen &l)
{
	if (this != &l)
	{
		blog = l.blog;
		list = l.list;
	}
	return *this;
}

wbs::Listen::~Listen()
{
	close(list);
}

void wbs::Listen::listning()
{
	list = listen(get_sfd(), blog);
}