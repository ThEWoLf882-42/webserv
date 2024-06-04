/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responce.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:21:15 by fbelahse          #+#    #+#             */
/*   Updated: 2024/06/04 14:40:03 by agimi            ###   ########.fr       */
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
	if (inf.get_directives().find("cgi_extention") != inf.get_directives().end())
		key = *inf.get_directives().find("cgi_extention")->second.begin();
	if (req.get_mloc())
	{
		wbs::Location loc = *req.get_mloc();

		if (loc.get_params().find("cgi_extention") != loc.get_params().end())
			key = loc.get_params().find("cgi_extention")->second.front();
	}
	return key == ex;
}

bool wbs::Response::if_supports_upload()
{
	std::vector<std::string> ind;
	if (inf.get_directives().find("methods") != inf.get_directives().end())
		ind = inf.get_directives().find("methods")->second;

	if (req.get_mloc())
	{
		wbs::Location loc = *req.get_mloc();

		if (loc.get_params().find("methods") != loc.get_params().end())
			ind = loc.get_params().find("methods")->second;
	}
	if (std::find(ind.begin(), ind.end(), "POST") != ind.end())
	{
		return (true);
	}
	return (false);
}

void wbs::Response::get_resource_type(const std::string &path)
{
	struct stat s;

	if (stat(path.c_str(), &s) == 0)
	{
		if (s.st_mode & S_IFDIR)
		{
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
		std::cerr << ">>ERROR<<" << std::endl;
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
	if (code == 201 || code == 204 || code == 500)
	{
		ss << "HTTP/1.1 " << code << status << "\r\n"
		   << "Content-Type: text/html" << "\r\n"
		   << "Content-Length: " << length << "\r\n\r\n"
		   << body;
	}
	else
	{
		ss << "HTTP/1.1 " << code << status << "\r\n"
		   << "Content-Type: " << get_mime(path) << "\r\n"
		   << "Content-Length: " << length << "\r\n\r\n"
		   << body;
	}

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
	else if (method == "PUT")
		return (4);
	return (0);
}

int wbs::Response::check_file(std::string &url)
{
	if (!opendir(url.c_str()))
	{
		if (access(url.c_str(), F_OK) == -1 && access(url.c_str(), R_OK) == -1)
		{
			generate_body(url, 2, 403);
			generate_response(403, " Forbidden");
			return (0);
		}
	}
	else if (!opendir(url.c_str()))
	{
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

	if (ind == 2)
		body = readfile(inf.get_error_pages()[code]);
	if (ind == 4)
	{
		size_t p = url.find("\r\n\r\n");
		if (p != std::string::npos)
			body = url.substr(p + 4, url.size());
	}

	std::stringstream s;

	s << body.size();
	length = s.str();
}

std::string wbs::Response::get_method(std::string &loc)
{
	get_resource_type(loc);
	if (ress_type == "directory")
	{
		if (req.get_oloc().back() != '/')
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
					CGI cgi(*this);
					generate_body(cgi.get_content(), 4, 200);
					generate_response(200, " OK");
				}
				else
				{
					generate_body(loc, 1, 200);
					generate_response(200, " OK");
					return "";
				}
			}
			else if (check_auto_index())
			{
				generate_body(loc, 3, 200);
				generate_response(200, " OK");
				return "";
			}
			else
			{
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
			CGI cgi(*this);
			generate_body(cgi.get_content(), 4, 200);
			generate_response(200, " OK");
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
	get_resource_type(loc);
	if (ress_type == "directory")
	{
		if (req.get_oloc().back() != '/')
		{
			generate_body(loc, 2, 301);
			generate_response(301, " Moved Permanently\r\nLocation: " + req.get_oloc() + '/');
			return "";
		}
		there_is_an_index();
		CGI cgi(*this);
		generate_body(cgi.get_content(), 4, 201);
		generate_response(201, " Created");
		return "";
	}
	else if (ress_type == "file")
	{
		CGI cgi(*this);
		generate_body(cgi.get_content(), 4, 201);
		generate_response(201, " Created");
		return "";
	}
	return "";
}

std::string wbs::Response::put_method(std::string &loc)
{
	get_resource_type(loc);
	if (ress_type == "directory")
	{
		if (req.get_oloc().back() != '/')
		{
			generate_body(loc, 2, 301);
			generate_response(301, " Moved Permanently\r\nLocation: " + req.get_oloc() + '/');
			return "";
		}
		there_is_an_index();
		CGI cgi(*this);
		generate_body(cgi.get_content(), 4, 201);
		generate_response(201, " Created");
		return "";
	}
	else if (ress_type == "file")
	{
		CGI cgi(*this);
		generate_body(cgi.get_content(), 4, 201);
		generate_response(201, " Created");
		return "";
	}
	return "";
}

std::string wbs::Response::delete_method(std::string &loc)
{
	get_resource_type(loc);
	if (ress_type == "directory")
	{
		if (req.get_oloc().back() != '/')
		{
			generate_body(loc, 2, 301);
			generate_response(301, " Moved Permanently\r\nLocation: " + req.get_oloc() + '/');
			return "";
		}
		there_is_an_index();
		CGI cgi(*this);
		generate_body(cgi.get_content(), 4, 204);
		generate_response(204, " No Content");
		return "";
	}
	else if (ress_type == "file")
	{
		CGI cgi(*this);
		generate_body(cgi.get_content(), 4, 204);
		generate_response(204, " No Content");
		return "";
	}
	return "";
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

void wbs::Response::delete_file(std::string &file)
{
	if (!remove(file.c_str()))
	{
		generate_body(file, 2, 500);
		generate_response(500, " Internal Server Error");
		return;
	}
	generate_body(path, 1, 204);
	generate_response(204, " No Content");
}

std::string wbs::Response::get_cgi_path()
{
	DIR *dir = opendir("./cgi-bin/");
	if (dir != NULL)
	{
		struct dirent *entry;
		while ((entry = readdir(dir)) != NULL)
		{
			if (entry->d_type == DT_REG)
			{
				std::string f_name = entry->d_name;
				std::string cgi_path = "./cgi-bin/" + f_name;
				return (cgi_path);
			}
		}
	}
	return "";
}

void wbs::Response::set_env()
{
	std::map<std::string, std::string> heads = req.get_heads();
	int port = req.get_serv().port;
	std::stringstream ss;
	ss << port;

	if (heads.find("Auth-Scheme") != heads.end() && heads["Auth-Scheme"] != "")
		map_env.insert(std::make_pair("AUTH_TYPE", heads["Authorization"]));

	if (!req.get_up_dir().empty())
		map_env.insert(std::make_pair("UPLOAD_DIR", req.get_up_dir()));

	map_env.insert(std::make_pair("SERVER_PROTOCOL", "HTTP/1.1"));
	map_env.insert(std::make_pair("SERVER_PORT", ss.str()));
	map_env.insert(std::make_pair("CONTENT_TYPE", heads["Content-Type"]));
	map_env.insert(std::make_pair("CONTENT_LENGTH", length));
	map_env.insert(std::make_pair("PATH_INFO", req.get_loc()));
	map_env.insert(std::make_pair("PATH_TRANSLATED", req.get_loc()));
	map_env.insert(std::make_pair("REQUEST_METHOD", req.get_meth()));
	map_env.insert(std::make_pair("SERVER_NAME", "the Webrains on a Re\"Quest to Peasantria"));
	map_env.insert(std::make_pair("QUERY_STRING", req.get_query()));
	map_env.insert(std::make_pair("SCRIPT_NAME", path));
	map_env.insert(std::make_pair("SCRIPT_FILENAME", path));
	map_env.insert(std::make_pair("SCRIPT_PATH", path));
	map_env.insert(std::make_pair("REDIRECT_STATUS", "200"));
	map_env.insert(std::make_pair("GATEWAY_INTERFACE", "CGI/1.1"));
	map_env.insert(std::make_pair("REMOTE_IDENT", heads["Authorization"]));
	map_env.insert(std::make_pair("REMOTE_USER", heads["Authorization"]));
}

void wbs::Response::create_envp()
{
	envp_c = new char *[map_env.size() + 1];
	int i = 0;
	std::map<std::string, std::string>::iterator it;
	for (it = map_env.begin(); it != map_env.end(); ++it, ++i)
	{
		std::string str = it->first + "=" + it->second;
		envp_c[i] = new char[str.size() + 1];
		std::strcpy(envp_c[i], str.c_str());
	}
	envp_c[i] = NULL;
}

void wbs::Response::free_envp()
{
	for (int i = 0; envp_c != 0; i++)
	{
		delete[] envp_c[i];
	}
	delete[] envp_c;
	envp_c = NULL;
}

char **&wbs::Response::get_envi_var()
{
	set_env();
	create_envp();
	return envp_c;
}

void wbs::Response::print_env()
{
	for (int i = 0; envp_c[i] != NULL; i++)
	{
		std::cout << envp_c[i] << std::endl;
	}
}

void wbs::Response::start_resp()
{
	path = req.get_loc();
	std::string codemsg = req.get_codemsg();
	std::string method = req.get_meth();
	code = req.get_code();

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
			try
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
				case 4:
					put_method(path);
					break;
				}
			}
			catch (const std::exception &e)
			{
				generate_body(path, 2, 500);
				generate_response(500, " Internal Server Error");
			}
		}
	}
}

const std::string &wbs::Response::get_response()
{
	return response;
}

const std::string &wbs::Response::get_path()
{
	return path;
}

wbs::Request &wbs::Response::get_req()
{
	return req;
}
