/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SSocket.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:02:13 by agimi             #+#    #+#             */
/*   Updated: 2024/01/03 10:16:05 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdint.h>
#include <iostream>

namespace wbs
{
	class SSocket
	{
	private:
		int sfd;
		int cfd;
		struct sockaddr_in add;

	public:
		SSocket(int, int, int, u_long i);

		virtual int connect() = 0;
		void c_test(int);

		sockaddr_in get_add();
		int get_sfd();
		int get_cfd();

		void set_cfd(int);
	};
}