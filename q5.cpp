// Write a program to determine the maximum number of open files permitted by a process in your operating system.
// Repeatedly open a file until the open call results in an EMFILE error. Report the maximum number of files that
// were opened successfully.

// Solution:

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd = 0;
    int max_fd = 0;

    while (true)
    {
        fd = open("m.txt", O_RDONLY);
        if (fd == -1)
        {
            perror("open");
            break;
        }
        else
        {
            max_fd++;
            std::cout << "Current Open: " << max_fd << std::endl;
        }
    }
    std::cout << "Maximum number of open files: " << max_fd << std::endl;

    return 0;
}
