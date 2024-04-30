/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:01:58 by fbelahse          #+#    #+#             */
/*   Updated: 2024/04/30 17:30:35 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <webserv.hpp>

struct resp
{
	std::vector<std::string>vec;
	std::vector<std::string>vec_p;
	std::map<const std::string, std::string> map;
	std::string file_name;
	std::string status;
	std::string extention;
	std::string path;
	std::string meth;
	std::string str;
	std::string n_str;
	std::string loc;
	double ver;
	int length;
	int code;
}respp_t;

namespace wbs
{
	class Response
	{
		public:
			Response();
			~Response();
			
			std::string mime_comp();
			void count_size(std::string &url);
			int check_file(std::string &url);
			void mapping();
			int check_meth();
			void get_file(std::string &url);
			void get_file_p(std::string &url, std::string s1);
			void hund_(std::string &st);
			void get_cont_ty(std::string &url_tst);
			void print_map(std::map<const std::string, std::string>& map);
			void openf();
			void uhhh();
			void start_tst();
	private:
		int ver;
		std::string stat;
		std::string url_tst;
		std::string con_ty;
		std::string serv;
		std::string meth;
		std::string tst;
		size_t con_len;
		int code;

	public:
		Response();
		~Response();

		std::string GenRes();
		void count_size();
		void get_cont_ty();
		void GetResp();
	};
}
