#include <iostream>
#include <unordered_set>
using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(nullptr) {}
};


/*
    ============================================================================
    APPROACH 1 — HASHING (Visited Set)
    ============================================================================
    IDEA:
        - Store address of each visited node in a set.
        - If we ever visit a node already present in the set => cycle exists.

    TIME:  O(n)
    SPACE: O(n)

    PROS: Simple to understand
    CONS: Extra space — not optimal for interviews
*/
class HashingSolution {
public:
    bool hasCycle(ListNode* head) {
        unordered_set<ListNode*> visited;
        ListNode* temp = head;

        while (temp != nullptr) {
            // already seen → cycle detected
            if (visited.find(temp) != visited.end())
                return true;

            visited.insert(temp);
            temp = temp->next;
        }
        return false; // reached end => no cycle
    }
};



/*
    ============================================================================
    APPROACH 2 — FLOYD’S CYCLE DETECTION ALGORITHM
    (Tortoise and Hare Algorithm)
    ============================================================================
    IDEA:
        - Use two pointers (slow & fast)
        - slow moves 1 step at a time
        - fast moves 2 steps at a time
        - If a cycle exists, fast will eventually catch slow inside the loop

    WHY IT WORKS:
        - Think of it like running on a circular track:
          A fast runner eventually laps the slow runner.

    TIME:  O(n)
    SPACE: O(1)  ✓ Optimal

    MOST ASKED approach in tech interviews!
*/
class FloydCycleSolution {
public:
    bool hasCycle(ListNode* head) {
        if (!head || !head->next) return false;

        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;         // 1 step
            fast = fast->next->next;   // 2 steps

            if (slow == fast) {
                return true; // pointers meet => cycle exists
            }
        }
        return false; // fast reached end => no cycle
    }
};



/*
    ============================================================================
    MAIN — Example demonstration
    ============================================================================
*/
int main() {

    // Create a linked list with a cycle:
    // 1 -> 2 -> 3 -> 4 -> 5
    //          ^         |
    //          |         v
    //          └─────────
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    // Create a cycle: 5 -> points back to 3
    head->next->next->next->next->next = head->next->next;

    HashingSolution sol1;
    FloydCycleSolution sol2;

    cout << "Hashing Solution Says Cycle? "
         << (sol1.hasCycle(head) ? "Yes" : "No") << endl;

    cout << "Floyd Solution Says Cycle?  "
         << (sol2.hasCycle(head) ? "Yes" : "No") << endl;

    return 0;
}
