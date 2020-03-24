#include <unistd.h>
#include <iostream>
#include <cstdio>

int main()
{
    char buffer[256];
    while (!feof(stdin))
    {
        size_t msg_len;
        fread(&msg_len, sizeof(size_t), 1, stdin);
        fread(buffer, 1, msg_len, stdin);

        fwrite(&msg_len, sizeof(size_t), 1, stdout);
        fwrite(buffer, 1, msg_len, stdout);
        fflush(stdout);
    }

    return 0;
}