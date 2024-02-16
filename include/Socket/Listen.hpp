/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Listen.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:32:50 by agimi             #+#    #+#             */
/*   Updated: 2024/02/16 11:37:52 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <webserv.hpp>

namespace wbs
{
	class Listen : public Bind
	{
	private:
		std::map<long, std::string> reqs;
		int blog;
		int list;
		Listen();
		Listen(const Listen &);
		Listen &operator=(const Listen &);

	public:
		void close(long);
		void add_req(long);
		int recv(long);
		int send(long);
		Listen(int, int, int, int, unsigned int, int);
		virtual ~Listen();
		void listning();
	};
}