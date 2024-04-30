/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responce.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:21:15 by fbelahse          #+#    #+#             */
/*   Updated: 2024/04/30 17:31:34 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>
#include <sys/stat.h>

wbs_r::Response::Response()
{
	
}

wbs_r::Response::~Response(){}

void wbs_r::Response::print_map(std::map<const std::string, std::string>& map){
	for (std::map<const std::string, std::string>::const_iterator it = map.begin(); it != map.end(); ++it){
		std::cout << it->first.substr(2) << it->second << '\n';
	}
}

void wbs_r::Response::get_cont_ty(std::string &url_tst){
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
	respp_t.file_name = url_tst;
	pos = 0;
	std::string tok;
	while ((pos = url_tst.find(sec_delim)) != std::string::npos){
        tok = url_tst.substr(0, pos);
        url_tst.erase(0, pos + sec_delim.length());
    }
	respp_t.extention = url_tst; 
}

std::string wbs_r::Response::mime_comp(){
	std::string line;
	std::ifstream mime("mime");
	if (mime.is_open()){
		while (std::getline(mime, line)){
			std::istringstream ln(line);
			std::string pth, exte;
			std::getline(ln, pth, '.');
			if (std::getline(ln, exte, '.')){
				if (respp_t.extention.compare(exte) == 0){
					std::string::iterator end_pos = std::remove(pth.begin(), pth.end(), '\t');
					pth.erase(end_pos, pth.end());
					respp_t.path = pth;
					break;
				}
			}
		}
	}
	return ("");
}

void wbs_r::Response::count_size(std::string &url){
	std::string line;
	size_t con_len = 0;
		std::ifstream file(url);
		if (file.is_open()){
			while (std::getline(file, line)){
				con_len += line.size() + 1;
	if (tst == "application/html")
	{
		std::ifstream file("aaa.html");
		if (file.is_open())
		{
			while (std::getline(file, line))
			{
				con_len += line.size();
			}
	}
	respp_t.length = con_len;
}

int wbs_r::Response::check_file(std::string &url){
	std::ifstream file(url);
	if (access(url.c_str(), F_OK) != 0){
		respp_t.code = 404;
		respp_t.status = "Not Found";
		return (0);
	}
	else if ((access(url.c_str(), R_OK) != 0 && access(url.c_str(), W_OK) != 0)
			|| (access(url.c_str(), R_OK)) != 0){
		respp_t.code = 403;
		respp_t.status = " Forbidden";
		return (0);
	}
	else if (!access(url.c_str(), F_OK) && respp_t.meth == "POST"){
		respp_t.code = 201;
		respp_t.status = " Created";
		return(1);
	}
	else if (!access(url.c_str(), F_OK)){
		respp_t.code = 200;
		respp_t.status = " OK";
		return (1);
	}
	else if (respp_t.ver != 1.1){
		respp_t.code = 505;
		respp_t.status = " HTTP version not supported";
		return (0);
	}
	else if (!access(url.c_str(), F_OK)){
		
	}
	return (2);
}

void wbs_r::Response::hund_(std::string &st){
	if (access(st.c_str(), F_OK)){
		respp_t.code = 404;
		respp_t.status = "Not Found";
	}
}

void wbs_r::Response::mapping(){
	std::stringstream aa;
	aa << respp_t.code;
	std::string code = aa.str();
	const std::string prot = "1:HTTP/1.1 " + code;
	std::string status = respp_t.status;
	respp_t.map.insert(std::make_pair(prot, status));

	std::stringstream ss;
	int val_len = respp_t.length;
	ss << val_len;
	const std::string cntt_ln = "2:Content-Length: ";
	std::string val_lenn = ss.str();
	respp_t.map.insert(std::make_pair(cntt_ln, val_lenn));

	const std::string cntt_type = "3:Content-Type: ";
	std::string type_val = respp_t.path;
	respp_t.map.insert(std::make_pair(cntt_type, type_val));

	print_map(respp_t.map);
}

int wbs_r::Response::check_meth(){
	if (respp_t.meth == "GET")
		return (1);
	else if (respp_t.meth == "POST")
		return (2);
	else if (respp_t.meth == "DELETE")
		return (3);
	return (0);
}

void wbs_r::Response::get_file(std::string &url){
	std::string line;
	std::ifstream file(url);

	if (file.is_open()){
		while (std::getline(file, line)){
			respp_t.vec.push_back(line);
		}
	}
	file.close();

	for (size_t i = 0; i < respp_t.vec.size(); i++){
		std::cout << respp_t.vec[i];
		std::cout << "\n";
	}
}

void wbs_r::Response::get_file_p(std::string &url, std::string s1){
	std::string line;
	std::ifstream file(url.c_str());

	if (file.is_open()){
	 	while (std::getline(file, line)){
			respp_t.vec_p.push_back(line);
		}
		file.close();
	}

	for (size_t i = 0; i != respp_t.vec_p.size(); i++){
		if (respp_t.vec_p[i] == s1){
			respp_t.vec_p[i] = respp_t.n_str;
			break;
		}
	}

	for (size_t i = 0; i < respp_t.vec_p.size(); i++){
		std::cout << respp_t.vec_p[i];
		std::cout << "\n";
	}

	std::ofstream outfile(url.c_str());
	if (outfile.is_open()){
		for(std::vector<std::string>::iterator it = respp_t.vec_p.begin(); it != respp_t.vec_p.end(); ++it){
			outfile << *it << "\n";
		}
		outfile.close();
	}
}

void wbs_r::Response::openf(){
	std::vector<std::string>victor;
	std::ifstream file("/Users/fbelahse/Desktop/stuff/sub.html");
	std::string line;

	if (file.is_open()){
		while (std::getline(file, line)){
			victor.push_back(line);
		}
	}
	for (size_t i = 0; i < victor.size(); i++){
		std::cout << victor[i] << "\n";
	}
}

void wbs_r::Response::uhhh(){
	std::ifstream file("/Users/fbelahse/Desktop/stuff/text.html");
	if (file.is_open()){
		openf();
	}
	file.close();
}

//even before
int check_code(){
	if (respp_t.code == 200){
		return (1);	
	}
	return (0);
}

bool check_uri_dir(){
	std::string uri("/Users/fbelahse/Desktop/stuff/");

	if (uri.empty() || uri[uri.size() - 1] != '/'){
		respp_t.code = 301;
		respp_t.status = " Moved Permanently"; //links or records returning this response should be updated
		return false;
	}
	std::string index_file_path = uri + "index.html";

	struct stat s;
	if( stat(index_file_path.c_str(),&s) == 0 )
	{
		if( s.st_mode & S_IFDIR ){
			respp_t.code = 403;
			respp_t.status = " Forbidden";
			return false;
		}
		else if( s.st_mode & S_IFREG ){
			std::cout << "Im a file!" << std::endl;
		}
		else
			return (false);
	}
	else{
		std::cout << "Error!" << std::endl;
		return (false);
	}
	std::ifstream file(index_file_path.c_str());

	if (!file) {
		std::ofstream dir(index_file_path, std::ios::app);
		if (!dir){
			respp_t.code = 403;
			respp_t.status = " Forbidden";
			respp_t.loc = uri + "/";
			return (false);
		}
		else{
			respp_t.code = 403;
			respp_t.status = " Forbidden";
			return false;
		}
	}
	return true;
}

bool if_supp_upload(const std::string &path){
	std::string f_path = path + "/tstfile.tmp";
	std::ofstream tstfile(f_path.c_str());

	bool witab = tstfile.good();
	tstfile.close();
	remove(f_path.c_str());
	return (witab);
}

bool check_uri_dir_ver2(){
	std::string uri("/Users/fbelahse/Desktop/stuff/");

	if (uri.empty() || uri[uri.size() - 1] != '/'){
		respp_t.code = 301;
		respp_t.status = " Moved Permanently"; //links or records returning this response should be updated
		return false;
	}

	if (!if_supp_upload(uri)){
		respp_t.code = 403;
		respp_t.status = " Forbidden";
		return (false);
	}

	std::string index_file_path = uri + "index.html";
	std::ifstream file(index_file_path.c_str());

	if (!file) {
		std::ofstream dir(index_file_path, std::ios::app);
		if (!dir){
			respp_t.code = 403;
			respp_t.status = " Forbidden";
			respp_t.loc = uri + "/";
			return (false);
		}
		else{
			respp_t.code = 403;
			respp_t.status = " Forbidden";
			return (false);
		}
	}
	return (true);
}

void wbs_r::Response::start_tst(){
	respp_t.code = 0;
	respp_t.ver = 1.1;
	respp_t.extention = "";
	respp_t.loc = "";
	respp_t.meth = "GET";
	respp_t.length = 0;
	respp_t.path = "";

	respp_t.str = "";
	respp_t.n_str = "";

	std::string url("/Users/fbelahse/Desktop/stuff/text.html");
	if (check_code == 0){
		respp_t.status = " error";
		return ;
	}
	int check = check_file(url);
	if (check == 0){
		std::cout << respp_t.code << " " << respp_t.status << std::endl;
		return;
	}
	else if (check == 1){
		if (check_meth() == 1){
			get_cont_ty(url); 
			mime_comp();
			count_size(respp_t.file_name);
			mapping();
			std::cout << "\r\n";
			get_file(respp_t.file_name);
		}
		else if (check_meth() == 2){
			get_cont_ty(url); 
			mime_comp();
			count_size(respp_t.file_name);
			mapping();
			std::cout << "\r\n";
			uhhh();
		}
	}
}
