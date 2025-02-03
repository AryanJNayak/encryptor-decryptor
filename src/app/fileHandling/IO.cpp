// implementation of IO class

#include <iostream>
#include <fstream>
#include <utility>
#include "IO.hpp";

// configuration using constructor
IO::IO(const std::string &file_path)
{
    /*
    open(path, open_modes)
    This line opens the file in the following modes:
    std::ios::in → for reading.
    std::ios::out → for writing.
    std::ios::binary → in binary mode (for non-text files like images, videos, etc.).
    */
    file_stream.open(file_path, std::ios::in | std::ios::out | std::ios::binary);

    // if an error while opening file_path
    if (!file_stream.is_open())
    {
        std::cout << "Unable to open the file: " << file_path << std::endl;
    }

    // if file is store then teh stream is stored in file_stream(private variable of IO class)
}

std::fstream IO::getFileStream()
{
    //move(): It allowing resources to be transferred from one object to another without copying.

    //transfer ownership of the file_stream object, which is a std::fstream instance.
    return std::move(file_stream);
}

IO::~IO()
{
    if (file_stream.is_open())
    {
        file_stream.close();
    }
}