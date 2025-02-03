#include "Cryption.hpp"
#include "../processes/Task.hpp"
#include "../fileHandling/ReadEnv.cpp"
#include <string>

int executeCryption(const std::string &taskdata)
{
    // to call static function it include className::functionName no need object
    Task task = Task::fromString(taskdata);
    ReadEnv env;

    std::string envKey = env.getenv(); // return string of env content
    int key = std::stoi(envKey);       // convert string to integer

    if (task.action == Action::ENCRYPT)
    {
        char ch;

        // here we need to get() each character from file stream and store it to "ch"
        // perform algorithm
        // then put() into file straem

        while (task.f_stream.get(ch))
        {
            ch = (ch + key) % 256;
            //  h e l l o
            //  ch

            // whenever read each character from file
            // the pointer shift to the right charcter
            // tell the stream to get back by 1(-1) step where you are curr(ios::cur)

            task.f_stream.seekp(-1, std::ios::cur);
            //  h e l l o
            // ch

            task.f_stream.put(ch);
            //  � e l l o
            //  ch
        }
        task.f_stream.close();
    }
    else
    {
        char ch;

        while (task.f_stream.get(ch))
        {
            // why +256 > This ensures the value stays positive when subtracting the key.
            ch = (ch - key + 256) % 256;

            task.f_stream.seekp(-1, std::ios::cur);
            task.f_stream.put(ch);
        }

        task.f_stream.close();
    }

    return 0;
}

/*
input:
    char c = 'h';
    char ch = (c + 12345)%256;
    char ch2 = (ch - 12345 + 256)%256;
    std::cout << ch << " " << ch2;
output:
    � h
*/