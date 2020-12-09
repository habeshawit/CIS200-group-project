#pragma once
#include "Queue.h"


class Processor
{
private:
    int jobCount = 0;
    
public:
    Processor() {};
    void add(jobList inputJob, int cpu_num, int currentTime, ofstream& logFile);
    void remove();
    bool isEmpty();
    bool isComplete();
    void processJob(jobList inputJob, int cpu_num, int currentTime, ofstream& logFile);
    int totalRunTime = 0;
    int idleTime = 0;
    int runTime= 0;
    bool active = false;
    jobList currentJob;

};

