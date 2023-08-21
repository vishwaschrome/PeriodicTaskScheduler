#include "PeriodicTask.h"
#include <iostream>

// Sample periodic task functions
void Task1() {
    std::cout << "Task 1 executed!\n";
}

void Task2() {
    std::cout << "Task 2 executed!\n";
}

void Task3() {
    std::cout << "Task 3 executed!\n";
}

int main() {
    // Get the singleton instance of the task manager.
    PeriodicTaskManager& taskManager = PeriodicTaskManager::GetInstance();

    // Add periodic tasks with different intervals and functions.
    taskManager.AddTask(1.0, Task1);
    taskManager.AddTask(2.0, Task2);
    taskManager.AddTask(0.5, Task3);
    
    // Let tasks run for a certain duration.
    std::this_thread::sleep_for(std::chrono::seconds(15));

    // Change the interval of a task using the public method.
    taskManager.GetInstance().m_tasks[0]->ChangeInterval(1.5);

    // Let tasks run again.
    std::this_thread::sleep_for(std::chrono::seconds(10));

    // Remove tasks and clean up resources.
    taskManager.RemoveTask(taskManager.GetInstance().m_tasks[0]);
    taskManager.RemoveTask(taskManager.GetInstance().m_tasks[1]);
    taskManager.RemoveTask(taskManager.GetInstance().m_tasks[2]);

    return 0;
}

