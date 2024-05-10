/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:01:58 by fbelahse          #+#    #+#             */
/*   Updated: 2024/05/10 15:47:27 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <webserv.hpp>

namespace wbs_r
{
	class Response
	{
		private:
			std::vector<std::string> vec_p;
			std::vector<std::string> vec;
			std::map<const std::string, std::string> map;
			std::string extention;
			std::string file_name;
			std::string status;
			std::string path;
			std::string dir_stats;
			std::string ress_type;
			std::string ver;
			std::string meth;
			int code;
			int length;
		public:
			Response();
			~Response();
			
			std::string mime_comp();
			void count_size(std::string &url);
			int check_file(std::string &url);
			void mapping();
			int check_meth(const std::string &method);
			void get_file(std::string &url);
			void get_file_p(std::string &url, std::string s1);
			void hund_(std::string &st);
			void get_cont_ty(std::string &url_tst);
			void print_map(std::map<const std::string, std::string>& map);
			void openf_f();
			void uhhh();
			void start_tst();
			void check_dir_file(const std::string &path);
			int get_ressource_type(const std::string &path);
			bool post_resp();
			int check_code();
			void gen_resp();
	};
}

bool supports_upload(const std::string &path);
void upload_req_body(const std::string &path);
bool location_has_cgi(const std::string &path);
bool get_req_ressource();
