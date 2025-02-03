#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

// use the functionality of IO
#include "IO.hpp"

// reads the content of a .env file and returns it as a string.
class ReadEnv
{
public:
    std::string getenv()
    {

        // The path is not ../../../.env because the .exe(main file) file is created in Encryption folder
        // .exe(main file) file not created in this folder
        std::string env_path = ".env";

        // store env file stream in io object
        // this env stream store in io.file_stream as it is implement in IO() constructor
        IO io(env_path);

        // store env stream in local variable using getFileStream()
        // it returns fstream object
        std::fstream f_stream = io.getFileStream();

        // Create a stringstream (buffer) to hold data temporarily
        // std::stringstream acts as an in-memory buffer that allows for both reading and writing operations, similar to file streams, but it works with strings.
        std::stringstream buffer;

        // rdbuf() retrieves the stream buffer of the file object.
        // The stream buffer is where the actual I/O operations occur when dealing with files or other streams.
        // It holds the raw data being read or written.
        // reading all the data from the file's internal buffer and writing it to the stringstream (buff).
        buffer << f_stream.rdbuf();

        //.str() converts the content of the stringstream (buff) into a std::string.
        std::string content = buffer.str();

        return content;
    }
};