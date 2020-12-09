
#include "processor.h"


void Processor::add(jobList j, int cpu_num, int currentTime, ofstream& logFile)
{
    if (jobCount == 0) {
        currentJob = j;
        jobCount++;
        (*this).idleTime = 0;
        (*this).runTime = 0;
        active = true;
        logFile <<  "\nTime " << currentTime << ":- Begin Processing Job : " << j.jobNumber << " Job " << j.jobType << " : " << j.jobTypeNumber << " in CPU " << cpu_num + 1;
    }
}

bool Processor::isEmpty()
{
    if (jobCount == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool Processor::isComplete()
{
    if (currentJob.processingTime == 0) {

        (*this).remove();
        return true;
    }
    else {
        return false;
    }
}

void Processor::processJob(jobList j, int cpu_num, int currentTime, ofstream& logFile) {
    if (j.processingTime != 0) {
        currentJob.processingTime--;
        (*this).totalRunTime++;
    }
}


void Processor::remove()
{
    if (jobCount != 0) {
        active = false;
        currentJob = {};
        (*this).runTime = 0;
        jobCount--;
    }
}

