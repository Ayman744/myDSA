#include <bits/stdc++.h>
using namespace std;
class Queue
{
public:
    // Maximum capacity of the queue
    int capacity {};
    // Index of the front element (dequeue from here)
    int front {0};
    // Index of the rear element (enqueue here)
    int rear {0};
    // Number of elements currently in the queue
    int addedElements{ };
    // Dynamic array to hold the elements of the queue
    int *arr{ };
    // Default constructor (empty queue)
    Queue() {};
    // Parameterized constructor to set the capacity and allocate array
    Queue(int capacity) : capacity(capacity)
    {
        arr = new int[capacity];  // Allocating memory for the queue
    }
    // Destructor to deallocate memory when the object is destroyed
    ~Queue()
    {
        delete[] arr;  // Avoid memory leaks
    }
    // Returns the next position in a circular manner
    int next(int pos)
    {
        ++pos;  // Move to the next position
        if (pos == capacity)  // Wrap around if the end of the array is reached
            pos = 0;
        return pos;
    }
    // Checks if the queue is empty
    bool isEmpty()
    {
        return addedElements == 0;  // Queue is empty when no elements are added
    }
    // Checks if the queue is full
    bool isFull()
    {
        return addedElements == capacity;  // Queue is full when the number of added elements equals capacity
    }
    // Adds an element to the rear of the queue
    void enQueue(int val)
    {
        assert(!isFull());  // Ensure the queue is not full
        arr[rear] = val;    // Insert the element at the rear index
        rear = next(rear);  // Update rear index (circularly)
        ++addedElements;    // Increment the count of added elements
    }
    // Removes an element from the front of the queue
    int deQueue()
    {
        assert(!isEmpty()); // Ensure the queue is not empty
        int deVal = arr[front];  // Retrieve the value at the front
        front = next(front);     // Update front index (circularly)
        --addedElements;         // Decrement the count of added elements
        return deVal;            // Return the dequeued value
    }
    // Displays the elements of the queue and its current state
    void display()
    {
        cout << "Front " << front << " - rear " << rear << "\t";
        if (isFull())
            cout << "full";
        else if (isEmpty()) {
            cout << "empty\n\n";  // Early exit if queue is empty
            return;
        }
        cout << "\n";

        // Traverse the queue from front to rear in a circular manner
        for (int cur = front, step = 0; step < addedElements; ++step, cur = next(cur))
            cout << arr[cur] << " ";
        cout << "\n\n";
    }
    // Returns the previous position in a circular manner
    int prev(int idx)
    {
        --idx;  // Move to the previous position
        if (idx == -1)  // Wrap around if the beginning of the array is reached
            idx = capacity - 1;
        return idx;
    }
    // Adds an element to the front of the queue
    void enQueueFront(int val)
    {
        assert(!isFull());  // Ensure the queue is not full
        front = prev(front);  // Update front index to previous position
        arr[front] = val;     // Insert the element at the new front index
        ++addedElements;      // Increment the count of added elements
    }
    // Removes an element from the rear of the queue
    int deQueueRear()
    {
        assert(!isEmpty());  // Ensure the queue is not empty
        rear = prev(rear);   // Update rear index to previous position
        int deVal = arr[rear];  // Retrieve the value at the rear
        --addedElements;        // Decrement the count of added elements
        return deVal;           // Return the dequeued value
    }
    // Returns the value at the front of the queue without removing it
    int frontVal()
    {
        assert(!isEmpty());  // Ensure the queue is not empty
        return arr[front];   // Return the value at the front
    }
};

