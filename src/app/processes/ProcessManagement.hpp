#ifndef PROCESS_MANAGEMENT_HPP
#define PROCESS_MANAGEMENT_HPP

#include "Task.hpp"
#include <queue>
#include <memory> //for unique_ptr

class ProcessManagement
{
private:
    // taskQue contains unique_ptr of Task
    
    std::queue<std::unique_ptr<Task>> taskQue;

public:
    ProcessManagement();
    bool submitToQueue(std::unique_ptr<Task> task);
    void executeTask();
};

#endif