#include <unistd.h>
#include <iostream>
#include <cstdio>

int main()
{
    char buffer[256];
    while (!feof(stdin))
    {
        size_t bytes = read(STDIN_FILENO, buffer, sizeof(buffer));
        write(STDOUT_FILENO, buffer, bytes);
    }

    return 0;
}