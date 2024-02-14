/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:44:51 by agimi             #+#    #+#             */
/*   Updated: 2024/02/14 10:19:02 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

int main(int ac, char **av)
{
	try
	{
		if (ac != 2 && ac != 1)
			throw std::runtime_error("Invalid number of arguments.");

		if (ac == 2)
			wbs::Confile ob(av[1]);
		else
			wbs::Confile ob;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
