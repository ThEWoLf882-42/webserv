/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responce.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:21:15 by fbelahse          #+#    #+#             */
/*   Updated: 2024/05/21 16:09:27 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>
#include <sys/stat.h>
#include <dirent.h>

wbs::Response::Response(Request &req): req(req)
{
	
}

wbs::Response::~Response(){}

void wbs::Response::print_map(std::map<const std::string, std::string>& map){
	for (std::map<const std::string, std::string>::const_iterator it = map.begin(); it != map.end(); ++it){
		std::cout << it->first.substr(2) << it->second << '\r\n';
	}
}

void wbs::Response::openf_f(){
	std::vector<std::string>vector;
	wbs::Request req();
	
	std::ifstream file(req().get_loc()); //loc
	std::string line;

	if (file.is_open()){
		while (std::getline(file, line)){
			vector.push_back(line);
		}
	}
	for (size_t i = 0; i < vector.size(); i++){
		std::cout << vector[i] << "\n";
	}
}

std::string::size_type find_char(const std::string &path, char thing){
	for (std::string::size_type i = path.size(); i > 0; --i){
		if (path[i - 1] == thing)
			return (i - 1);
	}
	return (std::string::npos);
}

bool wbs::Response::location_has_cgi(){
	wbs::Location loc;

	std::map<std::string, std::vector<std::string> >::iterator it;
	for (it = loc.get_params().begin(); it != loc.get_params().end(); ++it){
		std::string key = it->first;
		std::vector<std::string> vec = it->second;
		
		if (key == "cgi_extention"){
			std::vector<std::string>::iterator it_v;
			
			for (it_v = vec.begin(); it_v != vec.end(); ++it_v){
				if (std::find(vec.begin(), vec.end(), ".py") == vec.end())
					return (false);
				else
					return (true);
			}
		}
	}
	return (false);
}

int if_file(const std::string &path){
	struct stat s;

	std::string::size_type pos = find_char(path, '.');
    std::string ext = (pos != std::string::npos) ? path.substr(pos + 1) : "";
	
	if (stat(path.c_str(), &s) == 0){
		if (s.st_mode & S_IFREG)
			return (1);
		else if (ext == "html" || ext == "php"){
			return (1);	
		}
	}
	return (0);
}

bool if_supports_upload(){
	wbs::Location loc;
	std::string conf;

	std::map<std::string, std::vector<std::string> >::iterator it;
	for (it = loc.get_params().begin(); it != loc.get_params().end(); ++it){
		std::string key = it->first;
		std::vector<std::string> vec = it->second;

		if (key == "methods"){
			std::vector<std::string>::iterator it_v;
			for (it_v = vec.begin(); it_v != vec.end(); ++it_v){
				std::string method = *it_v;
				if (std::find(vec.begin(), vec.end(), "POST") == vec.end()){
					return (false);
				}
				else
					return (true);
			}
		}
	}
	return (true);
}

void wbs::Response::get_resource_type(const std::string &path){
	struct stat s;

	if ( stat(path.c_str(), &s) == 0){ //extract the resource info, which will contain if it's a dir/file (o_o;)?
		if (s.st_mode & S_IFDIR){ //st_mode field contains the file type and permissions for the file ~(^v^)~
			ress_type = "directory";
			return;
		}
		else if (s.st_mode & S_IFREG){
			ress_type = "file";
			return;
		}
		else{
			ress_type = "";
			return; 
		}
	}
	else{
		std::cout << ">>ERROR<<" << std::endl;
		return;
	}
}

//----------------RESP HEADER/BODY

void wbs::Response::get_cont_ty(std::string &url_tst){
	wbs::Request req();

	std::string token;
	std::string delim = "/";
	std::string sec_delim = ".";
	size_t pos = 0;
	if (!url_tst.empty() && url_tst[url_tst.size() - 1] == '/'){
		std::cout << "invalid url" << std::endl;
		return;
	}
	while ((pos = url_tst.find(delim)) != std::string::npos){
		token = url_tst.substr(0, pos);
		url_tst.erase(0, pos + delim.length());
	}
	file_name = url_tst;
	pos = 0;
	std::string tok;
	while ((pos = url_tst.find(sec_delim)) != std::string::npos){
        tok = url_tst.substr(0, pos);
        url_tst.erase(0, pos + sec_delim.length());
    }
	extention = url_tst;
}

std::string wbs::Response::mime_comp(){
	std::string line;
	std::ifstream mime("mime");
	if (mime.is_open()){
		while (std::getline(mime, line)){
			std::istringstream ln(line);
			std::string pth, exte;
			std::getline(ln, pth, '.');
			if (std::getline(ln, exte, '.')){
				if (extention.compare(exte) == 0){
					std::string::iterator end_pos = std::remove(pth.begin(), pth.end(), '\t');
					pth.erase(end_pos, pth.end());
					path = pth;
					break;
				}
			}
		}
	}
	return ("");
}

void wbs::Response::count_size(std::string &url){
	std::string body = readfile(url.c_str());
	std::stringstream s;

	s << body.size();
	std::string size = s.str();
	url += size + "\r\n\r\n";
	url += body;

	length = size;
}

void wbs::Response::get_file(std::string &url){
	std::string line;
	std::ifstream file(url);

	if (file.is_open()){
		while (std::getline(file, line)){
			vec.push_back(line);
		}
	}
	file.close();

	for (size_t i = 0; i < vec.size(); i++){
		std::cout << vec[i];
		std::cout << "\n";
	}
}

//--------------------CHECK

bool wbs::Response::check_auto_index(){
	wbs::Location loc;
	std::string conf;

	std::map<std::string, std::vector<std::string> >::iterator it;
	for (it = loc.get_params().begin(); it != loc.get_params().end(); ++it){
		std::string key = it->first;
		std::vector<std::string> vec = it->second;
		
		if (key == "autoindex"){
			std::vector<std::string>::iterator it_v;
			for (it_v = vec.begin(); it_v != vec.end(); ++it_v){
				std::string autoin = *it_v;
				if (std::find(vec.begin(), vec.end(), "off") == vec.end()){
					return (false);
				}
				else
					return (true);
			}
		}
	}
	return (false);
}

void wbs::Response::generate_response_headers(int code, const std::string &status){
	std::stringstream ss;

	ss << "HTTP/1.1" << " " << code << status << "\r\n"
		<< "Content-Type: " << path << "\r\n"
		<< "Content-Length" << length
		<< "\r\n\r\n"; 
}

int wbs::Response::check_meth(const std::string &method){
	if (method == "GET")
		return (1);
	else if (method == "POST")
		return (2);
	else if (method == "DELETE")
		return (3);
	return (0);
}

int wbs::Response::check_file(std::string &url){
	std::ifstream file(url);
	if (access(url.c_str(), F_OK) != 0){
		generate_response_headers(404, " Not Found");
		generate_body(url, 2, 404);
		return (0);
	}
	else if ((access(url.c_str(), R_OK) != 0 && access(url.c_str(), W_OK) != 0)
			|| (access(url.c_str(), R_OK)) != 0){
		generate_response_headers(403, " Forbidden");
		generate_body(url, 2, 403);
		return (0);
	}
	else if (check_auto_index()){
		generate_response_headers(403, " Forbidden");
		generate_body(url, 2, 403);
		return(0);
	}
	else if (check_meth(meth)){
		generate_response_headers(405, " Method Not Allowed");
		generate_body(url, 2, 405);
		return (0);
	}
	else if (!opendir(url.c_str())){
		generate_response_headers(404, " Not Found");
		generate_body(url, 2, 404);
		return (0);
	}
	else if (!access(url.c_str(), F_OK)){
		generate_response_headers(200, " OK");
		generate_body(url, 1, 200);
		return (1);
	}
	return (1);
}

//-----------------------

std::string generate_autoindex(){std::string index;return (index);}
std::string run_cgi(){}

bool there_is_an_index(){
	wbs::Infos inf;
	
	std::map<std::string, std::vector<std::string> >::iterator it;
	for (it = inf.get_directives().begin(); it != inf.get_directives().end(); ++it){
		std::string key = it->first;
		std::vector<std::string> vec = it->second;
		if (key == "default_file"){
			std::vector<std::string>::iterator it_v;
			
			for (it_v = vec.begin(); it_v != vec.end(); ++it_v){							
				if (std::find(vec.begin(), vec.end(), "index.html") == vec.end())
					return (false);
				else
					return (true);
			}
		}
	}
	return (false);
}

void wbs::Response::generate_body(std::string &url, int ind, int code){
	
	if (ind == 1 && (code == 200 || code == 201 || code == 204)){
		body = readfile(url.c_str());
		body += "\r\n";
	}
	else if (ind == 3 && code == 200){
		body =  autoindex(req.get_loc(), req.get_oloc());
		body += "\r\n";
	}
	else if (ind == 2 && code == 403){
		body = readfile("/Users/fbelahse/Desktop/webserv/extra/403.html");
		body += "\r\n";
	}
	else if (ind == 2 && code == 404){
		body = readfile("/Users/fbelahse/Desktop/webserv/extra/404.html"); 
		body += "\r\n";
	}
	else if (ind == 2 && code == 405){
		body = readfile("/Users/fbelahse/Desktop/webserv/extra/405.html");
		body += "\r\n";
	}
	else if (ind == 2 && code == 301){
		body = readfile("/Users/fbelahse/Desktop/webserv/extra/301.html");
		body += "\r\n";
	}
	else if (ind == 2 && code == 409){
		body = readfile("/Users/fbelahse/Desktop/webserv/extra/409.html");
		body += "\r\n";
	}
	else if (ind == 2 && code == 500){
		body = readfile("/Users/fbelahse/Desktop/webserv/extra/500.html");
		body += "\r\n";
	}
}

std::string wbs::Response::get_method(std::string &loc){
	get_req_resource(loc);
	get_resource_type(loc);
	if (ress_type == "directory"){
		if (loc[loc.size() - 1] != '/'){
			generate_response_headers(301, " Moved Permanently");
			generate_body(loc, 2, 301);
			loc += '/';
			return (loc);
		}
		else{
			if (there_is_an_index() == true){
				if (location_has_cgi()){
					//return code based on cgi (?)
				}
				else{
					if (check_auto_index() == true){
						generate_response_headers(200, " OK");
						generate_body(loc, 3, 200);
						return "";
					}
					else{
						generate_response_headers(403, " Forbidden");
						generate_body(loc, 2, 403);
						return "";
					}
				}
			}
			else{
				generate_response_headers(404, " Not Found");
				generate_body(loc, 2, 404);
				return "";
			}
		}
	}
	if (ress_type == "file"){
		if (location_has_cgi()){
			generate_response_headers(200, " OK");
			generate_body(loc, 1, 200);
			return "";
		}
		else{
			generate_response_headers(403, " Forbidden");
			generate_body(loc, 1, 403);
			return "";
		}
	}
	else
		return "";
}

std::string wbs::Response::post_method(std::string &loc){
	if (if_supports_upload()){
		generate_response_headers(201, " Created");
		generate_body(loc, 1, 201);
		return ("");
	}
	else{
		get_resource_type(loc);
		if (ress_type == "directory"){
			if (loc[loc.size() - 1] != '/'){
				generate_response_headers(301, " Moved Permanently");
				generate_body(loc, 2, 301);
				loc += '/';
				return (loc);
			}
			else{
				if (there_is_an_index()){
					if (location_has_cgi()){
						// run cgi
					}
					else{
						generate_response_headers(403, " Forbidden");
						generate_body(loc, 2, 403);
						return ("");
					}
				}
				else{
					generate_response_headers(403, " Forbidden");
					generate_body(loc, 2, 403);
					return ("");
				}
			}
			}
			if (ress_type == "file"){
				if (location_has_cgi()){
					// run cgi
				}
				else{
					generate_response_headers(403, " Forbidden");
					generate_body(loc, 2, 403);
					return ("");
				}
		}
		else{
			generate_response_headers(404, " Not Found");
			generate_body(loc, 2, 404);
			return ("");
		}
	}
}

void wbs::Response::delete_all_content(std::string &loc){
	DIR* dir = opendir(loc.c_str());
	if (dir == NULL){
		generate_response_headers(500, " Internal Server Error");
		generate_body(loc, 2, 500);
		return ;
	}
	
	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL){
		std::string f_name = entry->d_name;
		if (f_name != "." && f_name != ".."){
			std::string f_path = loc + f_name;
			if (remove(f_path.c_str()) != 0){
				generate_response_headers(500, " Internal Server Error");
				generate_body(loc, 2, 500);
				closedir(dir);
				return ;
			}
		}
	}
	closedir(dir);

	int count  = 0;
	dir = opendir(loc.c_str());
	struct dirent *ent;
	while ((ent = readdir(dir)) != NULL){
		std::string f_name = ent->d_name;
		if (f_name != "." && f_name != ".."){
			count++;
		}
	}
	closedir(dir);

	if (count == 0){
		generate_response_headers(204, " No Content");
		generate_body(loc, 1, 204);
		return ;
	}
	else{
		if (access(path.c_str(), W_OK) != 0 || access(path.c_str(), X_OK) != 0){
			generate_response_headers(403, " Forbidden");
			generate_body(loc, 2, 403);
			return ;
		}
		else{
			generate_response_headers(500, "Internal Server Error");
			generate_body(loc, 2, 500);
			return ;
		}
	}
	return ;
}

// get_req_res : readfile

std::string wbs::Response::delete_method(std::string &loc){
		get_req_resource(loc);
		get_resource_type(loc);
		if (ress_type == "directory"){
			if (loc[loc.size() - 1] != '/'){
				generate_response_headers(409, " Conflict");
				generate_body(loc, 2, 409);
				loc += '/';
				return (loc);
			}
			else{
				if (location_has_cgi()){
					if (there_is_an_index()){
						// run cgi
					}
					else{
						generate_response_headers(403, " Forbidden");
						generate_body(loc, 2, 403);
						return ("");
					}
				}
				delete_all_content(loc);
			}
			generate_response_headers(404, " Not Found");
			generate_body(path, 2, 404);
		}
		if (ress_type == "file"){
			if (location_has_cgi()){
				//3tiha l meriem :3
			}
			else
				delete_all_content(loc);
		}
	return ("");
}

void wbs::Response::start_tst(){
	std::string content = readfile(req.get_loc());
	std::string codemsg = req.get_codemsg();
	std::string method = req.get_meth();
	ver = req.get_ver();
	code = req.get_code();

	int check = check_file(content);
	if (check == 0){
		return;
	}
	else{
		switch(check_meth(method)) {
			case 1:
				get_method(content);
				break;
			case 2:
				post_method(content);
				break;
			case 3:
				delete_method(content);
				break;
		}
	}
}
