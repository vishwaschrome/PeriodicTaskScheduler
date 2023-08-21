#include "gtest/gtest.h"
#include "../PeriodicTask.h"

// Test fixture for PeriodicTask
class PeriodicTaskTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up common resources before each test
    }

    void TearDown() override {
        // Clean up common resources after each test
    }
};

// Test basic PeriodicTask functionality
TEST_F(PeriodicTaskTest, BasicFunctionality) {
    bool taskExecuted = false;
    PeriodicTask::TaskFunction taskFunc = [&]() { taskExecuted = true; };
    PeriodicTask task(1.0, taskFunc);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    EXPECT_TRUE(taskExecuted);
}

// Test changing interval of PeriodicTask
TEST_F(PeriodicTaskTest, ChangeInterval) {
    int executionCount = 0;
    PeriodicTask::TaskFunction taskFunc = [&]() { executionCount++; };
    PeriodicTask task(1.0, taskFunc);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    task.ChangeInterval(0.5);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    EXPECT_GE(executionCount, 3); // Should execute at least 3 times
}

// Test removing a PeriodicTask
TEST_F(PeriodicTaskTest, RemoveTask) {
    int executionCount = 0;
    PeriodicTask::TaskFunction taskFunc = [&]() { executionCount++; };
    PeriodicTask task(1.0, taskFunc);

    task.Remove();

    std::this_thread::sleep_for(std::chrono::seconds(2));

    EXPECT_EQ(executionCount, 0); // Task should not be executed
}

// Test fixture for PeriodicTaskManager
class PeriodicTaskManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up common resources before each test
    }

    void TearDown() override {
        // Clean up common resources after each test
    }
};

/*
// Test adding and removing tasks from PeriodicTaskManager
TEST_F(PeriodicTaskManagerTest, AddAndRemoveTask) {
    PeriodicTaskManager& taskManager = PeriodicTaskManager::GetInstance();

    int executionCount = 0;
    PeriodicTask::TaskFunction taskFunc = [&]() { executionCount++; };
    
    taskManager.AddTask(1.0, taskFunc);
    taskManager.AddTask(0.5, taskFunc);

    std::this_thread::sleep_for(std::chrono::seconds(3));

    EXPECT_GE(executionCount, 5); // Should execute at least 5 times

    taskManager.RemoveTask(taskManager.m_tasks[0]);
    taskManager.RemoveTask(taskManager.m_tasks[1]);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    EXPECT_EQ(executionCount, 5); // Should not execute after removal
}*/

