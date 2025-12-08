#include <iostream>
using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(): val(0), next(nullptr) {}
    ListNode(int x): val(x), next(nullptr) {}
    ListNode(int x, ListNode *next): val(x), next(next) {}
};

/*
    =============================================================================
    PROBLEM (LeetCode 2 style):
    -----------------------------------------------------------------------------
    Each linked list represents a non-negative integer in REVERSE ORDER:
        l1: 2 -> 4 -> 3   = 342
        l2: 5 -> 6 -> 4   = 465

    Output: 7 -> 0 -> 8  = 807  (342 + 465)

    We add digit by digit like we do in school, from least significant to most.
    =============================================================================
*/

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

        // Dummy node to simplify list construction
        ListNode* dummy = new ListNode(0);
        ListNode* curr = dummy;

        int carry = 0;

        // Loop until both lists and carry are done
        while (l1 != nullptr || l2 != nullptr || carry) {

            int sum = carry;

            if (l1 != nullptr) {
                sum += l1->val;
                l1 = l1->next;  // move l1 ahead
            }

            if (l2 != nullptr) {
                sum += l2->val;
                l2 = l2->next;  // move l2 ahead
            }

            carry = sum / 10;        // new carry
            int digit = sum % 10;    // digit to store in node

            curr->next = new ListNode(digit);
            curr = curr->next;
        }

        ListNode* ansHead = dummy->next;
        delete dummy;  // free dummy node
        return ansHead;
    }
};
