/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:03:15 by agimi             #+#    #+#             */
/*   Updated: 2024/04/28 13:00:38 by agimi            ###   ########.fr       */
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
		Location mloc;
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

		Location &get_mloc();
		std::string get_meth();
		std::string get_loc();
		std::string get_ver();
		std::string get_body();
		int get_code();
	};
}