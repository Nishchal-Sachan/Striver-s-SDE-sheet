#include <iostream>
using namespace std;

/*
----------------------------------------------------
Definition of the Node
----------------------------------------------------
Each node has:
- data   : integer value
- next   : pointer to next list
- child  : pointer to sorted sub-list
*/
class Node {
public:
    int data;
    Node* next;
    Node* child;

    Node(int x) {
        data = x;
        next = NULL;
        child = NULL;
    }
};

/*
----------------------------------------------------
MERGE TWO SORTED LINKED LISTS (USING CHILD POINTER)
----------------------------------------------------
This function merges two sorted linked lists.
IMPORTANT:
- We use `child` pointer instead of `next`
- All `next` pointers are set to NULL
*/
Node* merge(Node* a, Node* b) {
    // Base cases
    if (a == NULL) return b;
    if (b == NULL) return a;

    Node* result;

    // Choose smaller node and recurse
    if (a->data < b->data) {
        result = a;
        result->child = merge(a->child, b);
    } else {
        result = b;
        result->child = merge(a, b->child);
    }

    // VERY IMPORTANT:
    // In flattened list, next must be NULL
    result->next = NULL;

    return result;
}

/*
----------------------------------------------------
FLATTEN LINKED LIST FUNCTION
----------------------------------------------------
Approach:
1. Flatten the list to the right (head->next)
2. Merge current list with flattened right list
3. Return merged head

This is similar to MERGE SORT.
*/
Node* flattenLinkedList(Node* head) {
    // Base case:
    // If list is empty or only one list exists
    if (head == NULL || head->next == NULL)
        return head;

    // Step 1: Flatten the right side
    head->next = flattenLinkedList(head->next);

    // Step 2: Merge current list with flattened list
    head = merge(head, head->next);

    // Step 3: Return the head of merged list
    return head;
}

/*
----------------------------------------------------
UTILITY FUNCTION TO PRINT FLATTENED LIST
----------------------------------------------------
Prints list using child pointers
*/
void printList(Node* head) {
    while (head) {
        cout << head->data << " ";
        head = head->child;
    }
    cout << endl;
}

/*
----------------------------------------------------
MAIN FUNCTION
----------------------------------------------------
Creates sample input and flattens it
*/
int main() {

    /*
    Constructing the linked list:

    5 → 10 → 19 → 28
    |    |     |     |
    7    20    22    35
    |           |     |
    8           50    40
    |                  |
    30                 45
    */

    Node* head = new Node(5);
    head->child = new Node(7);
    head->child->child = new Node(8);
    head->child->child->child = new Node(30);

    head->next = new Node(10);
    head->next->child = new Node(20);

    head->next->next = new Node(19);
    head->next->next->child = new Node(22);
    head->next->next->child->child = new Node(50);

    head->next->next->next = new Node(28);
    head->next->next->next->child = new Node(35);
    head->next->next->next->child->child = new Node(40);
    head->next->next->next->child->child->child = new Node(45);

    // Flatten the linked list
    Node* flattenedHead = flattenLinkedList(head);

    // Print the flattened list
    cout << "Flattened Linked List:\n";
    printList(flattenedHead);

    return 0;
}
