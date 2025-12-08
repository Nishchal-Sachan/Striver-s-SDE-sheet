#include <iostream>
using namespace std;

/*
    Definition of singly linked list node:
*/
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/*
    ===============================================================
    APPROACH 1️⃣ : Iterative Reversal
    ===============================================================
    - Use 3 pointers: prev, curr, nextNode
    - Reverse links one by one while traversing
    - Time:  O(n)
    - Space: O(1)
*/
class IterativeSolution {
public:
    ListNode* reverseList(ListNode* head) {

        ListNode* prev = nullptr; // previous node for reversal
        ListNode* curr = head;    // pointer to traverse list

        while(curr != nullptr) {
            ListNode* nextNode = curr->next; // store next node
            curr->next = prev;               // reverse the link

            prev = curr;                     // move prev forward
            curr = nextNode;                 // move curr forward
        }

        return prev; // new head of reversed list
    }
};


/*
    ===============================================================
    APPROACH 2️⃣ : Recursive Reversal
    ===============================================================
    - Reverse first and then fix the current link
    - Let recursion handle rest of the list
    - Time:  O(n)
    - Space: O(n) stack memory due to recursion
*/
class RecursiveSolution {
public:
    ListNode* reverseList(ListNode* head) {

        // Base case: single node OR empty list
        if(head == nullptr || head->next == nullptr)
            return head;

        // Reverse everything after head
        ListNode* newHead = reverseList(head->next);

        // Fix the current node's pointer
        head->next->next = head;
        head->next = nullptr;

        return newHead;
    }
};


/*
    ===============================================================
    MAIN (Optional)
    - Demonstration of calling both reversal methods
    ===============================================================
*/
int main() {
    // Creating a test linked list: 1 -> 2 -> 3 -> nullptr
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);

    IterativeSolution it;
    RecursiveSolution re;

    ListNode* reversed1 = it.reverseList(head);

    cout << "Reversed Using Iterative: ";
    ListNode* temp = reversed1;
    while(temp != nullptr) {
        cout << temp->val << " ";
        temp = temp->next;
    }
    cout << endl;

    // Reverse again recursively to show second method
    ListNode* reversed2 = re.reverseList(reversed1);

    cout << "Reversed Using Recursive: ";
    temp = reversed2;
    while(temp != nullptr) {
        cout << temp->val << " ";
        temp = temp->next;
    }
    cout << endl;

    return 0;
}
