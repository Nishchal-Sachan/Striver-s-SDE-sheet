#include <iostream>
using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/*
    ===============================================================
    FIND MIDDLE OF A LINKED LIST — Optimal Approach
    ===============================================================

    APPROACH:
        Slow & Fast Pointer Method (Floyd's Algorithm)

        - slow moves one step at a time
        - fast moves two steps at a time

        When fast reaches the end:
            → slow will be at the middle

    EVEN LENGTH CASE:
        Example: 1 → 2 → 3 → 4
        Result should be node with value 3 (right middle)
        This approach naturally returns the 2nd middle.

    TIME COMPLEXITY:  O(n)
    SPACE COMPLEXITY: O(1)
*/

class Solution {
public:
    ListNode* middleNode(ListNode* head) {

        ListNode* slow = head;
        ListNode* fast = head;

        // Move fast by 2 steps & slow by 1 step
        while(fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // slow is now the middle node
        return slow;
    }
};


/*
    ===============================================================
    MAIN (Optional for demonstration)
    ===============================================================
*/
int main() {
    // Example Linked List: 1 -> 2 -> 3 -> 4 -> 5
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    Solution sol;
    ListNode* mid = sol.middleNode(head);

    cout << "Middle Node Value: " << mid->val << endl;  // Output: 3
}
