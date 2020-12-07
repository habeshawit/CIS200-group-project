
#include "processor.h"



void Processor::add(jobList j, int cpu_num, int currentTime)
{
    if (jobCount == 0) {
        currentJob = j;
        jobCount++;
        (*this).idleTime = 0;
        cout << "\nTime " << currentTime << ":  Arrival: Overall Job : " << j.jobNumber << " Job " << j.jobType << " : " << j.jobTypeNumber << " Processing Time " << j.processingTime;

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

void Processor::processJob(jobList j, int cpu_num, int currentTime) {
    if ((*this).runTime == 0 && j.waitTime >= 0) {
        cout << "\nTime " << currentTime << ":- Begin Processing Job : " << j.jobNumber << " Job " << j.jobType << " : " << j.jobTypeNumber << " in CPU " << cpu_num + 1;
    }
    else if(j.arrivalTime == currentTime) {
        cout << "\nTime " << currentTime << ":- Begin Processing Job : " << j.jobNumber << " Job " << j.jobType << " : " << j.jobTypeNumber << " in CPU " << cpu_num + 1;
    }
    else {
        currentJob.processingTime--;
    }
}


void Processor::remove()
{
    currentJob = {}; 
    jobCount--;
    //return jobs[front];
}


//
//
//jobList Processor::pop()
//{
//    jobList tempJob = currentJob;
//    currentJob = {};
//    jobCount--;
//    cout << "popped off processor" << currentJob.jobType << currentJob.arrivalTime << currentJob.processingTime << endl;
//
//    return tempJob;
//
//}