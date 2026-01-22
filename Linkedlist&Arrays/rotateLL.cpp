#include <iostream>
using namespace std;

//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:

    /* ============================================================
       APPROACH 1 : BRUTE FORCE (Rotate one step at a time)
       ------------------------------------------------------------
       IDEA:
       Rotate the linked list to the right by 1 position,
       and repeat this process k times.

       HOW ONE ROTATION WORKS:
       - Traverse till the last node
       - Detach the last node
       - Move it to the front

       TIME COMPLEXITY:
       Each rotation = O(n)
       k rotations     = O(n * k)   ❌

       SPACE COMPLEXITY:
       O(1)

       WHEN TO USE:
       - Only for understanding pointer manipulation
       - NOT recommended for interviews or large inputs
    ============================================================ */
    
    ListNode* rotateRight_BruteForce(ListNode* head, int k) {
        if (!head || !head->next || k == 0)
            return head;

        for (int i = 0; i < k; i++) {

            ListNode* curr = head;
            ListNode* prev = NULL;

            // Move to last node
            while (curr->next != NULL) {
                prev = curr;
                curr = curr->next;
            }

            // Detach last node and move it to front
            prev->next = NULL;
            curr->next = head;
            head = curr;
        }

        return head;
    }

    /* ============================================================
       APPROACH 2 : OPTIMIZED USING LENGTH (Interview Preferred)
       ------------------------------------------------------------
       OBSERVATION:
       Rotating by k times is same as rotating by (k % length)

       LOGIC:
       - Find length of list
       - Reduce k using modulo
       - New head will be at (length - k + 1)th position
       - Break the list at (length - k)th node
       - Attach the tail to old head

       TIME COMPLEXITY:
       O(n)  ✅

       SPACE COMPLEXITY:
       O(1)

       WHEN TO USE:
       - Interview
       - Large constraints
       - Clean & efficient solution
    ============================================================ */

    int getLength(ListNode* head) {
        int count = 0;
        while (head != NULL) {
            count++;
            head = head->next;
        }
        return count;
    }

    ListNode* rotateRight_Optimized(ListNode* head, int k) {
        if (!head || !head->next || k == 0)
            return head;

        int len = getLength(head);
        k = k % len;

        // If no rotation needed
        if (k == 0)
            return head;

        // Move to (len - k)th node
        ListNode* temp = head;
        for (int i = 1; i < len - k; i++) {
            temp = temp->next;
        }

        // New head will be next of temp
        ListNode* newHead = temp->next;
        temp->next = NULL;

        // Connect tail of rotated part to old head
        ListNode* tail = newHead;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = head;

        return newHead;
    }

    /* ============================================================
       MAIN FUNCTION
       ------------------------------------------------------------
       Choose which approach to run.
       For interviews → ALWAYS use Optimized.
    ============================================================ */

    ListNode* rotateRight(ListNode* head, int k) {
        // return rotateRight_BruteForce(head, k);
        return rotateRight_Optimized(head, k);
    }
};

/* ================= HELPER FUNCTIONS ================= */

ListNode* createList(int arr[], int n) {
    if (n == 0) return NULL;

    ListNode* head = new ListNode(arr[0]);
    ListNode* temp = head;

    for (int i = 1; i < n; i++) {
        temp->next = new ListNode(arr[i]);
        temp = temp->next;
    }
    return head;
}

void printList(ListNode* head) {
    while (head != NULL) {
        cout << head->val << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

/* ======================= MAIN ======================= */

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = 5;
    int k = 2;

    ListNode* head = createList(arr, n);

    cout << "Original List: ";
    printList(head);

    Solution sol;
    head = sol.rotateRight(head, k);

    cout << "After Rotating Right by " << k << " positions: ";
    printList(head);

    return 0;
}