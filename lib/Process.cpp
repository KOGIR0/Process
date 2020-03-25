#include "Process.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <exception>
#include "ExceptionProcess.h"

Process::Process(const std::string& path) : canRead(true)
{
    int inProcfd[2], outProcfd[2];
    createPipes(inProcfd, outProcfd);

    pid = fork();
    if(pid == -1)
    {
	    closeFDs(inProcfd[0], inProcfd[1]);
		closeFDs(outProcfd[0], outProcfd[1]);
	    throw ForkException();
	}
	if(pid == 0)
	{
		dup2(inProcfd[0], STDIN_FILENO);
		dup2(outProcfd[1], STDOUT_FILENO);

		closeFDs(inProcfd[0], inProcfd[1]);
		closeFDs(outProcfd[0], outProcfd[1]);

		if(execlp(path.c_str(), path.c_str(), nullptr) == -1)
		{
			throw ExecException();
		}
	}else
	{
		parentToChild = inProcfd[1];
		childToParent = outProcfd[0];
		closeFDs(inProcfd[0], outProcfd[1]);
	}
}

void Process::closeFDs(int& fd1, int& fd2)
{
	::close(fd1);
	::close(fd1);
}

void Process::createPipes(int* inProcfd, int* outProcfd)
{
	if(pipe(inProcfd) == -1)
	    throw PipeException("Error creating inProcfd.");
	if(pipe(outProcfd) == -1)
	{
	    closeFDs(inProcfd[0], inProcfd[1]);
	    throw PipeException("Error creating outProcfd.");
	}
}

size_t Process::write(const void* data, size_t len)
{
	ssize_t ret_v = ::write(parentToChild, data, len);
	if(ret_v == -1)
	{
		throw WriteException();
	}

	return ret_v;
}

void Process::writeExact(const void* data, size_t len)
{
	size_t nwrite = 0;

	while(len != nwrite)
	{
		const void* buff = static_cast<const char*>(data) + nwrite;
		nwrite += write(buff, len - nwrite);
	}
}

size_t Process::read(void* data, size_t len)
{
	ssize_t ret_v = ::read(childToParent, data, len);

	if(ret_v == 0)
	{
		canRead = false;
	}
	
	if(ret_v == -1)
	{
		throw ReadException();
	}

	return ret_v;
}

void Process::readExact(void* data, size_t len)
{
	size_t nread = 0;

	while(nread != len)
	{
		void* begin = static_cast<char*>(data) + nread;
		nread += read(begin, len - nread);
	}
}

bool Process::isReadable() const
{
	return canRead;
}

void Process::closeStdin()
{
	::close(parentToChild);
}

void Process::close()
{
	closeFDs(childToParent, parentToChild);
	
	kill(pid, SIGTERM);
	waitpid(pid, NULL, WNOHANG);
}

Process::~Process()
{
	close();
}
