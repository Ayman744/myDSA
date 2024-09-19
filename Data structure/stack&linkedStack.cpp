#include <bits/stdc++.h>
using namespace std;
// Typedef defines a new name for the char type, which will be used to store stack elements
typedef char type;  // Stack will store `char` elements by default
class Stack //LIFO
{
private:
    int size{ };  // Holds the size (capacity) of the stack
    int top { };  // Index of the top element in the stack. -1 means the stack is empty
    type *array { };  // Pointer to dynamically allocated array that holds stack elements
public:
    // Constructor to initialize the stack with a given size
    Stack(int size) : size(size), top(-1)
    {
        // Dynamically allocate memory for the stack array
        array = new type[size];
    }
    // Destructor to free up the allocated memory when the stack is destroyed
    ~Stack()
    {
        delete[] array;
    }
    // Checks if the stack is full. A stack is full when the top reaches size - 1
    bool isFull()
    {
        return top == size - 1;
    }
    // Checks if the stack is empty. A stack is empty when top is -1
    bool isEmpty()
    {
        return top == -1;
    }
    // Function to print the contents of the stack from top to bottom
    void printStack()
    {
        for (int i = top; i >= 0; --i)
            cout << array[i] << " ";  // Print each element in the stack
        cout << endl;
    }
    // Pushes a new element to the top of the stack
    void push(type val)
    {
        // Ensure the stack is not full before pushing a new element
        assert(!isFull());
        array[++top] = val;  // Increment `top` and place the value at the new top
    }
    // Pops the top element from the stack and returns it
    type pop()
    {
        // Ensure the stack is not empty before popping an element
        assert(!isEmpty());
        return array[top--];  // Return the top element and decrement `top`
    }
    // Returns the top element of the stack without popping it
    type peak()
    {
        // Ensure the stack is not empty before accessing the top element
        assert(!isEmpty());
        return array[top];
    }
    // Reverses subwords in a sentence. Subwords are sequences of characters separated by spaces.
    string reverseSubwords(string line)
    {
        string res;  // Stores the final result
        line += ' ';  // Add a space at the end to handle the last word
        Stack st(line.size());  // Create a stack with size equal to the string length
        for (int i = 0; i < (int)line.size(); ++i)
        {
            if (line[i] == ' ')  // When a space is encountered, pop the stack to reverse the word
            {
                while (!st.isEmpty())
                    res += st.pop();  // Pop and append characters to result
                res += ' ';  // Add the space after the word is reversed
            }
            else
                st.push(line[i]);  // Push each character to the stack until a space is found
        }
        return res;  // Return the reversed subwords
    }
    // Reverses the digits of an integer
    int reverseNum(int num)
    {
        if (num == 0)
            return 0;
        Stack st(10);  // Create a stack to store digits (assuming max 10 digits)
        while (num)  // Push each digit onto the stack
            st.push(num % 10), num /= 10; //(%)get the last digit , (/)remove it

        int ten = 1;  // Multiplier to build the reversed number
        while (!st.isEmpty())  // Pop each digit and reconstruct the reversed number
            num = st.pop() * ten + num, ten *= 10;

        return num;  // Return the reversed number
    }
    // Removes adjacent duplicate characters from a string
    string removeDuplicates(string s)
    {
        stack<char> st;  // Use standard library stack (not the class above)
        for (auto ch : s)
        {
            if (!st.empty() && st.top() == ch)  // If top of stack matches current character, pop it (remove duplicate)
                st.pop();
            else
                st.push(ch);  // Otherwise, push the current character to the stack
        }
        s = "";  // Clear the original string
        while (!st.empty())  // Pop each character from the stack to rebuild the string without duplicates
            s = st.top() + s, st.pop();
        return s;  // Return the string without duplicates
    }
};

class StackLinked
{
private:
    struct Node
    {
        int data { };     // Stores the data of the node.
        Node* next { };   // Pointer to the next node in the linked list.
        // Constructor that initializes a node with the given data.
        Node(int data) :data(data)
        {
        }
    };
    Node *head { };  // The head pointer (or top of the stack).
public:
    ~StackLinked()
    {
        while (!isEmpty())  // Keep popping elements until the stack is empty.
            pop();
    }
    void printStack ()
    {
        for (Node *cur=head;cur;cur=cur->next)  // Traverse from head to the last node.
            cout<<cur->data<<" ";  // Print data for each node.
        cout<<endl;
    }
    bool isEmpty ()
    {
        return !head;  // If head is nullptr, the stack is empty.
    }
    void push (int val)
    {
        Node *itm=new Node(val);  // Create a new node with the provided value.
        itm->next=head;  // Point the new node's next to the current head.
        head=itm;  // Update head to the new node.
    }
    int pop ()
    {
        assert(!isEmpty());  // Ensure that the stack is not empty.
        int val=head->data;  // Retrieve the value from the top node.
        Node *tmp=head;  // Temporarily store the current head.
        head=head->next;  // Move the head pointer to the next node.
        delete tmp;  // Delete the old head node.
        return val;  // Return the popped value.
    }
    int peak ()
    {
        assert(!isEmpty());  // Ensure the stack is not empty.
        int element = head->data;  // Get the value at the top.
        return element;  // Return the top element without popping it.
    }
};
