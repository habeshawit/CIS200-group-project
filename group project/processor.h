#pragma once
//Processor.h
#include "Queue.h"

//int currentTime = 1;

class Processor
{
private:
    int jobCount = 0;
    
public:
    Processor() {};
    void add(jobList inputJob, int cpu_num, int currentTime);
    void remove();
    bool isEmpty();
    bool isFull();
    bool isComplete();
    void processJob(jobList inputJob, int cpu_num, int currentTime);
    int idleTime = 0;
    int runTime;
    jobList currentJob;
    jobList peekJob() { return currentJob; }
    //~Processor();
};

