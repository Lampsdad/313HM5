// Write a program that demonstrates reference counting on filesystem objects.
// should be written as a parent-child 
//The parent does the following:
// 1. opens an existing file for reading
// 2. forks so that the just opened fd for the file ia available in the child
// 3. closes and deletes the file. Use the unlink system call to delete the file.
// 4. verify that the file is no longer available using the ls command
// 5. sends a synchronization message to the child over a pipe so the child can now continue.

// When the child continues, it should do the following:
// still be able to read the file even though the file is (supposedly) deleted

// Solution:
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        // child
        char buf[1024];
        close(pipefd[1]);                  // close the write end of the pipe
        read(pipefd[0], buf, sizeof(buf)); // read the synchronization message
        close(pipefd[0]);                  // close the read end of the pipe

        size_t bytes_read = read(fd, buf, sizeof(buf));
        if (bytes_read == -1)
        {
            perror("read");
            return 1;
        }

        std::cout << "Child read: " << std::string(buf, bytes_read) << std::endl;
    }
    else
    {
        // parent
        if (close(fd) == -1)
        {
            perror("close");
            return 1;
        }

        if (unlink("test.txt") == -1)
        {
            perror("unlink");
            return 1;
        }

        if (system("ls -l test.txt") == -1)
        {
            perror("system");
            return 1;
        }

        close(pipefd[0]);            // close the read end of the pipe
        write(pipefd[1], "sync", 4); // write the synchronization message
        close(pipefd[1]);            // close the write end of the pipe
    }

    return 0;
}