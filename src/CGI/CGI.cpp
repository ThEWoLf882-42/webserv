/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:00:59 by mel-moun          #+#    #+#             */
/*   Updated: 2024/06/05 13:11:14 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

wbs::CGI::CGI(const CGI &ob) : _response(ob._response)
{
	*this = ob;
}

wbs::CGI &wbs::CGI::operator=(const CGI &ob)
{
	if (this != &ob)
	{
	}
	return (*this);
}

wbs::CGI::CGI(wbs::Response &response) : _response(response)
{
	_path = response.get_path();
	try
	{
		execute_cgi();
	}
	catch (const std::exception &e)
	{
		throw std::runtime_error("500 Internal Server Error");
	}
}

wbs::CGI::~CGI()
{
	if (std_in != -1)
		close(std_in);
	if (std_out != -1)
		close(std_out);
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
		if (dup2(std_in, STDIN_FILENO) == -1)
			_exit(EXIT_FAILURE);
		if (dup2(std_out, STDOUT_FILENO) == -1)
			_exit(EXIT_FAILURE);
		char *argv[] = {strdup(_binary_path.c_str()), strdup(_path.c_str()), NULL};
		if (execve(argv[0], argv, _response.get_envi_var()) == -1)
			_exit(EXIT_FAILURE);
	}
	else
	{
		int status;
		time_t start = time(NULL);

		while (waitpid(pid, &status, WNOHANG) == 0)
		{
			if (time(NULL) - start > 5)
			{
				kill(pid, SIGTERM);
				close(std_in);
				close(std_out);
				throw std::runtime_error("Child process timed out");
			}
		}
		close(std_in);
		close(std_out);
		if (!(WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS))
			throw std::runtime_error("Child process exited with error");
	}
}

void wbs::CGI::take_output()
{
	lseek(std_out, 0, SEEK_SET);

	char buffer[4096];
	ssize_t bytesRead;
	while ((bytesRead = read(std_out, buffer, sizeof(buffer))) > 0)
	{
		content.append(buffer, bytesRead);
	}
	if (bytesRead == -1)
	{
		close(std_out);
		content.clear();
		perror("Error while reading from the pipe");
		throw std::runtime_error("Error while reading from the pipe");
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
	write(std_in, _response.get_req().get_body().c_str(), _response.get_req().get_body().size());
	lseek(std_in, 0, SEEK_SET);
	std_out = fileno(tmpfile());
	if (std_out == -1)
		throw std::runtime_error("Creating a stdout file");
}

std::string &wbs::CGI::get_content()
{
	return content;
}
