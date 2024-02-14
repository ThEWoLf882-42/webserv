/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bind.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 09:51:23 by agimi             #+#    #+#             */
/*   Updated: 2024/02/14 12:11:55 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <webserv.hpp>

namespace wbs
{
	class Bind : public SSocket
	{
	private:
		int cfd;
		Bind();

	public:
		Bind(const Bind &);
		Bind &operator=(const Bind &);
		~Bind();
		Bind(int d, int s, int pro, int por, u_long i);
		int connect();
	};
}