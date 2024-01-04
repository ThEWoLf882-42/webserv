/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Listen.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:35:32 by agimi             #+#    #+#             */
/*   Updated: 2024/01/04 15:03:34 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

wbs::Listen::Listen(int d, int s, int pro, int por, u_long i, int b) : Bind(d, s, pro, por, i), blog(b)
{
	listning();
	c_test(list);
}

wbs::Listen::~Listen()
{
	close(list);
}

void wbs::Listen::listning()
{
	list = listen(get_sfd(), blog);
}