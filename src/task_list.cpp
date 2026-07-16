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

    if (isValidPriority(priority)) {
        task.priority = priority;

    } else {
        task.priority = 1;
    }

    task.completed = false;

    return task;
}

// Dynamically allocates a new TaskNode at the head of a list
void insertFront(TaskNode*& head, Task task) {
    TaskNode* newNode = new TaskNode;

    newNode->data = task;
    newNode->next = head;

    head = newNode;
}

// Returns the total number of nodes in a list
int countTasks(const TaskNode* head) {
    int count = 0;
    
    while (head != nullptr) {
        count++;
        head = head->next;
    }

    return count;
}

// Returns the first node that matches a given description, returns nullptr if none found
TaskNode* findTask(TaskNode* head, string description) {
    while (head != nullptr) {
        if (head->data.description == description) {
            return head;
    }
    
    head = head->next;}
    
    return nullptr;
}

// Marks a given task as complete, returns true upon success
bool markTaskComplete(TaskNode* head, string description) {
   TaskNode* taskNode = findTask(head, description);
   
    if (taskNode != nullptr) {
        taskNode->data.completed = true;
        return true;
    } 

    return false;
}

// Removes all completed tasks and returns the number of tasks removed
int removeCompletedTasks(TaskNode*& head) {
    int removed = 0; 

    // Handles completed tasks at the front of the list
    while (head != nullptr && head->data.completed) {
        TaskNode* temp = head;
        head = head->next;

        delete temp;
        removed++;
    }

    // Traverses the rest of the list and removes completed tasks
    TaskNode* current = head;

    while (current != nullptr && current->next != nullptr) {
        if (current->next->data.completed) { 
            TaskNode* temp = current->next;

    current->next = temp->next;
    delete temp; 
    removed++; 
        } else { 
            current = current->next;
        }
    }
    return removed;
}

// Deletes all nodes in a list and sets the head to nullptr
void clearTasks(TaskNode*& head) {
    while (head != nullptr) {
        TaskNode* temp = head;

        head = head->next;

        delete temp;
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
