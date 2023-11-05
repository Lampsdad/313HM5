#include <iostream>
#include <cstring>
#include <unistd.h> // For write function
using namespace std;

extern "C" int openr(const char *pathname); // Declare the external assembly function

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <pathname>" << std::endl;
        return 1;
    }

    const char *pathname = argv[1];

    int fileDescriptor = openr(pathname); // Call the assembly function
    cout << "File descriptor: " << fileDescriptor << endl;

    if (fileDescriptor == -1)
    {
        std::cerr << "Failed to open file " << pathname << std::endl;
        return 1;
    }

    char buffer[1024];
    int bytesRead;

    while ((bytesRead = read(fileDescriptor, buffer, sizeof(buffer))) > 0)
    {
        write(STDOUT_FILENO, buffer, bytesRead); // Write the contents to stdout
    }

    close(fileDescriptor); // Close the file when done

    return 0;
}