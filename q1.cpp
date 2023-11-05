#include <iostream>
#include <string>
#include <fstream>

extern "C"
{
    int openr(const char *pathname);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <pathname>" << std::endl;
        return 1;
    }

    const char *pathname = argv[1];
    int result = openr(pathname);

    if (result == -1)
    {
        perror("openr");
        return 1;
    }

    return 0;
}