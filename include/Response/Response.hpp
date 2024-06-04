/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:01:58 by fbelahse          #+#    #+#             */
/*   Updated: 2024/06/03 12:30:05 by agimi            ###   ########.fr       */
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
		std::map<std::string, std::string> map_env;
		std::string path;
		std::string ress_type;
		std::string meth;
		std::string length;
		std::string body;
		std::string response;
		char **envp_c;

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
		bool check_auto_index();
		void delete_all_content(std::string &loc);
		void delete_file(std::string &file);
		bool location_has_cgi();
		bool if_supports_upload();
		bool there_is_an_index();
		void create_envp();
		void set_env();
		void free_envp();
		void print_env();
		std::string get_cgi_path();

		std::string get_method(std::string &url);
		std::string post_method(std::string &url);
		std::string delete_method(std::string &url);

		const std::string &get_response();
		char **&get_envi_var();
		Request &get_req();
		
		const std::string &get_path();
	};
}
