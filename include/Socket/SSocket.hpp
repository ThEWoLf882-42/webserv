/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SSocket.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:02:13 by agimi             #+#    #+#             */
/*   Updated: 2024/01/04 15:05:41 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <webserv.hpp>

namespace wbs
{
	class SSocket
	{
	private:
		int sfd;
		struct sockaddr_in add;

	public:
		~SSocket();
		SSocket(int, int, int, int, u_long);

		virtual int connect() = 0;
		void c_test(int);

		sockaddr_in get_add();
		int get_sfd();

		void set_cfd(int);
	};
}