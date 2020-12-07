#include "Queue.h"
#include "processor.h"

Processor* CPU = new Processor[3];
//int max = 4150;
//const int s = sizeof(jobList);

// Constructor to initialize queue
Queue::Queue(int max)
{
    jobs = new jobList[max];
    maxQue = max;
    front = 0;
    rear = -1;
    count = 0;
}

//function to read from input file and add to queue based on arrival time
jobList Queue::readFile(ifstream& inputFile2, int time)
{
   // int time = 0;
//    inputFile2.seekg(s * (jobs[time].jobNumber), ios::cur);
   // for (int i = 0; i < 4150; i++) {
        inputFile2 >> jobs[0].jobType >> jobs[0].arrivalTime >> jobs[0].processingTime;
       // for (time; time < 13000; time++) {
           // if(jobs[time].arrivalTime == time){
            //    cout << "TIME: " << time << " ";
                return jobs[0];
            //    (*this).enqueue(jobs[i]);
            //    break;
           // }
       // }
      // inputFile.clear();
    //}
        

}

//Function to add job to front of queue
void Queue::enqueue(ItemType& j)
{
    // check for queue is full
    if (isFull())
    {
        cout << "Cannot add job. The queue is full";
        return;
        //exit(EXIT_FAILURE);
    }

 /*   if ((*CPU).isEmpty())
    {
        (*CPU).add(item);
    }*/
    else {
        rear = (rear + 1) % maxQue;
        jobs[rear] = j;
        count++;
        //cout << "\nTime " << currentTime << ":  Arrival: Overall Job : " << j.jobNumber << " Job " << j.jobType << " : " << j.jobTypeNumber << " Processing Time " << j.processingTime;

    }

}

//Function to remove job from front of queue
jobList Queue::dequeue()
{
    // check for queue underflow
    if (isEmpty())
    {
        cout << "Error: There are no items in the queue\n";
        exit(EXIT_FAILURE);
    }

   // cout << "Removing " << jobs[front].jobType << '\n';
    jobList dequeueJob = jobs[front];
    front = (front + 1) % maxQue;
    count--;
    return dequeueJob;
}

//Function to return front element in the queue
int Queue::peek()
{
    if (isEmpty())
    {
        cout << "Error: The queue is empty\n";
        exit(EXIT_FAILURE);
    }
    return jobs[front].arrivalTime;
}

//Function to check if the queue is empty
bool Queue::isEmpty() const
{
    return (count == 0);
}

//Function to check of the queue is full
bool Queue::isFull() const
{
    return (count == maxQue);
}


Queue::~Queue()
{
    delete[] jobs;
}

string Queue::status() {
    if (count == 0) {
        return "Empty";
    }
    else
        cout << "Que SIZE: " << count << endl;
        return to_string(count) + " Jobs";
}