/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:03:15 by agimi             #+#    #+#             */
/*   Updated: 2024/04/27 12:20:00 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <webserv.hpp>

namespace wbs
{
	class Request
	{
	private:
		Listen &serv;
		std::map<std::string, std::string> heads;
		std::string meth;
		std::string loc;
		std::string ver;
		std::string body;
		int code;

		Request();
		void set_heads(std::stringstream &, std::string &);
		void set_body(const std::string &);
		void checkmeth();
		void checkloc();
		void checkver();

	public:
		Request(Listen &, const std::string &);
		Request(const Request &);
		Request &operator=(const Request &);
		~Request();

		std::string get_loc();
	};
}