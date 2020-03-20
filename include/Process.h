#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <unistd.h>
#include <fstream>
#include <iostream>

class Process
{
public:
	explicit Process(const std::string& path);
	~Process();

	size_t write(const void* data, size_t len);
	void writeExact(const void* data, size_t len);
	size_t read(void* data, size_t len);
	void readExact(void* data, size_t len);

	bool isReadable() const;
	void closeStdin();

	void close();

	private:
		pid_t pid;
		int inProcfd[2];
		int outProcfd[2];
};
#endif //PROCESS_H
