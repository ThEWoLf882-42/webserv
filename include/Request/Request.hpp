/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:03:15 by agimi             #+#    #+#             */
/*   Updated: 2024/02/20 19:53:00 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <webserv.hpp>

namespace wbs
{
	class Request
	{
	private:
		std::map<std::string, std::string> heads;
		std::string meth;
		std::string loc;
		std::string ver;
		int code;

		Request();
		void set_heads(std::stringstream &, std::string &);
		void checkmeth();
		void checkloc();
		void checkver();

	public:
		Request(const std::string &);
		Request(const Request &);
		Request &operator=(const Request &);
		~Request();
	};
}