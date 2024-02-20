/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:00:57 by mel-moun          #+#    #+#             */
/*   Updated: 2024/02/20 17:49:33 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <webserv.hpp>

namespace wbs
{
	class CGI
	{
	public:
		CGI();
		CGI(const CGI &ob);
		CGI &operator=(const CGI &ob);
		~CGI();
	};
}