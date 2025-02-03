#include "ProcessManagement.hpp"
#include <iostream>
#include <cstring>
#include "../encryptDecrypt/Cryption.hpp"
// #include <sys/wait.h>

ProcessManagement::ProcessManagement() {}

bool ProcessManagement::submitToQueue(std::unique_ptr<Task> task)
{
    taskQue.push(std::move(task));
    return true;
}

// It consume task from queue and then proccess it
void ProcessManagement::executeTask()
{
    while (!taskQue.empty())
    {
        // taskToExecute is not a task it is just pointing to task
        std::unique_ptr<Task> taskToExecute = std::move(taskQue.front());

        // pop for the task which are ready to execute
        taskQue.pop();
        std::cout << "Executing task: " << taskToExecute->toString() << std::endl;

        // It takes task in serealized form(toString()) and deserialized(fromString()) and then process
        executeCryption(taskToExecute->toString());
    }
}