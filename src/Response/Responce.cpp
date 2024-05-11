/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responce.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:21:15 by fbelahse          #+#    #+#             */
/*   Updated: 2024/05/10 16:35:17 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>
#include <sys/stat.h>
#include <dirent.h>

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

std::string wbs_r::Response::mime_comp(){
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

void wbs_r::Response::count_size(std::string &url){
	std::string line;
	size_t con_len = 0;
		std::ifstream file(url);
		if (file.is_open()){
			while (std::getline(file, line)){
				con_len += line.size() + 1;
			}
	}
	length = con_len;
} //binary files

int wbs_r::Response::check_file(std::string &url){
	std::ifstream file(url);
	if (access(url.c_str(), F_OK) != 0){
		code = 404;
		status = "Not Found";
		return (0);
	}
	else if ((access(url.c_str(), R_OK) != 0 && access(url.c_str(), W_OK) != 0)
			|| (access(url.c_str(), R_OK)) != 0){
		code = 403;
		status = " Forbidden";
		return (0);
	}
	else if (!access(url.c_str(), F_OK) && meth == "POST"){
		code = 201;
		status = " Created";
		return(1);
	}
	else if (!access(url.c_str(), F_OK)){
		code = 200;
		status = " OK";
		return (1);
	}
	return (2);
}

void wbs_r::Response::hund_(std::string &st){
	if (access(st.c_str(), F_OK)){
		code = 404;
		status = "Not Found";
	}
}

void wbs_r::Response::mapping(){
	wbs::Request req();

	std::string version = req().get_ver();
	std::stringstream aa;
	aa << code;
	std::string code = aa.str();
	const std::string prot = "1:" + version + code;
	std::string status = status;
	map.insert(std::make_pair(prot, status));

	std::stringstream ss;
	int val_len = length;
	ss << val_len;
	const std::string cntt_ln = "2:Content-Length: ";
	std::string val_lenn = ss.str();
	map.insert(std::make_pair(cntt_ln, val_lenn));

	const std::string cntt_type = "3:Content-Type: ";
	std::string type_val = path;
	map.insert(std::make_pair(cntt_type, type_val));

	print_map(map);
}

int wbs_r::Response::check_meth(const std::string &method){
	if (method == "GET")
		return (1);
	else if (method == "POST")
		return (2);
	else if (method == "DELETE")
		return (3);
	return (0);
}

void wbs_r::Response::get_file(std::string &url){
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

void wbs_r::Response::get_file_p(std::string &url, std::string s1){
	std::string line;
	std::ifstream file(url.c_str());
 
	if (file.is_open()){
	 	while (std::getline(file, line)){
			vec_p.push_back(line);
		}
		file.close();
	}

	for (size_t i = 0; i < vec_p.size(); i++){
		std::cout << vec_p[i];
		std::cout << "\n";
	}

	std::ofstream outfile(url.c_str());
	if (outfile.is_open()){
		for(std::vector<std::string>::iterator it = vec_p.begin(); it != vec_p.end(); ++it){
			outfile << *it << "\n";
		}
		outfile.close();
	}
}

void wbs_r::Response::openf_f(){
		std::vector<std::string>vector;
	std::ifstream file("/Users/fbelahse/Desktop/stuff/sub.html"); //loc
	std::string line;

	if (file.is_open()){
		while (std::getline(file, line)){
			vector.push_back(line);
		}
	}
	for (size_t i = 0; i < vector.size(); i++){
		std::cout << vector[i] << "\n";
	}
} //readfile

// void wbs_r::Response::uhhh(){
// 	std::ifstream file("/Users/fbelahse/Desktop/stuff/text.html");
// 	if (file.is_open()){
// 		openf_f();
// 	}
// 	file.close();
// }

//even before
int wbs_r::Response::check_code(){
	if (code == 200){
		return (1);	
	}
	return (0);
}

bool if_supp_upload(const std::string &path){return (true);}

bool supports_upload(const std::string &path){return (true);} //will ask if they are available. /(Q.Q/!)
void upload_req_body(const std::string &path){} //will upload the request body
bool get_req_ressource(){return (true);} //will get the request ressources
bool location_has_cgi(const std::string &path){return (true);}

int wbs_r::Response::get_ressource_type(const std::string &path){
	struct stat s;

	if ( stat(path.c_str(), &s) == 0){ //extract the ressource info, which will contain if it's a dir/file (o_o;)?
	
		if (s.st_mode & S_IFDIR){ //st_mode field contains the file type and permissions for the file ~(^v^)~
			std::cout << ">>DIRECTORY<<" << std::endl;
			ress_type = "directory";
			return (1);
		}
		else if (s.st_mode & S_IFREG){
			std::cout << ">>FILE<<" << std::endl;
			ress_type = "file";
			return (2);
		}
		else{
			ress_type = "";
			std::cout << ">>UNKNOWN<<" << std::endl;
			return (0); 
		}
	}
	else{
		std::cout << ">>ERROR<<" << std::endl;
		return (0);
	}
	return (0);
}

std::string::size_type find_char(const std::string &path, char thing){
	for (std::string::size_type i = path.size(); i > 0; --i){
		if (path[i - 1] == thing)
			return (i - 1);
	}
	return (std::string::npos);
}

int if_file(const std::string &path){
	struct stat s;

	std::string::size_type pos = find_char(path, '.');
    std::string ext = (pos != std::string::npos) ? path.substr(pos + 1) : "";
	
	if (stat(path.c_str(), &s) == 0){
		if (s.st_mode & S_IFREG)
			return (1);
		else if (ext == "html" || ext == "php" || ext == "cgi"){
			return (1);	
		}
	}
	return (0);
}

void wbs_r::Response::check_dir_file(const std::string &path){
	if ((!path.empty() && path[path.size() - 1] == '/') && ress_type == "directory"){
		DIR *dir = opendir(path.c_str());
		if (dir != NULL){
			struct dirent *entry;
			while ((entry = readdir(dir)) != NULL){
				if (if_file(entry->d_name)){
					dir_stats = 1;
					if (!location_has_cgi(path)){ //check in config file ".py"
						code = 403;
						status = " Forbidden";
						closedir(dir);
						//generate response
						return ;
					}
					closedir(dir);
				}
				else{
					code = 403;
					status = " Forbidden";
					dir_stats = -1;
					closedir(dir);
					//generate resp
					return;
				}
			}
			closedir(dir);
		}
		else if (dir == NULL){
			code = 404;
			status = " Not Found.";
			std::cout << "Error ( ò _ ó ) 💢" << std::endl;
			return ;
		}
	}
	else if (ress_type == "file"){
		if (!location_has_cgi(path)){
			code = 403;
			status = " Forbidden";
			return;
		}
	}
}

bool wbs_r::Response::post_resp(){
	std::string index_path("/Users/fbelahse/Desktop/stuff/");

	if (index_path.empty() || index_path[index_path.size() - 1] != '/'){
		code = 301;
		status = " Moved permanently + /";
		// return (false);
	}
	struct stat s;
	
	if (supports_upload(index_path)){
		upload_req_body(index_path);
		return (true);
	}
	else{
		if (get_req_ressource() == 0){
			get_ressource_type(index_path);
			check_dir_file(index_path);
			return (true);
		}
		else{
			code = 404;
			status = " Not Found.";
			return (false);
		}
	}
	return (false);
}

void wbs_r::Response::gen_resp(){
	std::string method;
	std::string url;
	std::string check;
	int code;

	if (check_meth(method) == 1){
		get_cont_ty(url);
		mime_comp();
		count_size(file_name);
		mapping();
		std::cout << "\r\n\r\n";
		get_file(file_name);
	}
}

void wbs_r::Response::start_tst(){
	wbs::Request req();

	std::string url = req().get_loc();
	std::string method = req().get_meth();
	ver = req().get_ver();
	int code = req().get_code();
	if (check_code == 0){
		status = " error";
		//generate response
		return ;
	}
	
	int check = check_file(url);
	if (check == 0){
		std::cout << code << " " << status << std::endl;
		return;
	}
	else if (check == 1){
		if (check_meth(method) == 1){
			get_cont_ty(url); 
			mime_comp();
			count_size(file_name);
			mapping();
			std::cout << "\r\n\r\n";
			get_file(file_name);
		}
		// else if (check_meth(method) == 2){
		// 	get_cont_ty(url); 
		// 	mime_comp();
		// 	count_size(file_name);
		// 	mapping();
		// 	std::cout << "\r\n\r\n";
		// 	check_dir_file(url);
		// 	uhhh();
		// }
	}
}
