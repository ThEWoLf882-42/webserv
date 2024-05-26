/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Listen.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:32:50 by agimi             #+#    #+#             */
/*   Updated: 2024/05/25 20:30:42 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <webserv.hpp>

namespace wbs
{
	class Listen : public Bind
	{
	private:
		Infos &inf;
		std::map<long, std::string> reqs;
		int blog;
		int list;
		Listen();
		Listen(const Listen &);
		Listen &operator=(const Listen &);

	public:
		Listen(int, int, int, int, unsigned int, int, Infos &);
		virtual ~Listen();

		Infos &get_inf();

		const int port;
		void listning();
		void close(long);
		long accept();
		int recv(long);
		int send(long);
		void proc(long);
	};
}