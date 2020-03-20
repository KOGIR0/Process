#include "Process.h"

#include <cstring>
#include <string>

int main(int argc, char *argv[])
{
    Process* p;
    try
    {
        p = new Process(argv[1]);
    }
    catch(std::string s)
    {
        std::cout << s;
    }

    char send[256], get[256];
    std::cout<<"Enter string: ";
    while(std::cin>>send)
    {
        int retCode, n, k;
        n = p->write(&send, sizeof(send));
        if(n != 0)
        {
            k = p->read(&get, n);
            std::cout<<get<<'\n';
        }
        std::cout<<"Enter string: ";
    }
    return 0;
}
