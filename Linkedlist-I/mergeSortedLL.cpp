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
    APPROACH 1: In-place Merge inserting nodes of second into first
    ============================================================================
    IDEA:
        - Always treat `first` as the list with the smaller starting value.
        - We try to insert nodes from `second` at the correct sorted position
          inside `first`.

        Example:
            first:  1 -> 4 -> 7
            second: 2 -> 3 -> 5 -> 6

        We walk `curr1` and `next1` in `first`, and try to "fit" `curr2`
        (from `second`) between them whenever:

                curr1->val <= curr2->val <= next1->val

        If `curr2` is bigger than `next1`, we advance in `first`.

        If we reach the end of `first` (next1 == NULL),
        we simply attach the remaining part of `second`.
*/

class InPlaceMergeSolution {
public:
    // Merge `second` into `first`, assuming first->val <= second->val
    ListNode* solve(ListNode* first, ListNode* second) {

        // If first has only one node, just attach second after it
        if (first->next == nullptr) {
            first->next = second;
            return first;
        }

        ListNode* curr1 = first;          // pointer in first list
        ListNode* next1 = curr1->next;    // next node in first
        ListNode* curr2 = second;         // pointer in second list
        ListNode* next2 = nullptr;        // next node in second

        // Traverse until we exhaust either `next1` or `curr2`
        while (next1 != nullptr && curr2 != nullptr) {

            // Check if curr2 fits between curr1 and next1
            if (curr2->val >= curr1->val && curr2->val <= next1->val) {

                // Insert curr2 between curr1 and next1
                curr1->next = curr2;
                next2 = curr2->next;   // store next of curr2
                curr2->next = next1;   // link curr2 to next1

                // Move curr1 and curr2 forward
                curr1 = curr2;
                curr2 = next2;
            }
            else {
                // Move ahead in first list
                curr1 = next1;
                next1 = next1->next;

                // If we've reached the end of first list,
                // simply attach remaining second list.
                if (next1 == nullptr) {
                    curr1->next = curr2;
                }
            }
        }

        return first;  // `first` is still the head of merged list
    }

    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {

        if (list1 == nullptr) return list2;
        if (list2 == nullptr) return list1;

        // Ensure `first` has the smaller or equal starting value
        if (list1->val <= list2->val) {
            return solve(list1, list2);
        } else {
            return solve(list2, list1);
        }
    }
};



/*
    ============================================================================
    APPROACH 2: Standard Dummy-Node Merge (Simpler, Same Complexity)
    ============================================================================
    IDEA:
        - Use a dummy node to build the merged list.
        - Always pick the smaller node from list1 or list2,
          attach it to the `tail`, and move forward.

        This approach is very clean and commonly written in interviews.

    TIME:  O(n + m)
    SPACE: O(1) extra
*/

class DummyMergeSolution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {

        ListNode dummy(0);           // dummy head
        ListNode* tail = &dummy;     // current tail of merged list

        ListNode* p1 = list1;
        ListNode* p2 = list2;

        // Merge while both lists have nodes
        while (p1 != nullptr && p2 != nullptr) {
            if (p1->val <= p2->val) {
                tail->next = p1;
                p1 = p1->next;
            } else {
                tail->next = p2;
                p2 = p2->next;
            }
            tail = tail->next;
        }

        // Attach remaining nodes
        if (p1 != nullptr) tail->next = p1;
        else               tail->next = p2;

        return dummy.next;   // head of merged list
    }
};



/*
    ============================================================================
    MAIN (Optional Test)
    ============================================================================
*/
int main() {
    // Example:
    // list1: 1 -> 3 -> 5
    // list2: 2 -> 4 -> 6

    ListNode* a = new ListNode(1);
    a->next = new ListNode(3);
    a->next->next = new ListNode(5);

    ListNode* b = new ListNode(2);
    b->next = new ListNode(4);
    b->next->next = new ListNode(6);

    InPlaceMergeSolution s1;
    DummyMergeSolution s2;

    ListNode* merged1 = s1.mergeTwoLists(a, b);
    cout << "In-place merged: ";
    for (ListNode* t = merged1; t != nullptr; t = t->next)
        cout << t->val << " ";
    cout << endl;

    // NOTE: a and b are now interlinked after first merge,
    // for a real test you'd reconstruct them for the second call.

    return 0;
}
