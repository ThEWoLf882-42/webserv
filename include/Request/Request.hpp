/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:03:15 by agimi             #+#    #+#             */
/*   Updated: 2024/05/31 12:30:27 by mel-moun         ###   ########.fr       */
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
		Location *mloc;
		Infos &inf;
		std::map<std::string, std::string> heads;
		std::string meth;
		std::string loc;
		std::string oloc;
		std::string ver;
		std::string body;
		std::string codemsg;
		std::string query;
		int code;

		Request();
		void set_heads(std::stringstream &, std::string &);
		void set_body(const std::string &);
		void checkencoding();
		void checkbodysize();
		void checkmeth();
		void checkloc();
		void checkver();
		void setquery();
		void checkreturn();
		void chunked();

	public:
		Request(Listen &, const std::string &);
		Request(const Request &);
		Request &operator=(const Request &);
		~Request();

		Listen &get_serv();
		Infos &get_inf();
		Location *get_mloc();
		std::map<std::string, std::string> get_heads();
		std::string get_meth();
		std::string get_loc();
		std::string get_oloc();
		std::string get_ver();
		std::string get_body();
		std::string get_codemsg();
		std::string get_query();
		int get_code();
	};
}