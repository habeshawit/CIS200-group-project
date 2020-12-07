#include <iostream>
#include <fstream>
#include <random>
#include "processor.h"
#include "Queue.h"
#include <iomanip>
#include <string>

//int size = 4150;
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

//Processor* CPU = new Processor[userInput];



int main() {
    ofstream inputFile("inputFile.txt", ios::out | ios::trunc);
    ifstream inputFile2;
    inputFile2.open("inputFile.txt");
    int currentTime = 1;

   
    generateJobs(inputFile);
   // jobQ.readFile(inputFile);

    cout << "\nWelcome to the Simulation Program" << endl;
    cout << "\nEnter the number of processors you would like to use to run the simulation: " << endl;
    cin >> userInput;

    //Dynamically allocate an array for the processor(s)
    Processor* CPU = new Processor[userInput];
    //int time = 1;
    jobList j = jobQ.readFile(inputFile2, currentTime);

    while (currentTime < 10000) {
        for (int i = 0; i < userInput; i++) { 

          //  bool repeatedTime = false;
            for (currentTime; currentTime <= j.arrivalTime|| !jobQ.isEmpty(); currentTime++) {

                bool jobadded = false;
                if (j.arrivalTime == currentTime) {
                    updateCount(j);

                    //check CPUs and add to unoccupied CPU
                    for (int p = 0; p < userInput; p++) {
                        if (CPU[p].isEmpty() || CPU[p].isComplete()) {
                          /*  if (!jobQ.isEmpty()) {
                                j = jobQ.dequeue();
                            }*/
                            CPU[p].add(j, p, currentTime);
                            jobadded = true;
                            break;
                        }
                    }
                    if (!jobadded ){
                        jobQ.enqueue(j);
                        jobadded = false;
                    }
                
                }
                //else {
                for (int x = 0; x < userInput; x++) {
                    if (!CPU[x].isEmpty() && !CPU[x].isComplete()) {
                        if(CPU[x].runTime !=0)
                        CPU[x].processJob(CPU[x].currentJob, x, currentTime);
                    }
                }
                    cout << "\nTime " << currentTime << ": " << " Queue: " << jobQ.status();
                    for (int p = 0; p < userInput; p++) {
                        if (!CPU[p].isEmpty() ) {

                            CPU[p].runTime = currentTime - CPU[p].currentJob.arrivalTime;
                            cout << " CPU " << p + 1 << " Run Time: " << currentTime - CPU[p].currentJob.arrivalTime << " ";
                        }
                        else {
                           cout << " CPU " << p + 1 << " Idle Time: " << CPU[p].idleTime << " ";
                           CPU[p].idleTime++;
                        }
                    }
         if (!jobQ.isEmpty()) {
                for (int p = 0; p < userInput; p++) {
                    if (CPU[p].isEmpty() || CPU[p].isComplete()) {
                        j = jobQ.dequeue();
                        j.waitTime = currentTime - j.arrivalTime;
                        CPU[p].runTime = 0;
                        CPU[p].add(j, p, currentTime);
                        CPU[p].processJob(CPU[p].currentJob, p, currentTime);
                        break;
                    }
                }
            }
         
            }

            if (jobQ.isEmpty()) {
                j = jobQ.readFile(inputFile2, currentTime);
                if (j.arrivalTime <= currentTime) {
                //    updateCount(j);
                currentTime = j.arrivalTime;
                //    break;
                //    //jobQ.enqueue(j);
                //    
                }
            }
            //}
        }
    }

    inputFile.close();
    return 0;
}


void generateJobs(ofstream& inputFile)
{
    vector<jobList> jobs;
    int jobCount = 0;

    jobList A = {'A'};
    jobList B = {'B'};
    jobList C = {'C'};
   
    for (int time = 0; time < 13000; time++) {

        //generate 2500 Type A jobs arriving every 4-6 time units of last A job
        if (time % 5 == 0 && A.jobTypeNumber < 2500) {
            A.arrivalTime = A.arrivalTime + 4 + rand() % 3;
            A.processingTime = 1 + rand() % 5;
            A.jobTypeNumber++;
            A.jobNumber = ++jobCount;
            jobs.push_back(A);
        }

        //generate 1200 Type B jobs arriving every 9-11 time units of last B job
        if (time % 10 == 0 && B.jobTypeNumber < 1200) {
            B.arrivalTime = B.arrivalTime + 9 + rand() % 3;
            B.processingTime = 6 + rand() % 5;
            B.jobTypeNumber++;
            B.jobNumber = ++jobCount;
            jobs.push_back(B);
        }

        //generate 450 Type C jobs arriving every 24-26 time units of last C job
        if (time % 25 == 0 && C.jobTypeNumber < 450) {
            C.arrivalTime = C.arrivalTime + 24 + rand() % 3; 
            C.processingTime = 11 + rand() % 5;
            C.jobTypeNumber++;
            C.jobNumber = ++jobCount;
            jobs.push_back(C);
        }
    }
    sortJobsbyArrival(jobs, inputFile);
    cout << A.jobTypeNumber + B.jobTypeNumber + C.jobTypeNumber << " jobs generated" << endl;
}

void sortJobsbyArrival(vector<jobList>& jobs, ofstream& inputFile) {
    //sort jobs vector by arrival time
    sort(jobs.begin(),jobs.end(),[](const jobList& j1, const jobList& j2) { return j1.arrivalTime < j2.arrivalTime; });

    //store sorted job list in file
    for (int i = 0; i < 4150; i++) {
        inputFile << jobs[i].jobType << setw(10) << jobs[i].arrivalTime << setw(10) << jobs[i].processingTime << endl;
    }
}

void updateCount(jobList& j) {
    switch (j.jobType)
    {
    case 'A': 
    {
        jobACount++;
        j.jobTypeNumber = jobACount;
    }
        break;
    case 'B':
    {
        jobBCount++;
        j.jobTypeNumber = jobBCount;
    }
        break;
    case 'C':
    {
        jobCCount++;
        j.jobTypeNumber = jobCCount;
    }
        break;
    }

    j.jobNumber = jobACount + jobBCount + jobCCount;

}
