#include "Process.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <cstring>

Process::Process(const std::string& path)
{
	if(pipe(inProcfd) == -1)      //pipe to get information
		throw("Failed creating inPipe");
	if(pipe(outProcfd) == -1)     //pipe to send information
		throw("Failed creating outPipe");
	
	pid = fork();
	if(pid == -1)
	    throw("Error in fork");
	if(pid == 0)    //child process
	{
		dup2(inProcfd[0], STDIN_FILENO);
		dup2(outProcfd[1], STDOUT_FILENO);
		::close(inProcfd[1]);                  //close write part of getting pipe
		::close(outProcfd[0]);                 //close read part of sending pipe

		execlp(path.c_str(), path.c_str(), (char*) NULL);
	}else  //parent procces
	{
		::close(inProcfd[0]);  //close read part of getting pipe
		::close(outProcfd[1]); //close write part of sending pipe
	}
}

size_t Process::write(const void* data, size_t len)
{
	return ::write(inProcfd[1], data, len);
}

void Process::writeExact(const void* data, size_t len)
{
	size_t n_len, nwrite;
	if(sizeof(data) < len)
	{
		n_len = sizeof(data);
	}else
	{
		n_len = len;
	}

	int flags = fcntl(inProcfd[1], F_GETFD);
	fcntl(inProcfd[1], F_SETFD, O_NONBLOCK);

	while(n_len > 0)
	{
		nwrite = ::write(inProcfd[1], data, n_len);
		if(nwrite > 0)
		{
			n_len -= nwrite;
		}
	}

	fcntl(inProcfd[1], F_SETFD, flags & ~O_NONBLOCK);
}

size_t Process::read(void* data, size_t len)
{
	return ::read(outProcfd[0], data, len);
}

void Process::readExact(void* data, size_t len)
{
	size_t read_len, nread;
	void* tmp_buf;
	char* data_read;
	if(len > sizeof(data))
	{
		read_len = sizeof(data);
	}else
	{
		read_len = len;
	}

	int flags = fcntl(outProcfd[0], F_GETFD);
	fcntl(outProcfd[0], F_SETFL, O_NONBLOCK);
	
	while(read_len > 0)
	{
		nread = ::read(outProcfd[0], tmp_buf, read_len);
		strcat(data_read, (char*)tmp_buf);
		if(nread > 0)
		{
			read_len -= nread;
		}
	}

	fcntl(outProcfd[0], F_SETFD, flags & ~O_NONBLOCK);
}

bool Process::isReadable() const
{
	return (fcntl(outProcfd[0], F_GETFD) < 0 && errno == EBADF);
}

void Process::closeStdin()
{
	::close(inProcfd[1]);
}

void Process::close()
{
	::close(inProcfd[1]);
	::close(outProcfd[0]);
}

Process::~Process()
{
	kill(pid, SIGTERM);
	int statlock;
	waitpid(pid, &statlock, WNOHANG);
}
