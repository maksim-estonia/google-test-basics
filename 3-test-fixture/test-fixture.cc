#include <iostream>
#include <cstdlib>
#include <gtest/gtest.h>
using namespace std;
 
// Define the default capacity of a queue
#define SIZE 1000
 
// A class to store a queue
class Queue
{
    int *arr;       // array to store queue elements
    int capacity;   // maximum capacity of the queue
    int front;      // front points to the front element in the queue (if any)
    int rear;       // rear points to the last element in the queue
    int count;      // current size of the queue
 
public:
    Queue(int size = SIZE);     // constructor
    ~Queue();                   // destructor
 
    int* dequeue();
    void enqueue(int x);
    int size();
    bool isEmpty();
    bool isFull();
};
 
// Constructor to initialize a queue
Queue::Queue(int size)
{
    arr = new int[size];
    capacity = size;
    front = 0;
    rear = -1;
    count = 0;
}
 
// Destructor to free memory allocated to the queue
Queue::~Queue() {
    delete[] arr;
}
 
// Utility function to dequeue the front element
int* Queue::dequeue()
{
    // check for queue underflow
    if (isEmpty())
    {
        //cout << "Underflow\nProgram Terminated\n";
        //exit(EXIT_FAILURE);
        return NULL;
    }
 
    int* x = &(arr[front]);
    cout << "Removing " << *x << endl;
 
    front = (front + 1) % capacity;
    count--;
 
    return x;
}
 
// Utility function to add an item to the queue
void Queue::enqueue(int item)
{
    // check for queue overflow
    if (isFull())
    {
        cout << "Overflow\nProgram Terminated\n";
        exit(EXIT_FAILURE);
    }
 
    cout << "Inserting " << item << endl;
 
    rear = (rear + 1) % capacity;
    arr[rear] = item;
    count++;
}
 
// Utility function to return the size of the queue
int Queue::size() {
    return count;
}
 
// Utility function to check if the queue is empty or not
bool Queue::isEmpty() {
    return (size() == 0);
}
 
// Utility function to check if the queue is full or not
bool Queue::isFull() {
    return (size() == capacity);
}

// TEST FIXTURE

class QueueTest : public ::testing::Test {
 protected:
  void SetUp() override {
     q1_.enqueue(1);
     q2_.enqueue(2);
     q2_.enqueue(3);
  }

  // void TearDown() override {}

  Queue q0_;    
  Queue q1_;
  Queue q2_;
};

// q0_ : contains zero elements
// q1_ : contains one element [1]
// q2_ : contains two elements [2,3]

TEST_F(QueueTest, IsEmptyInitially) {
  EXPECT_EQ(q0_.size(), 0); // q0_ should be empty
}

TEST_F(QueueTest, DequeueWorks) {
  int* n = q0_.dequeue();   // q0_ should be empty
  EXPECT_EQ(n, nullptr);    // thus the pointer returned should be empty

  n = q1_.dequeue();        // dequeue from q1
  ASSERT_NE(n, nullptr);    // this shouldn't be a nullptr
  EXPECT_EQ(*n, 1);         // the value of the pointer should be 1
  EXPECT_EQ(q1_.size(), 0); // the size of q1

  n = q2_.dequeue();        // dequeue from q2
  ASSERT_NE(n, nullptr);    // this shouldn't be a nullptr
  EXPECT_EQ(*n, 2);         // the value of the pointer should be 2
  EXPECT_EQ(q2_.size(), 1); // q2_ still contains one element
}




