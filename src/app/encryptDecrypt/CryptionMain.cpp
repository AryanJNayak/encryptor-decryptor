#include <iostream>
#include "Cryption.hpp"

// standalone application executable no need other files
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Use: ./encrypt \"file_name, action{ENCRYPT/DECRYPT}\" " << std::endl;
        return 1;
    }
    executeCryption(argv[1]);
    return 0;
}