/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responce.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:21:15 by fbelahse          #+#    #+#             */
/*   Updated: 2024/05/22 10:54:13 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

wbs::Response::Response(Request &req) : req(req), inf(req.get_inf())
{
	start_resp();
}

wbs::Response::~Response() {}

bool wbs::Response::location_has_cgi()
{
	std::string ex = path.substr(path.find_last_of('.'), path.size());
	std::string key;
	if (req.get_mloc())
	{
		wbs::Location loc = *req.get_mloc();

		if (loc.get_params().find("cgi_extention") != loc.get_params().end())
			key = *loc.get_params().find("cgi_extention")->second.begin();
	}
	else if (inf.get_directives().find("cgi_extention") != inf.get_directives().end())
		key = *inf.get_directives().find("cgi_extention")->second.begin();
	return key == ex;
}

bool wbs::Response::if_supports_upload()
{
	std::vector<std::string> ind;
	if (inf.get_directives().find("methods") != inf.get_directives().end())
		ind = inf.get_directives().find("methods")->second;
		
	if (req.get_mloc()){
		wbs::Location loc = *req.get_mloc();
		
		if (loc.get_params().find("methods") != loc.get_params().end())
			ind = loc.get_params().find("methods")->second;
	}
	if(std::find(ind.begin(), ind.end(), "POST") != ind.end()){
		return (true);
	}
	return (false);
}

void wbs::Response::get_resource_type(const std::string &path)
{
	struct stat s;

	if (stat(path.c_str(), &s) == 0)
	{ // extract the resource info, which will contain if it's a dir/file (o_o;)?
		if (s.st_mode & S_IFDIR)
		{ // st_mode field contains the file type and permissions for the file ~(^v^)~
			ress_type = "directory";
			return;
		}
		else if (s.st_mode & S_IFREG)
		{
			ress_type = "file";
			return;
		}
		else
		{
			ress_type = "";
			return;
		}
	}
	else
	{
		std::cout << ">>ERROR<<" << std::endl;
		return;
	}
}

//----------------RESP HEADER/BODY

void wbs::Response::count_size(std::string &url)
{
	std::string body = readfile(url.c_str());
	std::stringstream s;

	s << body.size();
	std::string size = s.str();
	url += size + "\r\n\r\n";
	url += body;

	length = size;
}

//--------------------CHECK

bool wbs::Response::check_auto_index()
{
	std::string key;
	if (inf.get_directives().find("autoindex") != inf.get_directives().end())
		key = *inf.get_directives().find("autoindex")->second.begin();
	if (req.get_mloc())
	{
		wbs::Location loc = *req.get_mloc();

		if (loc.get_params().find("autoindex") != loc.get_params().end())
			key = *loc.get_params().find("autoindex")->second.begin();
	}
	if (key == "on")
		return true;
	return false;
}

void wbs::Response::generate_response(int code, const std::string &status)
{
	std::stringstream ss;
	ss << "HTTP/1.1 " << code << status << "\r\n"
	   << "Content-Type: " << get_mime(path) << "\r\n"
	   << "Content-Length: " << length << "\r\n\r\n"
	   << body;

	response = ss.str();
}

int wbs::Response::check_meth(const std::string &method)
{
	std::vector<std::string> methods;
	if (inf.get_directives().find("methods") != inf.get_directives().end())
		methods = inf.get_directives().find("methods")->second;
	if (req.get_mloc())
	{
		Location loc = *req.get_mloc();
		if (loc.get_params().find("methods") != loc.get_params().end())
			methods = loc.get_params().find("methods")->second;
	}
	if (std::find(methods.begin(), methods.end(), method) == methods.end())
		return 0;
	if (method == "GET")
		return (1);
	else if (method == "POST")
		return (2);
	else if (method == "DELETE")
		return (3);
	return (0);
}

int wbs::Response::check_file(std::string &url)
{
	// if (access(url.c_str(), F_OK) != 0)
	// {
	// 	// std::cerr << "1" << std::endl;
	// 	generate_body(url, 2, 404);
	// 	generate_response(404, " Not Found");
	// 	return (0);
	// }
	// else if ((access(url.c_str(), R_OK) != 0 && access(url.c_str(), W_OK) != 0) || (access(url.c_str(), R_OK)) != 0)
	// {
	// 	generate_body(url, 2, 403);
	// 	generate_response(403, " Forbidden");
	// 	return (0);
	// }
	// std::cerr << url << std::endl;
	if (!opendir(url.c_str()))
	{
		if (access(url.c_str(), F_OK) == -1 && access(url.c_str(), R_OK) == -1)
		{
			// std::cerr << "1" << std::endl;
			generate_body(url, 2, 403);
			generate_response(403, " Forbidden");
			return (0);
		}
	}
	else if (!opendir(url.c_str()))
	{
		// std::cerr << "2" << std::endl;
		generate_body(url, 2, 404);
		generate_response(404, " Not Found");
		return (0);
	}
	else if (check_meth(meth))
	{
		generate_body(url, 2, 405);
		generate_response(405, " Method Not Allowed");
		return (0);
	}
	else if (!access(url.c_str(), F_OK))
	{
		generate_body(url, 1, 200);
		generate_response(200, " OK");
		return (1);
	}
	return (1);
}

//-----------------------

bool wbs::Response::there_is_an_index()
{
	std::vector<std::string> indexs;
	if (inf.get_directives().find("default_file") != inf.get_directives().end())
		indexs = inf.get_directives().find("default_file")->second;
	if (req.get_mloc())
	{
		Location loc = *req.get_mloc();
		if (loc.get_params().find("default_file") != loc.get_params().end())
			indexs = loc.get_params().find("default_file")->second;
	}


	for (std::vector<std::string>::iterator it = indexs.begin(); it != indexs.end(); it++)
	{
		std::string loc = path + *it;
		if (access(loc.c_str(), F_OK) != -1)
		{
			path = loc;
			return true;
		}
	}
	return false;
}

void wbs::Response::generate_body(std::string &url, int ind, int code)
{

	if (ind == 1 && (code == 200 || code == 201 || code == 204))
		body = readfile(url.c_str());
	else if (ind == 3 && code == 200)
		body = autoindex(req.get_loc(), req.get_oloc());

	std::map<int, std::string> error_path;
	error_path[403] = "/Users/fbelahse/Desktop/webserv/extra/403.html";
	error_path[404] = "/Users/fbelahse/Desktop/webserv/extra/404.html";
	error_path[405] = "/Users/fbelahse/Desktop/webserv/extra/405.html";
	error_path[301] = "/Users/fbelahse/Desktop/webserv/extra/301.html";
	error_path[409] = "/Users/fbelahse/Desktop/webserv/extra/409.html";
	error_path[500] = "/Users/fbelahse/Desktop/webserv/extra/500.html";

	if (ind == 2)
		body = readfile(error_path[code]);

	std::stringstream s;

	s << body.size();
	length = s.str();
}

std::string wbs::Response::get_method(std::string &loc)
{
	// std::cerr << "loc " << loc[loc.size() - 1] << std::endl;
	get_resource_type(loc);
	// std::cerr << "rt " << ress_type << std::endl;
	if (ress_type == "directory")
	{
		// std::cerr << req.get_oloc() << " [" << req.get_oloc().back() << "]" <<std::endl;
		if (req.get_oloc().back() != '/')
		{
			generate_body(loc, 2, 301);
			generate_response(301, " Moved Permanently\r\nLocation: " + req.get_oloc() + '/');
			return "";
		}
		else
		{
			if (there_is_an_index() == true)
			{
				if (location_has_cgi())
				{
					// return code based on cgi (?)
				}
				else
				{
					generate_body(loc, 1, 200);
					generate_response(200, " OK");
					return "";
				}
			}
			else if (check_auto_index() == true)
			{
				generate_body(loc, 3, 200);
				generate_response(200, " OK");
				return "";
			}
			else
			{
				// std::cerr << "2" << std::endl;
				generate_body(loc, 2, 403);
				generate_response(403, " Forbidden");
				return "";
			}
		}
	}
	if (ress_type == "file")
	{
		if (location_has_cgi())
		{
			// generate_body(loc, 1, 200);
			// generate_response(200, " OK");
			// return "";
		}
		else
		{
			generate_body(loc, 1, 200);
			generate_response(200, " OK");
			return "";
		}
	}
	return "";
}

std::string wbs::Response::post_method(std::string &loc)
{
	if (if_supports_upload())
	{
		generate_body(loc, 1, 201);
		generate_response(201, " Created");
		return ("");
	}
	else
	{
		get_resource_type(loc);
		if (ress_type == "directory")
		{
			if (loc[loc.size() - 1] != '/')
			{
				generate_body(loc, 2, 301);
				generate_response(301, " Moved Permanently\r\nLocation: " + req.get_oloc() + '/');
				return "";
			}
			else
			{
				if (there_is_an_index())
				{
					if (location_has_cgi())
					{
						// run cgi
					}
					else
					{
						// std::cerr << "3" << std::endl;
						generate_body(loc, 2, 403);
						generate_response(403, " Forbidden");
						return ("");
					}
				}
				else
				{
					// std::cerr << "4" << std::endl;
					generate_body(loc, 2, 403);
					generate_response(403, " Forbidden");
					return ("");
				}
			}
		}
		if (ress_type == "file")
		{
			if (location_has_cgi())
			{
				// run cgi
			}
			else
			{
				// std::cerr << "5" << std::endl;
				generate_body(loc, 2, 403);
				generate_response(403, " Forbidden");
				return ("");
			}
		}
		// std::cerr << "3" << std::endl;
		generate_body(loc, 2, 404);
		generate_response(404, " Not Found");
		return ("");
	}
}

void wbs::Response::delete_all_content(std::string &loc)
{
	DIR *dir = opendir(loc.c_str());
	if (dir == NULL)
	{
		generate_body(loc, 2, 500);
		generate_response(500, " Internal Server Error");
		return;
	}

	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL)
	{
		std::string f_name = entry->d_name;
		if (f_name != "." && f_name != "..")
		{
			std::string f_path = loc + f_name;
			if (remove(f_path.c_str()) != 0)
			{
				generate_body(loc, 2, 500);
				generate_response(500, " Internal Server Error");
				closedir(dir);
				return;
			}
		}
	}
	closedir(dir);

	int count = 0;
	dir = opendir(loc.c_str());
	struct dirent *ent;
	while ((ent = readdir(dir)) != NULL)
	{
		std::string f_name = ent->d_name;
		if (f_name != "." && f_name != "..")
		{
			count++;
		}
	}
	closedir(dir);

	if (count == 0)
	{
		generate_body(loc, 1, 204);
		generate_response(204, " No Content");
		return;
	}
	else
	{
		if (access(path.c_str(), W_OK) != 0 || access(path.c_str(), X_OK) != 0)
		{
			// std::cerr << "6" << std::endl;
			generate_body(loc, 2, 403);
			generate_response(403, " Forbidden");
			return;
		}
		else
		{
			generate_body(loc, 2, 500);
			generate_response(500, "Internal Server Error");
			return;
		}
	}
	return;
}

// get_req_res : readfile

std::string wbs::Response::delete_method(std::string &loc)
{
	get_resource_type(loc);
	if (ress_type == "directory")
	{
		if (loc[loc.size() - 1] != '/')
		{
			generate_body(loc, 2, 409);
			generate_response(409, " Conflict");
			loc += '/';
			return (loc);
		}
		else
		{
			if (location_has_cgi())
			{
				if (there_is_an_index())
				{
					// run cgi
				}
				else
				{
					// std::cerr << "7" << std::endl;
					generate_body(loc, 2, 403);
					generate_response(403, " Forbidden");
					return ("");
				}
			}
			delete_all_content(loc);
		}
		// std::cerr << "4" << std::endl;
		generate_body(path, 2, 404);
		generate_response(404, " Not Found");
	}
	if (ress_type == "file")
	{
		if (location_has_cgi())
		{
			// 3tiha l meriem :3
		}
		else
			delete_all_content(loc);
	}
	return ("");
}

void wbs::Response::start_resp()
{
	path = req.get_loc();
	std::string codemsg = req.get_codemsg();
	std::string method = req.get_meth();
	ver = req.get_ver();
	code = req.get_code();

	// std::cerr << path << std::endl;
	if (code != 200)
	{
		generate_body(path, 2, code);
		generate_response(code, req.get_codemsg());
	}
	else
	{
		int check = check_file(path);
		if (check == 0)
		{
			return;
		}
		else
		{
			switch (check_meth(method))
			{
			case 0:
				generate_body(path, 2, 405);
				generate_response(405, " Method Not Allowed");
				break;
			case 1:
				get_method(path);
				break;
			case 2:
				post_method(path);
				break;
			case 3:
				delete_method(path);
				break;
			}
		}
	}
}

const std::string &wbs::Response::get_response()
{
	return response;
}