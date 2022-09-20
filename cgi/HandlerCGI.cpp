#include "HandlerCGI.hpp"

std::string HandlerCGI::getServerNameFromHost(const std::string& host) {

	std::string res;
	size_t pos = host.find(':');
	if (pos == std::string::npos)
		return host;
	res = host.substr(0, pos);
	return res;
}

std::string HandlerCGI::getPortFromHost(const std::string& host) {

	std::string res;
	size_t pos = host.find(':');
	if (pos == std::string::npos)
		return ("80");
	res = host.substr(pos + 1, host.length() - pos - 1);
	return res;
}

std::string HandlerCGI::getScriptFromPath(const std::string& path) {

	std::string res;
	size_t pos = path.rfind('/');
	res = path.substr(pos + 1, path.length() - pos - 1);
	return res;
}

std::string HandlerCGI::myToString(int num) {

	char buf[15];
	sprintf(buf, "%d", num);
	std::string res = std::string(buf);
	return res;
}

std::string HandlerCGI::form_env_string(std::string name, std::string param) {

	std::string res = name + "=" + param;
	return res;
}

std::vector<std::string> HandlerCGI::init_env(Connect *conn) {

	std::vector<std::string> res;
	res.push_back(form_env_string("SERVER_SOFTWARE", "JUM webserv/0.0.1"));
	res.push_back(form_env_string("GATEWAY_INTERFACE", "CGI/1.1"));
	res.push_back(form_env_string("SERVER_PROTOCOL", "HTTP/1.1"));
	res.push_back(form_env_string("SERVER_NAME", getServerNameFromHost(conn->head.get("host"))));
	res.push_back(form_env_string("SERVER_PORT", getPortFromHost(conn->head.get("host"))));
	res.push_back(form_env_string("REQUEST_METHOD", conn->head.get("method")));
	res.push_back(form_env_string("PATH_INFO", conn->head.get("uri")));
	res.push_back(form_env_string("PATH_TRANSLATED", conn->full_file_path));
	res.push_back(form_env_string("QUERY_STRING", conn->get_str));
	res.push_back(form_env_string("REMOTE_HOST", conn->head.get("host")));
	res.push_back(form_env_string("REMOTE_ADDR", getServerNameFromHost(conn->head.get("host"))));
	res.push_back(form_env_string("CONTENT_TYPE", conn->head.get("content-type")));
	res.push_back(form_env_string("CONTENT_LENGTH", std::to_string(conn->body.len())));
	res.push_back(form_env_string("REDIRECT_STATUS", "200")); //for php

	std::map<std::string, std::string> const head_data = conn->head.get_data();
	std::map<std::string, std::string>::const_iterator it = head_data.begin();
	while (it != head_data.end())
	{
		if (it->first != "host" && it->first != "method" && it->first != "uri" &&
				it->first != "content-type")
			res.push_back(form_env_string(Connect::key_to_cgi(it->first), it->second));
		it++;
	}

	return res;
}

char** HandlerCGI::form_env(std::vector <std::string>& arrEnv) {

	char** env = new char*[arrEnv.size() + 1];
	for (size_t i = 0; i < arrEnv.size(); ++i) {
		env[i] = new char[arrEnv[i].size() + 1];
		strcpy(env[i], arrEnv[i].c_str());
	}
	env[arrEnv.size()] = 0;
	return env;
}

std::string HandlerCGI::getInterpretator(Connect *conn) {

	std::string scriptName = getScriptFromPath(conn->full_file_path);
	size_t pos = scriptName.find('.');
	if (pos == std::string::npos)
		return std::string();
	std::string extension = scriptName.substr(pos, scriptName.length() -
	pos + 1);
	std::map<std::string, std::string>cgiInters = conn->location->getCGI();
	for (std::map<std::string, std::string>::iterator it = cgiInters.begin();
	it != cgiInters.end(); ++it) {
		if (it->first == extension) {
			return it->second;
		}
	}
	return std::string();
}

void	HandlerCGI::handleCGI(Connect* conn, std::string const
&path_interpritator, std::string& head, AContent* body)
{

	std::vector<std::string> envVec = init_env(conn);
	char** env = form_env(envVec);

	int fdIn[2];
	int fdOut[2];
	pipe(fdIn);
	pipe(fdOut);
	pid_t proc = fork();
	if (proc == 0) {
		if ((dup2(fdIn[0], 0)) < 0) {
			std::cerr << "dup error" << std::endl;
			exit(1);
		}
		if ((dup2(fdOut[1], 1)) < 0) {
			std::cerr << "dup error 2" << std::endl;
			exit(1);
		}		
		close(fdIn[0]);
		close(fdIn[1]);
		close(fdOut[0]);
		close(fdOut[1]);
		char* args[3];
		std::string script = conn->full_file_path;
		args[0] = const_cast<char*>(path_interpritator.c_str());
		args[1] = const_cast<char*>(script.c_str());
		args[2] = NULL;
		execve(args[0], args, env);
		exit (0);
	}
	ssize_t	read_len;
	size_t	write_len;
	RequestBody	content_buf;
	char	read_buf[4096];
	close(fdIn[0]);
	close(fdOut[1]);

	Content	buf;
	conn->body.write_data(&buf);
	bool	close_fd = 0;
	write_len = 0;
	if (Connect::down_str(conn->head.get("transfer-encoding")) != "chunked")
		fcntl(fdOut[0], F_SETFL, O_NONBLOCK);
	while ((write_len + (2 * 4096)) < buf.len())
	{
		if (write(fdIn[1], buf.get_content() + write_len, 4096) != 4096)
			throw (std::runtime_error("500"));
		write_len += 4096;
		read_len = read(fdOut[0], read_buf, 4096);		
		if (read_len > 0)
			content_buf.add(read_buf, read_len);
		else if (read_len == 0)
			close_fd = 1;
	}
	if (write(fdIn[1], buf.get_content() + write_len, buf.len() - write_len) != 
		static_cast<ssize_t>(buf.len() - write_len))
		throw (std::runtime_error("500"));

	close(fdIn[1]);
	read_len = read(fdOut[0], read_buf, 4096);
	while (read_len != 0 && close_fd == 0)
	{
		if (read_len > 0)
			content_buf.add(read_buf, read_len);
		read_len = read(fdOut[0], read_buf, 4096);
	}
	
	int status;
	waitpid(proc, &status, 0);
	close(fdOut[0]);


	if (WEXITSTATUS(status))
	{
		for (size_t i = 0; env[i]; i++) {
			delete[] env[i];
		}
		delete[] env;
		struct stat			_buf;
		std::ifstream		_file;
		if (stat(conn->full_file_path.data(), &_buf) == -1)
		{
			if (errno == ENOENT)
				throw (std::runtime_error("404"));
		}
		else
		{
			_file.open(conn->full_file_path.data());
			if (!_file.is_open())
				throw (std::runtime_error("403"));
			_file.close();
		}
		throw std::runtime_error("500");
	}

	head = "HTTP/1.1 200 OK\r\n";
	head += "Server: " + std::string("JUM webserv/0.0.1") + "\r\n";
	head += "Connection: keep-alive\r\n";

	if (content_buf.len() > 0)
	{
		std::string	str_head_cont = "";
		Content*	head_cont = content_buf.get_content(0);
		size_t	beg_str = 0;
		size_t	end_str = head_cont->find("\r\n");
		while (end_str != std::string::npos)
		{
			str_head_cont = std::string(head_cont->get_content() + beg_str, end_str - beg_str);
			if (str_head_cont.find("Status: ") != std::string::npos &&
				std::string(str_head_cont.data()+ 8, 3) != "200")
				throw std::runtime_error(std::string(str_head_cont.data()+ 8, 3));
			head += str_head_cont + "\r\n";			
			beg_str = end_str + 2;
			end_str = head_cont->find("\r\n", beg_str);
			if (beg_str == end_str)
				break;
		}
		if (beg_str)
			content_buf.cut(0, 0, end_str + 2);
	}
	content_buf.write_data(body);	

	for (size_t i = 0; env[i]; i++) {
		delete[] env[i];
	}
	delete[] env;
}
