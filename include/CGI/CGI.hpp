/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:00:57 by mel-moun          #+#    #+#             */
/*   Updated: 2024/02/20 11:05:04 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <webserv.hpp>

class CGI
{
public:
    CGI();
    CGI(const CGI &ob);
    CGI& operator=(const CGI &ob);
    ~CGI();
};