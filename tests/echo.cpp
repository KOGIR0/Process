#include <unistd.h>
#include <iostream>
#include <cstdio>

int main()
{
    char buffer[256];
    while (!feof(stdin))
    {
        //size_t bytes = fread(buffer, 1, sizeof(buffer), stdin);
        //fwrite(buffer, 1, sizeof(buffer), stdout);
        size_t bytes = read(STDIN_FILENO, buffer, sizeof(buffer));
        write(STDOUT_FILENO, buffer, sizeof(buffer));
    }

    return 0;
}