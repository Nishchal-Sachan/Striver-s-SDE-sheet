#include<iostream>
using namespace std;
struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
};
 

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        
        // If the list is empty, no cycle can exist
        if (!head) return NULL;

        // Two pointers: slow moves 1 step, fast moves 2 steps
        ListNode* slow = head;
        ListNode* fast = head;

        // Phase 1: Detect if a cycle exists
        while (fast && fast->next) {
            slow = slow->next;          // move slow by 1
            fast = fast->next->next;    // move fast by 2
            
            // If slow == fast, they meet → a cycle exists
            if (slow == fast) {
                
                // Phase 2: Find the starting node of the cycle
                
                // Move 'slow' to head.
                // Keep 'fast' at meeting point.
                // Now both move 1 step at a time.
                slow = head;
                
                while (slow != fast) {
                    slow = slow->next;
                    fast = fast->next;
                }

                // The node where they meet again is the cycle start
                return slow;
            }
        }

        // If fast reaches NULL, no cycle exists
        return NULL;
    }
};
