#ifndef PERIODIC_TASK_H
#define PERIODIC_TASK_H

#include <functional>
#include <chrono>
#include <thread>
#include <atomic>
#include <vector>
#include <mutex>

class PeriodicTask {
public:
    using TaskFunction = std::function<void()>;

    // Constructor: Creates a periodic task with a given interval and task function.
    explicit PeriodicTask(double intervalInSeconds, const TaskFunction& taskFunc);

    // Destructor: Cleans up resources and stops the task.
    ~PeriodicTask();

    // Change the interval at which the task is executed.
    void ChangeInterval(double newIntervalInSeconds);

    // Remove the task, stopping its execution.
    void Remove();

private:
    // Function executed by the task's thread in a loop.
    void TaskLoop();

    TaskFunction m_taskFunc;
    std::thread m_taskThread;
    std::atomic<bool> m_running;
    double m_interval;
    std::mutex m_mutex;
};

class PeriodicTaskManager {
public:
    // Get the singleton instance of the task manager.
    static PeriodicTaskManager& GetInstance();

    // Add a new periodic task to the manager.
    void AddTask(double intervalInSeconds, const PeriodicTask::TaskFunction& taskFunc);

    // Remove a periodic task from the manager.
    void RemoveTask(PeriodicTask* task);
    std::vector<PeriodicTask*> m_tasks;

private:
    // Private constructor to enforce singleton pattern.
    PeriodicTaskManager();

    // Destructor to clean up resources.
    ~PeriodicTaskManager();

    std::mutex m_mutex;
};

#endif // PERIODIC_TASK_H

