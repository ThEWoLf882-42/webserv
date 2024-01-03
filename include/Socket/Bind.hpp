/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bind.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 09:51:23 by agimi             #+#    #+#             */
/*   Updated: 2024/01/03 12:01:08 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "SSocket.hpp"

namespace wbs
{
	class Bind : public SSocket
	{
	private:
		int	cfd;
	public:
		Bind(int d, int s, int pro, int por, u_long i);
		int connect();
	};
}