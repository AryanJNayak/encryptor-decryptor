#ifndef TASK_HPP
#define TASK_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <utility>

#include "../fileHandling/IO.hpp"

/*
enum and enum class are used to represent a set of named constant values.
They are commonly used to make your code more readable, maintainable, and type-safe.
*/
enum class Action
{
    ENCRYPT,
    DECRYPT
};

// to encrypt file following can be store insude Task:
// file path
// action (encrypt/decrypt)
// file stream
struct Task
{
    std::string filePath;
    std::fstream f_stream;
    Action action;

    // &&: allows you to bind to temporary objects, which
    // enabling move semantics (the ability to move resources from one object to another).

    // The "stream" variable only need to transfer coming stream to f-stream
    // after this we doesnot need the "stream" variable so we use && to declare
    // that this "stream" variable is not going to take memory its just to transfer data
    // move() used for efficient ownership transfer from one object to another object

    // we can directly assign the stream,act,filePath by doing this
    Task(std::fstream &&stream, Action act, std::string filePath) : f_stream(std::move(stream)), action(act), filePath(filePath) {}

    std::string toString()
    {
        std::ostringstream oss;

        // append data to string like file
        //  oss should be like this > C:/test/temp,DECRYPT
        oss << filePath << "," << (action == Action::ENCRYPT ? "ENCRYPT" : "DECRYPT");
        return oss.str();
    }

    static Task fromString(const std::string &taskData)
    {
        std::istringstream iss(taskData);

        // this is function variable not class variable so name should be same because it is static function
        std::string filePath;
        std::string actionStr;

        // get data from string like file
        // fist part until ',' assign to filePath and after ',' content assign to actionStr
        // ie: C:/test/temp,DECRYPT => filePath=C:/test/temp and actionStr=DECRYPT
        if (std::getline(iss, filePath, ',') && std::getline(iss, actionStr))
        {
            Action action = (actionStr == "ENCRYPT") ? Action::ENCRYPT : Action::DECRYPT;
            IO io(filePath);
            std::fstream f_stream = std::move(io.getFileStream()); // move ownsership

            if (f_stream.is_open())
            {
                // when we craete task which is execute we need to pass by reference not by value
                return Task(std::move(f_stream), action, filePath);
            }
            else
            {
                throw std::runtime_error("Failed to open file: " + filePath);
            }
        }
        else
        {
            throw std::runtime_error("Invalid task data format");
        }
    }
};

#endif