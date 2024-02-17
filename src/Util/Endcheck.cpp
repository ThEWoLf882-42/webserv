/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Endcheck.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:01:06 by agimi             #+#    #+#             */
/*   Updated: 2024/02/16 17:53:03 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

int checkEnd(const std::string &str, const std::string &end)
{
	if (str.size() < end.size())
		return 1;

	return str.compare(str.size() - end.size(), end.size(), end) != 0;
}
