/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:44:51 by agimi             #+#    #+#             */
/*   Updated: 2024/02/13 16:39:11 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

int main(int ac, char **av)
{
	// if (2 == ac)
	// 	wbs::Server s(av[1]);
	// else
	// 	wbs::Server s;
	try
	{
		if (ac > 2)
			throw std::runtime_error("It must be 2 arguments.");
		wbs::Confile ob(av[1]);
		ob.parsing();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}
