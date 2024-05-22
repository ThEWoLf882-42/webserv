/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:01:58 by fbelahse          #+#    #+#             */
/*   Updated: 2024/05/22 11:13:29 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <webserv.hpp>

namespace wbs
{
	class Response
	{
		private:
			Request &req;
			Infos &inf;
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
			std::string response;
			
			int code;
			Response();
		public:
			~Response();
			Response(Request &req);
			
			void count_size(std::string &url);
			int check_file(std::string &url);
			int check_meth(const std::string &method);
			void start_resp();
			void get_resource_type(const std::string &path);
			void generate_response(int code, const std::string &status);
			void generate_body(std::string &url, int ind, int code);
			std::string get_method(std::string &url);
			std::string post_method(std::string &url);
			std::string delete_method(std::string &url);
			bool check_auto_index();
			void delete_all_content(std::string &loc);
			void delete_file(std::string &file);
			bool location_has_cgi();
			bool if_supports_upload();
			bool there_is_an_index();

			const std::string &get_response();
	};
}
