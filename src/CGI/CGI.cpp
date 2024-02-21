/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:00:59 by mel-moun          #+#    #+#             */
/*   Updated: 2024/02/21 15:19:50 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

wbs::CGI::CGI()
{
}

wbs::CGI::CGI(const CGI &ob)
{
	*this = ob;
}

wbs::CGI &wbs::CGI::operator=(const CGI &ob)
{
	if (this != &ob)
	{
		std::cout << "choofoonniii " << std::endl;
		std::cout << "laaaaa " << std::endl;
	}
	return (*this);
}

wbs::CGI::~CGI()
{
}
