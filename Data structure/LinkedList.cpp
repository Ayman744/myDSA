#include <bits/stdc++.h>
using namespace std;
struct Node {
    int data { };        // Holds the data for the node
    Node* next { };      // Pointer to the next node in the list
    // Constructor to initialize node with data and set next to nullptr
    Node(int data) : data(data) {}
};
class LinkedList
{
    Node *head { };      // Pointer to the first node in the list
    Node *tail { };      // Pointer to the last node in the list
    int length = 0;      // Tracks the number of nodes in the list
    // Debugging vector to track all nodes for verification (can be ignored)
    vector<Node*> debugData;
    // Debug function to add a node to the debug vector
    void debugAddNode(Node* node) {
        debugData.push_back(node);
    }
    // Debug function to remove a node from the debug vector
    void debugRemoveNode(Node* node) {
        auto it = find(debugData.begin(), debugData.end(), node);
        if (it == debugData.end())
            cout << "Node does not exist\n";
        else
            debugData.erase(it);
    }
    // Debug function to verify the integrity of the list
    void debugVerifyData() {
        if (length == 0) {
            assert(head == nullptr);   // If length is 0, head should be nullptr
            assert(tail == nullptr);   // If length is 0, tail should be nullptr
        } else {
            assert(head != nullptr);   // Non-empty list must have a head
            assert(tail != nullptr);   // Non-empty list must have a tail
            if (length == 1)
                assert(head == tail);  // If there's one node, head and tail must be the same
            else
                assert(head != tail);  // Otherwise, head and tail must be different
            assert(!tail->next);       // The tail's next pointer must be null
        }

        // Loop to verify the list length by traversing
        int len = 0;
        for (Node* cur = head; cur; cur = cur->next, len++)
            assert(len < 10000);       // To check for potential infinite loops
        assert(length == len);         // The calculated length must match the recorded length
        assert(length == (int)debugData.size());  // Debug size must match length
    }
    ///////////////////////////////////////
    LinkedList() {}
    ~LinkedList()
    {
        while (head)
        {
            Node *cur=head->next;
            head=cur;
        }
    }
    void print()
    {
        for (Node* cur = head; cur; cur = cur->next)
            cout << cur->data << " ";
        cout << "\n";
    }
// Function to delete a node (removes it from memory and debug tracking)
    void deleteNode(Node* node) {
        debugRemoveNode(node);  // Remove node from debug vector
        --length;               // Decrement the length of the list
        delete node;            // Free memory of the node
    }
    // Function to add a node to the list and track it in debug
    void addNode(Node* node) {
        debugAddNode(node);  // Add node to the debug vector
        ++length;            // Increment list length
    }
    // Insert a new node with a value at the end of the list
    void insertEnd(int value) {
        Node* item = new Node(value);  // Dynamically create a new node
        addNode(item);                 // Add the new node to the list

        if (!head)  // If the list is empty, set both head and tail to the new node
            head = tail = item;
        else {
            // Link the last node to the new node and update the tail
            tail->next = item;
            tail = item;
        }
    }
    // Delete the first node in the list
    void deleteFirst() {
        if (head) {  // If the list is not empty
            Node *cur = head;       // Store the current head
            head = head->next;      // Move the head to the next node
            deleteNode(cur);        // Delete the old head node
        }
        if (!head)   // If the list becomes empty, set tail to nullptr
            tail = nullptr;

        debugVerifyData();  // Verify list integrity after deletion
    }
    // Delete the last node in the list
    void deleteLast() {
        if (length <= 1) {   // If the list has 1 or 0 nodes, call deleteFirst()
            deleteFirst();
            return;
        }
        // Get the node before the last node
        Node *pre = getNth(length - 1);
        deleteNode(tail);  // Delete the current tail node
        tail = pre;        // Set the new tail
        tail->next = nullptr;  // Ensure the new tail's next pointer is null
        debugVerifyData();     // Verify list integrity
    }
    // Delete the node at a specific index
    void deleteNode(int idx) {
        if (idx < 0 || idx >= length) return;  // Index out of bounds check

        if (idx == 0) {
            deleteFirst();  // If the index is 0, delete the first node
        }
        if (idx == length - 1) {
            deleteLast();   // If the index is the last one, delete the last node
        }

        // Get the node before the one to be deleted
        Node *pre = getNthByIdx(idx - 1);
        Node* tmp = pre->next;    // Get the node to be deleted
        pre->next = tmp->next;    // Link the previous node to the next node, skipping the target
        delete tmp;               // Delete the target node
        length--;                 // Decrease the list length
    }
    Node* getNth(int n)
    {
        int cnt = 0;  // Initialize a counter to track the current node position
        for (Node* cur = head; cur; cur = cur->next)
        {  // Traverse the list from head
            if (++cnt == n)  // Increment count and check if we've reached the nth node
                return cur;  // Return the nth node if found
        }
        return nullptr;  // If n is out of bounds, return nullptr
    }
    Node* getNthByIdx(int idx)
    {
        if (idx <= 0 || idx >= length)  // Ensure the index is within valid bounds
            return nullptr;  // Return nullptr if the index is invalid
        Node* cur = head;  // Start traversal from the head node
        for (int i = 0; i < idx; ++i)
            cur = cur->next;  // Move to the next node `idx` times
        return cur;  // Return the node at the given index
    }
    void deletaNthNode(int n)
    {
        if (n < 1 || n > length)  // Ensure the nth node is within valid range
            cout << "Error. No such nth node\n";  // Print error if n is invalid
        if (n == 1)
            deleteFirst();  // Special case: If n is 1, simply delete the first node

        Node* beforeNth = getNth(n - 1);  // Get the node just before the nth node
        Node* nth = beforeNth->next;  // Get the nth node itself
        bool isTail = nth == tail;  // Check if the nth node is the tail

        beforeNth->next = nth->next;  // Link the previous node to the next node
        if (isTail)
            tail = beforeNth;  // If the nth node was the tail, update the tail

        deleteNode(nth);  // Delete the nth node
        debugVerifyData();  // Verify the list's integrity after deletion
    }
    void deleteNextNode(Node* node)
    {
        Node* toDelete = node->next;  // Get the next node to be deleted
        node->next = node->next->next;  // Link current node to the one after the next
        deleteNode(toDelete);  // Delete the next node
    }
    void emedAfter(Node *node, int val)
    {
        Node *itm = new Node(val);    // Create a new node with the value 'val'
        addNode(itm);                 // Add the new node to the linked list (for bookkeeping)
        itm->next = node->next;       // Link the new node's 'next' to the node that comes after 'node'
        node->next = itm;             // Update 'node's' next pointer to point to the new node
    }
    Node *getPrevious(Node *targeet)
    {
        // Start traversing the list from the head. Initialize two pointers:
        // 'cur' points to the current node in the list (starting at head),
        // 'prev' points to the previous node (initially nullptr because there's no node before the head).
        for (Node *cur = head, *prev = nullptr; cur; prev = cur, cur = cur->next) {

            // If the current node matches the target node (targeet),
            // return the previous node ('prev').
            if (cur == targeet)
                return prev;
        }
        // If we reached the end of the list without finding the target node,
        // return nullptr (meaning the target has no predecessor or doesn't exist in the list).
        return nullptr;
    }
    Node* moveToEnd(Node* cur, Node* pre) {
        // If the current node is already the tail, do nothing and return it
        if (cur == tail)
            return cur;
        // Save the next node of the current node
        Node *nex = cur->next;
        // Link the current node to the end of the list
        tail->next = cur;
        // If there's a previous node, link it to the next node of the current node
        if (pre)
            pre->next = nex;
        else
            // If there is no previous node, update the head to the next node (cur was the head)
            head = nex;
        // Move the current node to the tail
        tail = cur;
        // Set the new tail's next pointer to nullptr (as it's the end of the list now)
        tail->next = nullptr;
        // Return the next node to continue any iteration that was happening
        return nex;
    }
    void insertFront(int val)
    {
        // Create a new node with the given value 'val'
        Node *itm = new Node(val);
        // Add this node to the list, increasing the length and storing it in the debug data
        addNode(itm);
        // Point the new node's 'next' to the current head of the list
        itm->next = head;
        // Update the head of the list to be the new node
        head = itm;
        // If this is the first node being added (i.e., length == 1),
        // set both head and tail to point to the same node
        if (length == 1)
            tail = head;
        // Verify the internal consistency of the list for debugging purposes
        debugVerifyData();
    }
    void deleteFront() {
        // Ensure that the list is not empty
        assert(length);
        // Store the second node (next node after the head)
        Node *cur = head->next;
        // Delete the current head node
        deleteNode(head);
        // Update the head to be the second node (which is now the first node)
        head = cur;
        // Verify the internal structure of the list for debugging purposes
        debugVerifyData();
    }
    Node* getNthBack (int n)
    {
        if (length<n)
            return nullptr;
        return getNth(length - n + 1);
    //For example, if the list has 10 nodes and you want the 3rd node from the back,
    // that would be the 8th node from the front (length - n + 1 = 10 - 3 + 1 = 8).
    }
    bool isSame(const LinkedList &other)
    {
        // If the lengths of the two lists are not equal, they can't be the same
        if (length != other.length)
            return false;
        // Get a pointer to the head of the other list
        Node *otherHead = other.head;
        // Traverse the current list and compare each node's data with the corresponding node in the other list
        for (Node* curHead = head; curHead; curHead = curHead->next)
        {
            // If the data in the current node and the corresponding node in the other list differ, return false
            if (curHead->data != otherHead->data)
                return false;
            // Move to the next node in the other list
            otherHead = otherHead->next;
        }
        // If all nodes are the same, return true
        return true;
    }
    void removeWithKey (int key)
    {
        deleteNode(getNth(key));
    }
    void swapPairs()
    {
        for (Node* cur = head; cur; cur = cur->next->next) {  // Traverse the list in pairs
            if (cur->next)  // Ensure the next node exists (i.e., there is a pair to swap)
                swap(cur->data, cur->next->data);  // Swap the data between the current node and the next node
        }
    }
    void reverse()
    {
        if (length <= 1)
            return;  // No need to reverse if the list has 0 or 1 node
        tail = head;  // After reversal, the head will become the tail
        Node* prev = head;  // Keep track of the previous node
        head = head->next;  // Move the head to the second node
        while (head)
        {
            Node* next = head->next;  // Temporarily store the next node
            head->next = prev;  // Reverse the current node's next pointer
            prev = head;  // Move prev to the current node
            head = next;  // Move head to the next node
        }
        head = prev;  // After the loop, prev will be the new head
        tail->next = nullptr;  // Ensure the new tail points to nullptr

        debugVerifyData();  // Verify the list's integrity
    }
    void removeDuplicates() {

        if (length == 1)
            return;  // No duplicates possible in a list with one node
        for (Node* cur1 = head; cur1; cur1 = cur1->next)
        {  // Outer loop to select each node
            for (Node* cur2 = cur1->next, *prev = cur1; cur2;)
            {  // Inner loop to check for duplicates
                if (cur1->data == cur2->data)
                {  // If a duplicate is found
                    deleteNextNode(prev);  // Remove the duplicate node
                    cur2 = prev->next;  // Update cur2 to the next node after deletion
                }
                else
                {
                    prev = cur2;  // Move prev to cur2
                    cur2 = cur2->next;  // Move cur2 to the next node
                }
            }
        }

        debugVerifyData();  // Verify the list's integrity
    }
    int maxVal(Node* head_ = nullptr, bool first = true)
    {
        if (first)
            maxVal(head, false);  // If it's the first call, start with the real head of the list
        if (head == nullptr)
            return INT_MIN;  // If we've reached the end of the list, return the smallest possible integer
        return max(head->data, maxVal(head->next, false));  // Recursively compute the max value
    }
};