/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:01:58 by fbelahse          #+#    #+#             */
/*   Updated: 2024/05/21 13:07:33 by fbelahse         ###   ########.fr       */
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
			std::string length;
			std::string body;
			std::string content;
			
			int code;
		public:
			Response();
			~Response();
			
			std::string mime_comp();
			void count_size(std::string &url);
			int check_file(std::string &url);
			int check_meth(const std::string &method);
			void get_file(std::string &url);
			void get_cont_ty(std::string &url_tst);
			void print_map(std::map<const std::string, std::string>& map);
			void openf_f();
			void start_tst();
			void get_resource_type(const std::string &path);
			void generate_response_headers(int code, const std::string &status);
			void generate_body(std::string &url, int ind, int code);
			std::string get_method(std::string &url);
			void post_method(std::string &url);
			void delete_method(std::string &url);
			bool check_auto_index();
			bool get_req_resource(std::string &loc);
			void delete_all_content(std::string &loc);
			bool location_has_cgi();
	};
}
