/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:44:51 by agimi             #+#    #+#             */
/*   Updated: 2024/02/13 10:14:55 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

int main(int ac, char **av)
{
	if (2 == ac)
		wbs::Confile c(av[1]);
	else
		wbs::Confile c;
	wbs::Server s(av[1]);
	wbs::Server s;
}