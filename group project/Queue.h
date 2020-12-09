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
    int processingTime =0;
    int jobNumber;
    int jobTypeNumber;
    int waitTime = 0;
};

typedef jobList ItemType;
class Queue {
public:
    Queue(int max);
    ~Queue();
    bool isEmpty() const;
    bool isFull() const;
    int enqueue(ItemType& job, int highestQSize);
    jobList dequeue(int time);
    jobList readFile(ifstream& inputFile, int time);
    string status();
    int size();
private:
    jobList* jobs = new jobList[4150];
    int front;
    int rear;
    int maxQue;
    int count;
    
};



