#include "PeriodicTask.h"

// PeriodicTask Implementation

PeriodicTask::PeriodicTask(double intervalInSeconds, const TaskFunction& taskFunc)
    : m_taskFunc(taskFunc), m_interval(intervalInSeconds), m_running(true) {
    // Start a thread to execute the task loop.
    m_taskThread = std::thread(&PeriodicTask::TaskLoop, this);
}

PeriodicTask::~PeriodicTask() {
    // Destructor: Stop the task and clean up the thread.
    Remove();
}

void PeriodicTask::ChangeInterval(double newIntervalInSeconds) {
    // Change the task interval.
    std::lock_guard<std::mutex> lock(m_mutex);
    m_interval = newIntervalInSeconds;
}

void PeriodicTask::Remove() {
    // Stop the task and wait for the thread to finish.
    m_running = false;
    if (m_taskThread.joinable()) {
        m_taskThread.join();
    }
}

void PeriodicTask::TaskLoop() {
    // Execute the task in a loop with the specified interval.
    while (m_running) {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_taskFunc();
        }
        std::this_thread::sleep_for(std::chrono::duration<double>(m_interval));
    }
}

// PeriodicTaskManager Implementation

PeriodicTaskManager& PeriodicTaskManager::GetInstance() {
    // Get the singleton instance of the task manager.
    static PeriodicTaskManager instance;
    return instance;
}

PeriodicTaskManager::PeriodicTaskManager() {}

PeriodicTaskManager::~PeriodicTaskManager() {
    // Destructor: Clean up resources and stop tasks.
    for (auto task : m_tasks) {
        task->Remove();
        delete task;
    }
}

void PeriodicTaskManager::AddTask(double intervalInSeconds, const PeriodicTask::TaskFunction& taskFunc) {
    // Add a new periodic task to the manager.
    std::lock_guard<std::mutex> lock(m_mutex);
    PeriodicTask* task = new PeriodicTask(intervalInSeconds, taskFunc);
    m_tasks.push_back(task);
}

void PeriodicTaskManager::RemoveTask(PeriodicTask* task) {
    // Remove a periodic task from the manager.
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = std::find(m_tasks.begin(), m_tasks.end(), task);
    if (it != m_tasks.end()) {
        (*it)->Remove();
        delete *it;
        m_tasks.erase(it);
    }
}

