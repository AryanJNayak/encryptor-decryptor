#include <iostream>
#include <filesystem>
#include "./src/app/processes/ProcessManagement.hpp"
#include "./src/app/Processes/Task.hpp"

namespace fs = std::filesystem;

int main(int argc, char *argv[])
{
    std::string directory;
    std::string action;

    std::cout << "Enter the directory path: ";
    std::getline(std::cin, directory);

    std::cout << "Enter the action (ENCRYPT/DECRYPT): ";
    std::getline(std::cin, action);

    try
    {
        // check the directory is exist or not and also check that it is directory not a file
        if (fs::exists(directory) && fs::is_directory(directory))
        {
            ProcessManagement processManagement;
            // recursive directory is iterator it will takes all the file withing dir/dir/dir also
            for (const auto &entry : fs::recursive_directory_iterator(directory))
            {
                // the encrypt/decrypt perform on regular file not system files
                if (entry.is_regular_file())
                {
                    std::string filePath = entry.path().string();          // path of that file
                    IO io(filePath);                                       // initalize stream for IO
                    std::fstream f_stream = std::move(io.getFileStream()); // get the file stream

                    // if file is correctly open
                    if (f_stream.is_open())
                    {
                        // assign action
                        Action act = (action == "ENCRYPT" ? Action::ENCRYPT : Action::DECRYPT);

                        // create task
                        auto task = std::make_unique<Task>(std::move(f_stream), act, filePath);

                        // add task to queue
                        processManagement.submitToQueue(std::move(task));
                    }
                    else
                    {
                        std::cout << "Unable to open file: " << filePath << std::endl;
                    }
                }
            }

            // execute all files
            processManagement.executeTask();
        }
    }
    catch (const fs::filesystem_error &ex)
    {
        std::cout << "Filesystem error: ";
        std::cerr << ex.what() << std::endl;
    }

    return 0;
}