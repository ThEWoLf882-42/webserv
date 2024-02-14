/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Listen.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:32:50 by agimi             #+#    #+#             */
/*   Updated: 2024/02/14 12:14:25 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <webserv.hpp>

namespace wbs
{
	class Listen : public Bind
	{
	private:
		int blog;
		int list;
		Listen();

	public:
		Listen(int, int, int, int, u_long, int);
		Listen(const Listen &);
		Listen &operator=(const Listen &);
		virtual ~Listen();
		void listning();
	};
}