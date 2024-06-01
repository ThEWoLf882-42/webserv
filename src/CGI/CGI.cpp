/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:00:59 by mel-moun          #+#    #+#             */
/*   Updated: 2024/06/01 12:36:46 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

wbs::CGI::CGI(const CGI &ob)
: _response(ob._response)
{
	*this = ob;
}

wbs::CGI &wbs::CGI::operator=(const CGI &ob)
{
	if (this != &ob)
	{
		std::cout << "choofoonniii " << std::endl;
		std::cout << "laaaaa " << std::endl;
	}
	return (*this);
}

wbs::CGI::CGI(wbs::Response& response) 
: _response(response)
{
	_path = response.get_path();
	try
	{
		execute_cgi(_path);
		std::cerr << "CGI [" << content << "]" <<std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	// std::map<std::string, wbs::Location> locs = response.get_infos().get_locations();
	// std::map<std::string, wbs::Location>::iterator loc_cgi = locs.find("cgi-bin");
	// std::map<std::string, std::vector<std::string> > pars = loc_cgi->second.get_params();
	// binary_path = pars["cgi_path"][0];
}

wbs::CGI::~CGI()
{
}

void	wbs::CGI::valid_extension(const std::string& path)
{
	std::string extension = path.substr(path.find_last_of(".") + 1);
	if (extension != "py" && extension != "php")
		throw std::runtime_error("Invalid extension of the script");
	if (access(path.c_str(), R_OK | X_OK) == -1)
		throw std::runtime_error("File does not exist");
	if (extension == "php")
		ext = 1;
}

void wbs::CGI::check_binary_path()
{
	struct stat sb;

	if (stat(binary_path.c_str(), &sb) == -1)
		throw std::runtime_error("No such file");
	if (S_ISDIR(sb.st_mode))
		throw std::runtime_error("It's a directory");
	if (access(binary_path.c_str(), X_OK) == -1)
		throw std::runtime_error("Not executable");
}

void wbs::CGI::execution()
{
	if (pipe(fd) == -1)
		throw std::runtime_error("Pipe error");
	pid = fork();
	if (pid == -1)
		throw std::runtime_error("Forking error");
	else if (pid == 0)
	{
		// if (dup2(fd[1], STDOUT_FILENO) == -1)
		// 	throw std::runtime_error("Dup2 for STDOUT failure");
		if (dup2(fd[0], STDIN_FILENO) == -1)
			throw std::runtime_error("Dup2 for STDIN failure");
		args[0] = binary_path.c_str();
		args[1] = _path.c_str();
		args[2] = NULL;
		if (execve(args[0], (char *const *)args, _response.get_envi_var()) == -1)
			throw std::runtime_error("Execve failure");
	}
	else
	{
		int status;
		if (waitpid(pid, &status, 0) == -1)
			throw std::runtime_error("Waitpid failure");
		if (!(WIFEXITED(status)))
			throw std::runtime_error("Error");
	}
}

void wbs::CGI::take_output()
{
	r = 1;
	while (r > 0)
	{
		r = read(fd[1], &c, 1);
		if (r == -1)
		{
			close(fd[0]);
			close(fd[1]);
			throw std::runtime_error("Error while reading from the pipe");
		}
		content += c;
	}
	close(fd[0]);
	close(fd[1]);
}


void wbs::CGI::execute_cgi(const std::string &path)
{
	valid_extension(path);
	default_binary_path();
	check_binary_path();
	execution();
	take_output();
}

void	wbs::CGI::default_binary_path()
{
	if (ext && binary_path.empty())
		binary_path = "/usr/bin/php";
	else
		binary_path = "/usr/bin/python3";
}
