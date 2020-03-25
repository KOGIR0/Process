#include "Process.h"
#include "ExceptionProcess.h"

#include <cstring>
#include <iostream>
#include <string>
#include <memory>

std::string send(std::shared_ptr<Process> p, size_t* msg_size)
{
    std::string send;
    try
    {
        std::cout << "Enter message: " << std::endl;
        std::cin >> send;
        *msg_size = send.size();
        p->writeExact(msg_size, sizeof(size_t));
        p->writeExact(send.c_str(), send.size());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return send;
}

std::string get(std::shared_ptr<Process> p, size_t& msg_size)
{
    char buffer[256];
    try
    {
        p->readExact(&msg_size, sizeof(size_t));
        p->readExact(&buffer, msg_size);

    }catch(ReadException& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return std::string(buffer);
}

int main(int argc, char *argv[])
{
    std::shared_ptr<Process> p;
    try
    {
        p = std::make_shared<Process>("./echo.out");
    }
    catch(PipeException& e)
    {
        std::cout << e.what() << std::endl;
    }
    catch(ForkException& e)
    {
        std::cout << e.what() << std::endl;
    }
    catch(ExecException& e)
    {
        std::cout << e.what() << std::endl;
    }

    while(!feof(stdin))
    {
        size_t send_msg_size;
        std::string s_str = send(p, &send_msg_size);
        std::cout << "Message send: " << s_str << " Message size: " << send_msg_size << std::endl;

        size_t got_msg_size;
        std::string g_str = get(p, got_msg_size);
        std::cout << "Message got: " << g_str << " Message size: " << got_msg_size << std::endl;
    }
    p->closeStdin();
    return 0;
}
