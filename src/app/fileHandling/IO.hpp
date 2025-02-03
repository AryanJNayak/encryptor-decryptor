// This is "Header Guards" used for not include this file multiple times
#ifndef IO_HPP // Checks if IO_HPP is not defined.
#define IO_HPP // If not defined, it defines IO_HPP to prevent multiple inclusions of the same file.

#include <fstream>
#include <string>

class IO
{
private:
    // acts as a bridge between your program and the file
    std::fstream file_stream;

public:
    // It takes file_path (reference) to read/write on file_path
    // Pass the reference for unnecessary copy
    IO(const std::string &file_path);

    // cleanup code inside destructor
    ~IO();

    // return the file_stream
    std::fstream getFileStream();
};

#endif