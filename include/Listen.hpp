/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Listen.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:32:50 by agimi             #+#    #+#             */
/*   Updated: 2024/01/03 10:41:40 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Bind.hpp"

namespace wbs
{
	class Listen
	{
	private:
		int blog;

	public:
		Listen(int, int, int, u_long, int);
	};
}