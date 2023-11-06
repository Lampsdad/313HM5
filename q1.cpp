#include <iostream>
#include <fcntl.h>
#include <unistd.h>

extern "C" int openr(const char *pathname);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <file>\n";
        return 1;
    }

    int fd = openr(argv[1]);
    if (fd == -1)
    {
        perror("openr");
        return 1;
    }

    char buffer[4096];
    ssize_t bytes;
    while ((bytes = read(fd, buffer, sizeof(buffer))) > 0)
    {
        write(STDOUT_FILENO, buffer, bytes);
    }

    close(fd);
    std::cout << std::endl;
    return 0;
}
