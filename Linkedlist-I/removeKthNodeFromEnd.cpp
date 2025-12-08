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
    ============================================================================
    APPROACH 1: Two-pass method using length
    ============================================================================
    1. First pass: compute the total length `len`.
    2. The node to delete is at position (len - n + 1) from the start (1-based).
    3. Handle special case when we need to delete the head.
    4. Second pass: go to the (len - n)-th node and unlink its next.

    Time:  O(len) + O(len) = O(n)
    Space: O(1)
*/
class LengthBasedSolution {
public:
    int getLength(ListNode* head) {
        int count = 0;
        ListNode* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int len = getLength(head);

        // If we have to remove the only node
        if (len == 1) {
            delete head;
            return nullptr;
        }

        // If we must remove the head node (nth from end == len)
        if (n == len) {
            ListNode* newHead = head->next;
            delete head;
            return newHead;
        }

        // Position from start (1-based) of node to delete:
        // idx = len - n + 1, we want to stop at (idx-1)-th node.
        int steps = len - n;  // number of steps to reach node BEFORE target

        ListNode* temp = head;
        for (int i = 1; i < steps; i++) {
            temp = temp->next;
        }

        ListNode* nodeToDelete = temp->next;
        temp->next = nodeToDelete->next;
        delete nodeToDelete;

        return head;
    }
};



/*
    ============================================================================
    APPROACH 2: One-pass method using fast & slow pointers (dummy node)
    ============================================================================
    Idea:
        - Use a dummy node before head to simplify head deletion.
        - Move `fast` pointer n steps ahead.
        - Then move both `fast` and `slow` until `fast` reaches the end.
        - Now `slow->next` is the node to be removed.

    Why dummy?
        - It handles cases where the head is removed, without special logic.

    Time:  O(n)
    Space: O(1)
*/
class TwoPointerSolution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {

        // Dummy node before head
        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        ListNode* fast = dummy;
        ListNode* slow = dummy;

        // Move fast n steps ahead
        for (int i = 0; i < n; i++) {
            fast = fast->next;
        }

        // Move both until fast reaches last node
        while (fast->next != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }

        // Now slow->next is the node to remove
        ListNode* nodeToDelete = slow->next;
        slow->next = nodeToDelete->next;
        delete nodeToDelete;

        ListNode* newHead = dummy->next;
        delete dummy;   // free dummy node
        return newHead;
    }
};



/*
    ============================================================================
    APPROACH 3: Recursive approach
    ============================================================================
    Idea:
        - Recurse to the end of the list.
        - On the way back, keep a counter of how many nodes from the end.
        - When counter == n, delete that node.

    This is elegant, but less common in production due to recursion depth.

    Time:  O(n)
    Space: O(n) (recursion call stack)
*/
class RecursiveSolution {
public:
    // Helper returns new head and increments 'count' via reference
    ListNode* removeFromEnd(ListNode* head, int n, int &count) {
        if (head == nullptr) return nullptr;

        head->next = removeFromEnd(head->next, n, count);
        count++;

        // When count == n, this is the node to delete
        if (count == n) {
            ListNode* nextNode = head->next;
            delete head;
            return nextNode; // new link from above
        }
        return head; // no deletion at this level
    }

    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int count = 0;
        return removeFromEnd(head, n, count);
    }
};



/*
    ============================================================================
    MAIN (Optional test)
    ============================================================================
*/
int main() {
    // Example: create list 1->2->3->4->5, remove 2nd from end (4)

    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    LengthBasedSolution sol1;
    TwoPointerSolution sol2;
    RecursiveSolution sol3;

    // Test two-pointer optimal approach:
    ListNode* updated = sol2.removeNthFromEnd(head, 2);

    cout << "List after removal: ";
    while (updated != nullptr) {
        cout << updated->val << " ";
        updated = updated->next;
    }
    cout << endl;

    return 0;
}
