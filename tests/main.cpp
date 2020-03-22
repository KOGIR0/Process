#include "Process.h"
#include "ExceptionProcess.h"

#include <cstring>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    Process* p;
    try
    {
        p = new Process("./echo.out");
    }
    catch(PipeException& e)
    {
        std::cout << e.what() << std::endl;
    }
    catch(ForkException& e)
    {
        std::cout << e.what() << std::endl;
    }

    char send[256], get[256];
    int n, k;
    while(std::cin>>send)
    {
        n = p->write(&send, sizeof(send));
        if(n != 0)
        {
            k = p->read(&get, n);
            std::cout<<get<<'\n';
        }
    }
    p->closeStdin();
    return 0;
}
