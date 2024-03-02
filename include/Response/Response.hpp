/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:01:58 by fbelahse          #+#    #+#             */
/*   Updated: 2024/03/01 12:00:37 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <webserv.hpp>

namespace wbs_r
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
