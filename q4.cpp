// Write a program that accepts user input for a file path and displays 
// the following metadata for the provided path: 
// whether the provided path corresponds to a file/pipe/symlink
// the permissions of the owner of the file

//use the lstat function and the struct stat data structure

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <pathname>" << std::endl;
        return 1;
    }

    const char *pathname = argv[1];
    struct stat buf;

    if (lstat(pathname, &buf) == -1)
    {
        perror("lstat");
        return 1;
    }

    std::cout << "File type: ";

    switch (buf.st_mode & S_IFMT)
    {
        case S_IFREG:
            std::cout << "regular file" << std::endl;
            break;
        case S_IFDIR:
            std::cout << "directory" << std::endl;
            break;
        case S_IFLNK:
            std::cout << "symbolic link" << std::endl;
            break;
        case S_IFIFO:
            std::cout << "FIFO/pipe" << std::endl;
            break;
        case S_IFSOCK:
            std::cout << "socket" << std::endl;
            break;
        case S_IFBLK:
            std::cout << "block device" << std::endl;
            break;
        case S_IFCHR:
            std::cout << "character device" << std::endl;
            break;
        default:
            std::cout << "unknown" << std::endl;
            break;
    }

    std::cout << "Permissions: ";

    if (buf.st_mode & S_IRUSR)
    {
        std::cout << "r" << std::endl;
    }
    else
    {
        std::cout << "-" << std::endl;
    }

    if (buf.st_mode & S_IWUSR)
    {
        std::cout << "w" << std::endl;
    }
    else
    {
        std::cout << "-" << std::endl;
    }

    if (buf.st_mode & S_IXUSR)
    {
        std::cout << "x" << std::endl;
    }
    else
    {
        std::cout << "-" << std::endl;
    }

    // print out the owner of the file
    std::cout << "Owner: " << buf.st_uid << std::endl;

    std::cout << std::endl;

    return 0;
}
