#include "task_list.hpp"
#include <iostream>

using namespace std;

// Returns true if priority is from 1 to 5
bool isValidPriority(int priority) {
    return priority >= 1 && priority <= 5;
}

// Creates a new task, defaulting to priority 1 if the provided priority is invalid
Task createTask(string description, int priority) {
    Task task;

    task.description = description;
    task.completed = false;

    task.priority = isValidPriority(priority) ? priority : 1;
    
    return task;
}

// Dynamically allocates a new TaskNode at the head of a list
void insertFront(TaskNode*& head, Task task) {
    TaskNode* taskNode = new TaskNode;

    taskNode->data = task;
    taskNode->next = head;

    head = taskNode;
}

// Returns the total number of nodes in a list
int countTasks(const TaskNode* head) {
    int count = 0;

    const TaskNode* current = head;

    while (current != nullptr) {
        count++;
        current = current->next;
    }

    return count;
}

// Returns the first node that matches a given description, returns nullptr if none found
TaskNode* findTask(TaskNode* head, string description) {
    TaskNode* current = head;

    while (current != nullptr) {
        if (current->data.description == description) return current;

        current = current->next;
    }

    return nullptr;
}

// Marks a given task as complete, returns true upon success
bool markTaskComplete(TaskNode* head, string description) {
    TaskNode* targetNode = findTask(head, description);

    if (targetNode != nullptr) {
        targetNode->data.completed = true;
        return true;
    }

    return false;
}

// Removes all completed tasks and returns the number of tasks removed
int removeCompletedTasks(TaskNode*& head) {
    int removedCount = 0;

    // Case 1: Completed tasks at the head of the list
    while (head != nullptr && head->data.completed) {
        TaskNode* temp = head;
        head = head->next;
        delete temp;
        removedCount++;
    }

    // Case 2: Completed tasks inside the rest of the list
    TaskNode* current = head->next;
    TaskNode* previous = head;

    while (current != nullptr) {
        if (current->data.completed) {
            previous->next = current->next;

            TaskNode* temp = current;
            current = current->next;
            delete temp;

            removedCount++;
        } else {
            // No deletion, just moves both pointers forward
            previous = current;
            current = current->next;
        }
    }

    return removedCount;
}

// Deletes all nodes in a list and sets the head to nullptr
void clearTasks(TaskNode*& head) {
    TaskNode* current = head;

    while (current != nullptr) {
        TaskNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }

    head = nullptr;
}

// Prints all data of a single task
void printTask(const Task& task) {
    cout << task.description
         << " | priority " << task.priority
         << " | " << (task.completed ? "complete" : "not complete")
         << endl;
}

// Prints all data of all tasks in a given list
void printTasks(const TaskNode* head) {
    if (head == nullptr) {
        cout << "No tasks." << endl;
        return;
    }

    const TaskNode* current = head;

    while (current != nullptr) {
        printTask(current->data);
        current = current->next;
    }
}
