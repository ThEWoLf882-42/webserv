/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:00:59 by mel-moun          #+#    #+#             */
/*   Updated: 2024/05/30 18:30:03 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

wbs::CGI::CGI()
{
}

wbs::CGI::CGI(const std::string& path)
: _path(path) // initialize the binary path 
{
	// r = 1;
}

wbs::CGI::CGI(const CGI &ob)
{
	*this = ob;
}

wbs::CGI	&wbs::CGI::operator=(const CGI &ob)
{
	if (this != &ob)
	{
		std::cout << "choofoonniii " << std::endl;
		std::cout << "laaaaa " << std::endl;
	}
	return (*this);
}

wbs::CGI::~CGI()
{
}

// void	wbs::CGI::valid_extension(const std::string& path)
// {
// 	std::string extension = path.substr(path.find_last_of(".") + 1);
// 	if (extension != "py")
// 		throw std::runtime_error("Invalid extension of the script");
// 	if (access(path.c_str(), R_OK | X_OK) == -1)
// 		throw std::runtime_error("File does not exist"); // if its already done then remove it
// }

void	wbs::CGI::check_binary_path()
{
	// I should take the binary path first
	struct stat sb;
	
    if (stat(binary_path.c_str(), &sb) == -1)
		throw std::runtime_error("No such file");
    if (S_ISDIR(sb.st_mode))
		throw std::runtime_error("It's a directory");
	if (access(binary_path.c_str(), X_OK) == -1)
		throw std::runtime_error("Not executable");
}

void	wbs::CGI::execution()
{
	if (pipe(fd) == -1)
		throw std::runtime_error("Pipe error");
	pid = fork();
	if (pid == -1)
		throw std::runtime_error("Forking error");
	else if (pid == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			throw std::runtime_error("Dup2 for STDOUT failure");
		if (dup2(fd[0], STDIN_FILENO) == -1)
			throw std::runtime_error("Dup2 for STDIN failure");
		args[0] = binary_path.c_str();
		args[1] = _path.c_str();
		args[2] = NULL;
		if (execve(args[0], (char* const*)args, env) == -1)
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

void	wbs::CGI::take_output()
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

void	wbs::CGI::execute_cgi(const std::string& path)
{
	valid_extension(path);
	check_binary_path();
	execution();
	take_output();
}
