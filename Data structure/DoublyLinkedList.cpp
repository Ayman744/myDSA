#include <bits/stdc++.h>
using namespace std;
class Node
{
public:
    int data{ };// Stores the value/data for the node.
    Node *next{ };// Pointer to the next node in the list.
    Node *prev{ };// Pointer to the previous node in the list.
    // Constructor to initialize a node with a value and set next and prev pointers to nullptr.
    Node(int data) : data(data)
    {
        next = nullptr;
        prev = nullptr;
    }
    // Destructor prints the value being destroyed and its address.
    ~Node()
    {
        cout << "Destroy value: " << data << " at address " << this << "\n";
    }
    // Sets the next and previous pointers of the node.
    void set(Node* next_, Node* prev_)
    {
        this->next = next_;
        this->prev = prev_;
    }
};
class DoublyLinkedList
{
    Node *head{};  // Pointer to the first node of the list.
    Node *tail{};  // Pointer to the last node of the list.
    int length = 0;  // Keeps track of the number of nodes in the list.
    vector<Node*> debugData;  // Stores pointers to nodes for debugging purposes.
    // Adds a node to the debug vector.
    void debugAddNode(Node* node)
    {
        debugData.push_back(node);
    }
    // Removes a node from the debug vector.
    void debugRemoveNode(Node* node)
    {
        auto it = find(debugData.begin(), debugData.end(), node);
        if (it == debugData.end())
            cout << "Node does not exist\n";
        else
            debugData.erase(it);
    }
    // Verifies the correctness of the list (debugging).
    void debugVerifyData()
    {
        if (length == 0) {
            assert(head == nullptr);  // If list is empty, head must be null.
            assert(tail == nullptr);  // If list is empty, tail must be null.
        } else {
            assert(head != nullptr);  // If list has nodes, head should not be null.
            assert(tail != nullptr);  // If list has nodes, tail should not be null.
            if (length == 1)
                assert(head == tail);  // If only one node, head should equal tail.
            else
                assert(head != tail);  // Otherwise, they should be different.

            assert(!tail->next);  // Tail should not have a next node (end of the list).
        }

        int len = 0;
        for (Node* cur = head; cur; cur = cur->next, len++) {
            if (len == length - 1)    // Ensure last node is the tail.
                assert(cur == tail);
        }

        assert(length == len);  // Ensure calculated length matches the actual length.
        assert(length == (int)debugData.size());  // Ensure list length matches the debug data size.

        len = 0;
        for (Node* cur = tail; cur; cur = cur->prev, len++) {
            if (len == length - 1)    // Ensure first node is the head.
                assert(cur == head);
        }
        cout << "\n";
    }
    // Default constructor: creates an empty list.
    DoublyLinkedList() {}
    // Constructor with an initial value to create the list with one node.
    DoublyLinkedList(int val)
    {
        Node *newNode = new Node(val);
        head = newNode;  // Head and tail are the same for the first node.
        tail = newNode;
        length = 1;  // Initial list length is 1.
    }
    void deleteNode(Node* node)
    {
        debugRemoveNode(node);  // Removes the node from the debug tracking system.
        --length;  // Decrements the length of the doubly linked list since a node is being removed.
        delete node;  // Deletes the node, freeing the allocated memory.
    }
    void addNode(Node* node)
    {
        debugAddNode(node);
        ++length;
    }
    void printList()
    {
        Node *tmp = head;  // Start at the head of the list.
        while (tmp)  // Continue as long as the current node is not null.
        {
            cout << tmp->data << endl;  // Print the data of the current node.
            tmp = tmp->next;  // Move to the next node in the list.
        }
    }
    void printRev()
    {
        for (Node *cur = tail; cur; cur = cur->prev)  // Start at the tail and traverse backward.
            cout << cur->data << " ";  // Print the data of the current node, followed by a space.
        cout << "\n";  // Print a newline after all nodes are printed.
    }
    void link(Node *first, Node *secn)
    {
        if (first)
            first->next = secn;  // Link the 'first' node to the 'second' node.
        if (secn)
            secn->prev = first;  // Link the 'second' node back to the 'first' node.
    }
    void insertEnd(int val)
    {
        Node *newNode = new Node(val);  // Step 1: Create a new node with the given value.
        addNode(newNode);  // Step 2: Add the new node to the debugging system.
        if (!head)  // Step 3: If the list is empty, make this new node both the head and tail.
            head = tail = newNode;
        else  // Step 4: If the list is not empty:
        {
            link(tail, newNode);  // Step 4a: Link the current tail to the new node.
            tail = newNode;  // Step 4b: Update the tail to the new node.
        }
        debugVerifyData();  // Step 5: Verify the integrity of the list.
    }
    void insertFront(int val)
    {
        Node *newNode = new Node(val);  // Step 1: Create a new node with the given value.
        addNode(newNode);  // Step 2: Add the new node to the debugging system.
        if (!head)  // Step 3: If the list is empty, make this new node both the head and tail.
            head = tail = newNode;
        else  // Step 4: If the list is not empty:
        {
            link(newNode, head);  // Step 4a: Link the new node to the current head.
            head = newNode;  // Step 4b: Update the head to the new node.
        }
        debugVerifyData();  // Step 5: Verify the integrity of the list.
    }
    void insertSorted(int val)
    {
        // Step 1: Check if the list is empty or if the value should be inserted at the front
        if (!length || head->data >= val)
            insertFront(val);
            // Step 2: Check if the value should be inserted at the end
        else if (tail->data <= val)
            insertEnd(val);
            // Step 3: Otherwise, find the correct position to insert the new value
        else
        {
            for (Node *cur = head; cur; cur = cur->next)
            {
                if (val <= cur->data)
                    embedAfter(cur->prev, val);  // Insert after the previous node
                break;  // This break will cause the loop to exit after the first iteration
            }
        }
    }
    void embedAfter(Node *before, int val)
    {
        Node *mid = new Node(val);  // Step 1: Create a new node with the given value.
        ++length;  // Step 2: Increment the length of the list.
        debugAddNode(mid);  // Step 3: Add the new node to the debugging system.
        Node *after = before->next;  // Step 4: Store the node that comes after 'before'.
        link(before, mid);  // Step 5: Link the 'before' node to the new node 'mid'.
        link(mid, after);  // Step 6: Link the new node 'mid' to the 'after' node.
        debugVerifyData();  // Step 7: Verify the integrity of the list.
    }
    void deleteFirst()
    {
        if (length == 0) return;  // If the list is empty, do nothing.
        if (length == 1)
            head = nullptr, tail = nullptr;  // If there's only one node, set both head and tail to nullptr.
        Node *tmp = head->next;  // Temporarily store the next node of the head.
        deleteNode(head);  // Delete the current head node.
        head = tmp;  // Update head to the next node (previously stored in tmp).
        debugVerifyData();  // Call a debug function to verify the internal structure of the list.
    }
    void deleteLast()
    {
        if (length == 0) return;  // If the list is empty, do nothing.
        if (length == 1)
            head = nullptr, tail = nullptr;  // If there is only one node, set both head and tail to nullptr.
        Node *tmp = tail->prev;  // Store the node before the current tail.
        deleteNode(tail);  // Delete the current tail node.
        tail = tmp;  // Update tail to the previous node (stored in tmp).
        debugVerifyData();  // Verify the integrity of the list structure.
    }
    Node* deleteAndLink(Node *cur)
    {
        Node *ret = cur->prev;  // Step 1: Store the previous node
        link(cur->prev, cur->next);  // Step 2: Link the previous node to the next node
        deleteNode(cur);  // Step 3: Delete the current node
        return ret;  // Step 4: Return the previous node
    }
    void deleteWithKey(int val)
    {
        // Step 1: Check if the list is empty
        if (!length)
            return;
        // Step 2: Check if the head node contains the value to be deleted
        if (head->data == val)
            deleteFirst();  // Call deleteFirst() if the head node needs to be deleted
        else
        {
            // Step 3: Iterate through the list to find the node with the specified value
            for (Node *cur = head; cur; cur = cur->next)
            {
                // Step 4: If the node containing the value is found
                if (cur->data == val)
                {
                    deleteAndLink(cur);  // Delete the node and link its neighbors
                    // Step 5: Update tail if the last node was deleted
                    if (!cur->next)  // Check if the deleted node was the tail
                        tail = cur;  // Update tail to the previous node
                }
            }
        }
        // Step 6: Verify the integrity of the list after deletion
        debugVerifyData();
    }
    bool isPalandrom()
    {
        if (length <= 1)
            return true;  // A list with 0 or 1 nodes is inherently a palindrome.
        for (Node *cur = head; cur && cur->next; )
        {
            for (Node *back = tail; back && back->prev; )
            {
                if (cur->data != back->data)
                    return false;  // If data from the front and back don't match, it's not a palindrome.
                cur = cur->next;  // Move forward pointer to the next node.
                back = back->prev;  // Move backward pointer to the previous node.
            }
        }
        return true;  // If all node data matches symmetrically, return true.
    }
};