/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:01:58 by fbelahse          #+#    #+#             */
/*   Updated: 2024/04/29 12:46:13 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <webserv.hpp>

namespace wbs
{
	class Response
	{
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
