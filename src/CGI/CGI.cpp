/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:00:59 by mel-moun          #+#    #+#             */
/*   Updated: 2024/02/20 11:03:30 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

CGI::CGI()
{

}

CGI::CGI(const CGI &ob)
{ 
    *this = ob;
}

CGI& CGI::operator=(const CGI &ob)
{
    if (this != &ob)
    {
        
    }
    return (*this);
}

CGI::~CGI()
{

}
