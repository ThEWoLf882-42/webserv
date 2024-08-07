/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:01:06 by agimi             #+#    #+#             */
/*   Updated: 2024/06/04 12:05:32 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

int checkEnd(const std::string &str, const std::string &end)
{
	if (str.size() < end.size())
		return 1;

	return str.compare(str.size() - end.size(), end.size(), end) != 0;
}

void cleankey(std::string &key)
{
	if (key[key.size() - 1] == ':')
		key.erase(key.size() - 1);
}

void cleanval(std::string &val)
{
	if (val[val.size() - 1] == '\r')
		val.erase(val.size() - 1);
}

std::string readfile(std::string path)
{
	std::string bo;
	std::ifstream file(path, std::ios::binary);

	if (!file.is_open())
	{
		return "";
	}

	try
	{
		file.seekg(0, std::ios::end);
		std::streampos fileSize = file.tellg();
		file.seekg(0, std::ios::beg);

		bo.reserve(fileSize);

		const size_t bufferSize = 1024 * 64;
		std::vector<char> buffer(bufferSize);

		while (!file.eof())
		{
			file.read(buffer.data(), bufferSize);
			bo.append(buffer.data(), file.gcount());
		}
	}
	catch (const std::exception &e)
	{
		return "";
	}
	return bo;
}

std::map<std::string, std::string> set_mime()
{
	std::map<std::string, std::string> mime;
	std::string dot;
	std::string type;
	std::ifstream file("./config/mime");
	if (!file.is_open())
	{
		std::cerr << "mime are zooooot" << std::endl;
		return mime;
	}
	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream s(line);

		s >> type >> dot;
		mime.insert(std::pair<std::string, std::string>(dot, type));
	}
	return mime;
}

std::string get_mime(const std::string &pat)
{
	std::string type;

	if (pat.find_last_of('.') != std::string::npos)
		type = pat.substr(pat.find_last_of('.'), pat.size());
	else
		type = ".html";
	if (wbs::Server::mime.find(type) != wbs::Server::mime.end())
		return wbs::Server::mime.find(type)->second;
	else
		return wbs::Server::mime.find(".html")->second;
}

bool AllowedChars(const std::string &str)
{
	const std::string allowedChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%";
	return str.find_first_not_of(allowedChars) == std::string::npos;
}

std::vector<std::string> list_directory(const std::string &directory)
{
	std::vector<std::string> files;
	DIR *dirp = opendir(directory.c_str());
	if (dirp != NULL)
	{
		struct dirent *dp;
		while ((dp = readdir(dirp)) != NULL)
		{
			if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
				files.push_back(dp->d_name);
		}
		closedir(dirp);
	}
	return files;
}

bool is_dir(const std::string &path)
{
	struct stat statbuf;
	if (stat(path.c_str(), &statbuf) != 0)
		return false;
	return S_ISDIR(statbuf.st_mode);
}

std::size_t get_file_size(const std::string &path)
{
	struct stat statbuf;
	if (stat(path.c_str(), &statbuf) != 0)
		return 0;
	return statbuf.st_size;
}

time_t get_last_modified_time(const std::string &path)
{
	struct stat statbuf;
	if (stat(path.c_str(), &statbuf) != 0)
		return 0;
	return statbuf.st_mtime;
}

std::string format_size(std::size_t size)
{
	std::stringstream ss;
	if (size < 1024)
		ss << size << " B";
	else if (size < 1024 * 1024)
		ss << std::fixed << std::setprecision(2) << size / 1024.0 << " KB";
	else if (size < 1024 * 1024 * 1024)
		ss << std::fixed << std::setprecision(2) << size / (1024.0 * 1024.0) << " MB";
	else
		ss << std::fixed << std::setprecision(2) << size / (1024 * 1024 * 1024) << " GB";
	return ss.str();
}

std::string format_time(time_t time)
{
	std::stringstream ss;
	struct tm *tm_info = localtime(&time);
	char buffer[20];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
	ss << buffer;
	return ss.str();
}

std::string autoindex(const std::string &directory, const std::string &location)
{
	std::string html = "<!DOCTYPE html>\n"
					   "<html>\n"
					   "<head>\n"
					   "    <title>Index of " +
					   location + "</title>\n"
								  "    <link rel=\"stylesheet\" type=\"text/css\" href=\"/assets/css/autoindex.css\">\n"
								  "</head>\n"
								  "<body>\n"
								  "    <div class=\"container\">\n"
								  "        <h1>Index of " +
					   location + "</h1>\n"
								  "        <hr>\n"
								  "        <div class=\"content\">\n"
								  "            <ul>\n"
								  "                <li><span class=\"icon\">&#128193;</span><a href=\"./\">.</a></li>\n"
								  "                <li><span class=\"icon\">&#128193;</span><a href=\"../\">..</a></li>";

	std::vector<std::string> files = list_directory(directory);
	std::sort(files.begin(), files.end());

	for (size_t i = 0; i < files.size(); ++i)
	{
		const std::string &file = files[i];
		std::string path = directory + '/' + file;
		bool is_directory = is_dir(path);
		std::string icon = is_directory ? "&#128193;" : "&#x1F517;";
		std::string name = is_directory ? "<span class=\"directory\">" + file + "/</span>" : "<span class=\"file\">" + file + "</span>";
		std::string size = is_directory ? "" : "<span class=\"file-info size\">" + format_size(get_file_size(path)) + "</span>";
		std::string time = is_directory ? "" : "<span class=\"file-info time\">" + format_time(get_last_modified_time(path)) + "</span>";
		html += "                <li><span class=\"icon\">" + icon + "</span><div><a href='" + location + (location.back() != '/' ? ('/' + file) : file) + "'>" + name + "</a></div><div class=\"file-info size\">" + size + "</div><div class=\"file-info time\">" + time + "</div></li>\n";
	}

	html += "            </ul>\n"
			"        </div>\n"
			"        <hr>\n"
			"        <div class=\"footer\">Generated by autoindex</div>\n"
			"    </div>\n"
			"</body>\n"
			"</html>";

	return html;
}
