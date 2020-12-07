#pragma once
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

struct jobList {
    char jobType = ' ';
    int arrivalTime = 0;
    int processingTime;
    int jobNumber;
    int jobTypeNumber;
    int waitTime = 0;
};


//class Queue
//{
//private:
//    jobList jobs[4150];
//    int jobCount = 0;
//public:
//    Queue() {};
//    void enqueue(fstream& inputFile);
//    //void add(jobList& inputJobs);
//    jobList pop();
//    //bool isEmpty();
//    //bool isFull();
//    //void print();
//    //int peekArrivalTime();
//    //void quickSort(int low, int high);
//    //void swap(jobList* a, jobList* b);
//    //int partition(int low, int high);
//    //int getCount() { return jobCount; }
//    //~jobStack();
//};

//
typedef jobList ItemType;
class Queue {
public:
    Queue(int max);
    ~Queue();
   // Queue();
    bool isEmpty() const;
    bool isFull() const;
    void enqueue(ItemType& job);
    jobList dequeue();
    jobList readFile(ifstream& inputFile2, int time);
    string status();
private:
    jobList* jobs;
    int front;
    int rear;
    int maxQue;
    int peek();
    int count;
    
};



