#include "Queue.h"
#include "processor.h"

// Constructor to initialize queue
Queue::Queue(int max)
{
    //myQueue = new jobList[max];
    maxQue = max;
    front = 0;
    rear = -1;
    count = 0;
}

//function to read from input file and add to queue based on arrival time
jobList Queue::readFile(ifstream& inputFile, int time)
{
    jobList newJob[1];
    inputFile >> newJob[0].jobType >> newJob[0].arrivalTime >> newJob[0].processingTime;
    return newJob[0];
}

//Function to add job to front of queue
int Queue::enqueue(ItemType& j, int highestQsize)
{
        rear = (rear + 1) % maxQue;
        jobs[rear] = j;
        count++;
        if (highestQsize < count) {
            highestQsize = count;            
        }
        return highestQsize;
}

//Function to remove job from front of queue
jobList Queue::dequeue(int currentTime)
{
    // check for queue is empty
    if (isEmpty())
    {
        cout << "Error: There are no items in the queue\n";
        exit(EXIT_FAILURE);
    }

    jobList dequeueJob = jobs[front];
    dequeueJob.waitTime = currentTime - dequeueJob.arrivalTime;
    front = (front + 1) % maxQue;
    count--;
    return dequeueJob;
}

int Queue::size() {
    return count;
}

//Function to check if the queue is empty
bool Queue::isEmpty() const
{
    return (count == 0);
}

//Function to check if the queue is full
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
        return to_string(count) + " Jobs";
}