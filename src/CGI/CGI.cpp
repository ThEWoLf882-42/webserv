/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:00:59 by mel-moun          #+#    #+#             */
/*   Updated: 2024/06/04 13:34:29 by mel-moun         ###   ########.fr       */
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

wbs::CGI::CGI(wbs::Response &response)
	: ext(0), _response(response)
{
	_path = response.get_path();
	try
	{
		execute_cgi();
		std::cerr << "CGI [" << content << "]" << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
}

wbs::CGI::~CGI()
{
}

void wbs::CGI::valid_extension()
{
	std::string extension = _path.substr(_path.find_last_of(".") + 1);
	if (extension != "py")
		throw std::runtime_error("Invalid extension of the script");
	if (access(_path.c_str(), R_OK | X_OK) == -1)
		throw std::runtime_error("File does not have the correct permissions");
}

void wbs::CGI::binary_path()
{
	_binary_path = "/usr/bin/python3";

	struct stat sb;
	if (stat(_binary_path.c_str(), &sb) == -1)
		throw std::runtime_error("No such binary file");
	if (S_ISDIR(sb.st_mode))
		throw std::runtime_error("It's a directory");
	if (access(_binary_path.c_str(), X_OK) == -1)
		throw std::runtime_error("Binary file is not executable");
}

void wbs::CGI::execution()
{
	pid = fork();

	if (pid == -1)
		throw std::runtime_error("Forking error");
	else if (pid == 0)
	{
		// if (_response.get_req().get_meth() == "POST")  //I SHOULD KNOW IF IT'S POST
		// {
		if (lseek(std_in, 0, SEEK_SET) == -1)
			throw std::runtime_error("lseek for stdin");
		if (dup2(std_in, STDIN_FILENO) == -1)
			throw std::runtime_error("dup2 for stdin");
		// }
		if (dup2(std_out, STDOUT_FILENO) == -1)
			throw std::runtime_error("Dup2 for STDOUT failure");
		args[0] = _binary_path.c_str();
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
		// if (!(WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS))
		// 	throw std::runtime_error("Error HERE");
	}
}

void wbs::CGI::take_output()
{
	r = 1;
	if (lseek(std_out, 0, SEEK_SET) == -1)
		throw std::runtime_error("lseek error");
	while (r > 0)
	{
		r = read(std_out, &c, 1);
		if (r == -1)
		{
			close(std_out);
			throw std::runtime_error("Error while reading from the pipe");
		}
		else if (r == 0)
			break;
		content += c;
	}
	close(std_out);
}

void wbs::CGI::execute_cgi()
{
	valid_extension();
	binary_path();
	setup_files();
	execution();
	take_output();
}

void wbs::CGI::setup_files()
{
	std_in = fileno(tmpfile());
	if (std_in == -1)
		throw std::runtime_error("Creating stdin file");
	write(std_in, _response.get_req().get_body().c_str(), _response.get_req().get_body().size()); // BODY FROM THE REQUEST
	lseek(std_in, 0, SEEK_SET);
	std_out = fileno(tmpfile());
	if (std_out == -1)
		throw std::runtime_error("Creating a stdout file");
}

std::string &wbs::CGI::get_content()
{
	return content;
}