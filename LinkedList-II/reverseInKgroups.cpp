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
              PROBLEM: Reverse Nodes in k-Group (LeetCode 25)
    =============================================================================

    Given the head of a linked list and an integer k, reverse the nodes of the
    list k at a time, and return the modified list.

    - Nodes should be reversed in groups of size k.
    - If the number of nodes in the last group is less than k, leave them as is.
    - You must reverse the list in-place, using O(1) extra space.

    Example:
        Input:  1 -> 2 -> 3 -> 4 -> 5, k = 2
        Output: 2 -> 1 -> 4 -> 3 -> 5

        Input:  1 -> 2 -> 3 -> 4 -> 5, k = 3
        Output: 3 -> 2 -> 1 -> 4 -> 5
*/


/*
    =============================================================================
    APPROACH 1: RECURSIVE SOLUTION (O(n) time, O(n/k) stack)
    =============================================================================

    HIGH-LEVEL IDEA:

    1) From the current head, check if there are at least k nodes ahead.
       - If not, return head as is (no reversal for this block).
    2) Reverse exactly k nodes using standard linked list reversal pattern.
    3) After reversing k nodes:
         - `prev` becomes the new head of this block
         - `head` (original block head) becomes the tail of this block
         - `curr` points to the (k+1)-th node (next block start)
    4) Recursively call reverseKGroup(curr, k) on the remaining list and
       connect the result to head->next (tail of current reversed block).
    5) Return `prev` as the new head of this reversed block.

    This gives an in-place reversal with O(n) time.

    Note: Uses recursion → O(n/k) stack frames.
*/

class RecursiveSolution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {

        if (head == nullptr || k == 1) {
            // Empty list or reversing in groups of 1 → no change
            return head;
        }

        // Step 1: Check if we have at least k nodes starting from head
        ListNode* temp = head;
        int count = 0;
        while (temp != nullptr && count < k) {
            temp = temp->next;
            count++;
        }

        // Less than k nodes left → do NOT reverse, leave as-is
        if (count < k) return head;

        // Step 2: Reverse exactly k nodes
        ListNode* curr = head;
        ListNode* prev = nullptr;
        ListNode* next = nullptr;
        count = 0;

        while (curr != nullptr && count < k) {
            next = curr->next;   // store next node
            curr->next = prev;   // reverse pointer
            prev = curr;         // move prev forward
            curr = next;         // move curr forward
            count++;
        }

        // Now:
        // prev = new head of this k-sized reversed block
        // head = original head, now tail of this block
        // curr = (k+1)-th node, start of next block

        // Step 3: Recursively reverse the remaining list and attach
        head->next = reverseKGroup(curr, k);

        // Step 4: Return new head of this segment
        return prev;
    }
};



/*
    =============================================================================
    APPROACH 2: ITERATIVE SOLUTION (O(n) time, O(1) extra space)
    =============================================================================

    This version avoids recursion entirely and uses only pointers.

    IDEA:
        - Use a dummy node before head to simplify edge cases.
        - For each group:
            1) Find the k-th node from the current group's previous tail.
               If fewer than k nodes remain → done.
            2) Reverse the k nodes between groupPrev->next and kth.
            3) Reconnect:
                   groupPrev->next = new head of reversed block
                   tail_of_block->next = node after kth
            4) Move groupPrev to the tail_of_block and repeat.

    STEPS (POINTERS):
        - dummy -> [list...]
        - groupPrev starts at dummy.
        - Find kth = k-th node from groupPrev.
        - groupNext = kth->next
        - Reverse list from groupPrev->next up to kth.
        - Connect:
             groupPrev->next = kth
             newTail->next   = groupNext
        - Move groupPrev = newTail
        - Repeat until no full k-sized group remains.
*/

class IterativeSolution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == nullptr || k == 1) return head;

        // Dummy node before head to simplify connection logic
        ListNode dummy(0);
        dummy.next = head;

        // groupPrev points to the node before the current group
        ListNode* groupPrev = &dummy;

        while (true) {
            // Step 1: Find the k-th node from groupPrev
            ListNode* kth = groupPrev;
            int count = 0;
            while (kth != nullptr && count < k) {
                kth = kth->next;
                count++;
            }

            // If less than k nodes remain, we are done
            if (kth == nullptr) break;

            // Step 2: Define group boundaries
            ListNode* groupNext = kth->next;    // Node after kth (next group's start)
            ListNode* prev = groupNext;         // End connection for reversal
            ListNode* curr = groupPrev->next;   // First node of current group

            // Step 3: Reverse nodes in this group
            // Reverse [curr ... kth], linking each node to 'prev'
            while (curr != groupNext) {
                ListNode* temp = curr->next;
                curr->next = prev;
                prev = curr;
                curr = temp;
            }

            // Step 4: Reconnect reversed group with previous part
            // prev  = kth (new head of this group)
            // groupPrev->next was old head, now becomes tail
            ListNode* newGroupHead = prev;
            ListNode* newGroupTail = groupPrev->next;  // old head

            groupPrev->next = newGroupHead;
            groupPrev = newGroupTail;
        }

        return dummy.next;
    }
};



/*
    =============================================================================
    HELPER FUNCTIONS FOR TESTING (Optional)
    =============================================================================
*/

void printList(ListNode* head) {
    while (head != nullptr) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << "\n";
}

ListNode* buildList(initializer_list<int> vals) {
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    for (int v : vals) {
        if (!head) {
            head = new ListNode(v);
            tail = head;
        } else {
            tail->next = new ListNode(v);
            tail = tail->next;
        }
    }
    return head;
}


/*
    =============================================================================
    MAIN (Optional Example)
    =============================================================================
*/

int main() {
    // Example list: 1 -> 2 -> 3 -> 4 -> 5
    ListNode* head = buildList({1, 2, 3, 4, 5});
    int k = 2;

    cout << "Original list: ";
    printList(head);

    RecursiveSolution recSol;
    IterativeSolution itSol;

    // Using recursive solution
    ListNode* recResult = recSol.reverseKGroup(head, k);
    cout << "After reversing in groups of " << k << " (Recursive): ";
    printList(recResult);

    // Rebuild the list for iterative demo:
    head = buildList({1, 2, 3, 4, 5});
    ListNode* itResult = itSol.reverseKGroup(head, 3);
    cout << "After reversing in groups of 3 (Iterative): ";
    printList(itResult);

    return 0;
}
