#include <iostream>
#include <fstream>
#include <random>
#include "processor.h"
#include "Queue.h"
#include <iomanip>
#include <string>

using namespace std;

void generateJobs(ofstream& inputFile);
void sortJobsbyArrival(vector<jobList>& jobs, ofstream& inputFile);
void updateCount(jobList& j);

Queue jobQ(4150);
int userInput;
int jobACount = 0;
int jobBCount = 0;
int jobCCount = 0;
int totalJobCount = 0;

int main() {
    ofstream outputFile("inputFile.txt", ios::out | ios::trunc);
    ifstream inputFile;
    inputFile.open("inputFile.txt");
    ofstream logFile;
    logFile.open("logFile.txt");

    int currentTime = 1;
    int totalCPUProcessingTIme = 0; 
    int highestQsize = 0;
    int totalCPUIdleTIme = 0; 
    int totalJobsCompleted = 0; 
    int maxJobsInQ = 0;  
    int totalWaitTime = 0;
    int maxJobsInQueue = 0; 
    float averageQSize = 0; 
    float averageWaitTime = 0; 

    int simulationTime = 500;
    
    generateJobs(outputFile);

    cout << "\nWelcome to the Simulation Program" << endl;

    do
    {
        cout << "\nEnter the number of processors you would like to use to run the simulation: ";
        cin >> userInput;

        if (userInput <= 0)
        {
            cout << "\nERROR: Invalid Input. Please enter a positive number." << endl;
        }
       
    } while (userInput < 1);


    //Dynamically allocate an array for the processor(s)
    Processor* CPU = new Processor[userInput];

    jobList j = jobQ.readFile(inputFile, currentTime);
     
    jobList nextFromQ = {};

    //Runs simulation for 500 time units, then an additional 9500 time units
    while (currentTime <= simulationTime) {
        
        for (currentTime; currentTime <= simulationTime; currentTime++) {

            while (currentTime == j.arrivalTime) {
                updateCount(j);
                logFile << "\nTime " << currentTime << ":  Arrival: Overall Job : " << j.jobNumber << " Job " << j.jobType << " : " << j.jobTypeNumber << " Processing Time " << j.processingTime;
                bool jobadded = false;

                //adds to CPU if any available
                for (int i = 0; i < userInput; i++)
                {
                    if (CPU[i].isComplete() && CPU[i].isEmpty() && jobQ.isEmpty()) {
                        CPU[i].add(j, i, currentTime, logFile);
                        jobadded = true;
                        break;
                    }
                }

                //adds to queue if all CPUs busy
                if (!jobadded && j.arrivalTime == currentTime) {
                    highestQsize = jobQ.enqueue(j, highestQsize); 
                    maxJobsInQ++;
                }

                //adds job from queue to CPU if CPU free
                if (!jobQ.isEmpty())
                {
                    for (int i = 0; i < userInput; i++) {
                        if (CPU[i].isEmpty() || CPU[i].isComplete()) {
                            nextFromQ = jobQ.dequeue(currentTime);
                            totalWaitTime = totalWaitTime + nextFromQ.waitTime;
                            CPU[i].add(nextFromQ, i, currentTime, logFile);
                            jobadded = true;
                            break;
                        }
                    }
                }

                //reads next job from input file
                j = jobQ.readFile(inputFile, currentTime);

            }
            for (int i = 0; i < userInput; i++) {
                if (!CPU[i].isComplete() || !CPU[i].isEmpty()) { 
                    if (CPU[i].runTime >= 0)
                        CPU[i].processJob(CPU[i].currentJob, i, currentTime, logFile);
                }
                else if (CPU[i].isEmpty() && !jobQ.isEmpty()) {
                    nextFromQ = jobQ.dequeue(currentTime);
                    totalWaitTime = totalWaitTime + nextFromQ.waitTime;
                    CPU[i].add(nextFromQ, i, currentTime, logFile);
                    CPU[i].processJob(CPU[i].currentJob, i, currentTime, logFile);
                    break;
                }
            }
            logFile << "\nTime " << currentTime << ": " << " Queue: " << jobQ.status();
            for (int p = 0; p < userInput; p++) {
                if (!CPU[p].isEmpty()) {
                    logFile << " CPU " << p + 1 << " Run Time: " << ++CPU[p].runTime << " ";
                }
                else {
                    logFile << " CPU " << p + 1 << " Idle Time: " << CPU[p].idleTime << " ";
                    CPU[p].idleTime++;
                    totalCPUIdleTIme++;
                }
            }
            averageQSize = averageQSize + ((jobQ.size() - averageQSize) / currentTime);

        }
        //Sum up the total time cpus have been processing
        for (int i = 0; i < userInput; i++) {
            totalCPUProcessingTIme = totalCPUProcessingTIme + CPU[i].totalRunTime;
        }

        totalJobsCompleted = totalJobCount - jobQ.size();

        for (int i = 0; i < userInput; i++)
        {
            if (!CPU[i].isComplete())
                totalJobsCompleted--;
        }

        if (maxJobsInQ != 0) {
            averageWaitTime = totalWaitTime / maxJobsInQ;
        }

        logFile << "\n----------------------------------------------------------------------------" << endl;
        logFile << "           Simulation Metrics With Time At: " << currentTime - 1 << " time units" << endl;
        logFile << "----------------------------------------------------------------------------" << endl;
        logFile << "\nNumber of processor(s) being used : " << userInput << endl;
        logFile << "Current queue size : " << jobQ.size() << endl;
        logFile << "Average queue size : " << averageQSize << endl;
        logFile << "Maximum jobs in queue : " << highestQsize << endl;
        logFile << "Total time jobs in queue : " << totalWaitTime << " time units" << endl;
        logFile << "Average time in queue : " << averageWaitTime << " time units" << endl;
        logFile << "Total number of jobs A arrived : " << jobACount << endl;
        logFile << "Total number of jobs B arrived : " << jobBCount << endl;
        logFile << "Total number of jobs C arrived : " << jobCCount << endl;
        logFile << "Total jobs completed : " << totalJobsCompleted << endl;
        logFile << "Total time CPU(s) were processing : " << totalCPUProcessingTIme << " time units" << endl;
        logFile << "Total time CPU(s) were idle : " << totalCPUIdleTIme << " time units" << endl;

        cout << "\n----------------------------------------------------------------------------" << endl;
        cout << "           Simulation Metrics With Time At: " << currentTime - 1 << " time units" << endl;
        cout << "----------------------------------------------------------------------------" << endl;
        cout << "\nNumber of processor(s) being used : " << userInput << endl;
        cout << "Current queue size : " << jobQ.size() << endl;
        cout << "Average queue size : " << averageQSize << endl;
        cout << "Maximum jobs in queue : " << highestQsize << endl;
        cout << "Total time jobs in queue : " << totalWaitTime << " time units" << endl;
        cout << "Average time in queue : " << averageWaitTime << " time units" << endl;
        cout << "Total number of jobs A arrived : " << jobACount << endl;
        cout << "Total number of jobs B arrived : " << jobBCount << endl;
        cout << "Total number of jobs C arrived : " << jobCCount << endl;
        cout << "Total jobs completed : " << totalJobsCompleted << endl;
        cout << "Total time CPU(s) were processing : " << totalCPUProcessingTIme << " time units" << endl;
        cout << "Total time CPU(s) were idle : " << totalCPUIdleTIme << " time units" << endl;
        
        simulationTime = 10000;
    }
    
    outputFile.close();
    logFile.close();
    return 0;
}

//Function to generate jobs randomly
void generateJobs(ofstream& outputFile)
{
    vector<jobList> jobs;
    int jobCount2 = 0;
    int jobCount = 0;

    jobList A = {'A'};
    jobList B = {'B'};
    jobList C = {'C'};
   
    for (int time = 0; time < 13000; time++) {

        //generate 2500 Type A jobs arriving every 4-6 time units of last A job
        if (A.jobTypeNumber < 2500) {
            A.arrivalTime = A.arrivalTime + 4 + rand() % 3;
            A.processingTime = 1 + rand() % 5;
            A.jobTypeNumber++;
            jobCount2++;
            A.jobNumber = ++jobCount;
            jobs.push_back(A);
        }

        //generate 1200 Type B jobs arriving every 9-11 time units of last B job
        if (B.jobTypeNumber < 1200) {
            B.arrivalTime = B.arrivalTime + 9 + rand() % 3;
            B.processingTime = 6 + rand() % 5;
            B.jobTypeNumber++;
            jobCount2++;
            B.jobNumber = ++jobCount;
            jobs.push_back(B);
        }

        //generate 450 Type C jobs arriving every 24-26 time units of last C job
        if (C.jobTypeNumber < 450) {
            C.arrivalTime = C.arrivalTime + 24 + rand() % 3; 
            C.processingTime = 9 + rand() % 5;
            C.jobTypeNumber++;
            C.jobNumber = ++jobCount;
            jobCount2++;
            jobs.push_back(C);
        }
    }
   
    sortJobsbyArrival(jobs, outputFile);
}

//Function to sort generated jobs by arrival time and add to text file
void sortJobsbyArrival(vector<jobList>& jobs, ofstream& outputFile) {
    //sort jobs vector by arrival time
    sort(jobs.begin(),jobs.end(),[](const jobList& j1, const jobList& j2) { return j1.arrivalTime < j2.arrivalTime; });

    //store sorted job list in file
    for (int i = 0; i < 4150; i++) {
        outputFile << jobs[i].jobType << setw(10) << jobs[i].arrivalTime << setw(10) << jobs[i].processingTime << endl;
    }
}

//Function to update the count of jobs that just arrived
void updateCount(jobList& j) {
    switch (j.jobType)
    {
    case 'A': 
    {
        jobACount++;
        totalJobCount++;
        j.jobTypeNumber = jobACount;
    }
        break;
    case 'B':
    {
        jobBCount++;
        totalJobCount++;
        j.jobTypeNumber = jobBCount;
    }
        break;
    case 'C':
    {
        jobCCount++;
        totalJobCount++;
        j.jobTypeNumber = jobCCount;
    }
        break;
    }

    j.jobNumber = jobACount + jobBCount + jobCCount;

}
