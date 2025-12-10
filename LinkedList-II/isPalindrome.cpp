#include <iostream>
#include <stack>
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
       PROBLEM: Check if a Singly Linked List is a Palindrome
    ============================================================================
    A linked list is a palindrome if the sequence of values is the same
    forwards and backwards.

    Examples:
        1 -> 2 -> 2 -> 1      ✅ palindrome
        1 -> 2 -> 3 -> 2 -> 1 ✅ palindrome
        1 -> 2 -> 3           ❌ not palindrome
*/


// ============================================================================
// Helper function to reverse a linked list
// ============================================================================
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;
    ListNode* next = nullptr;

    while (curr != nullptr) {
        next = curr->next;   // store next
        curr->next = prev;   // reverse pointer
        prev = curr;         // move prev
        curr = next;         // move curr
    }
    return prev; // new head
}


/*
    ============================================================================
    APPROACH 1: Reverse Second Half (Optimal: O(n) time, O(1) extra space)
    ============================================================================
    IDEA:
        1) Use slow & fast pointers to find the middle of the list.
           - slow moves 1 step
           - fast moves 2 steps
        2) For even length:
                1 -> 2 -> 2 -> 1
            slow ends at 2 (first middle of the right half or just past left half)
        3) For odd length:
                1 -> 2 -> 3 -> 2 -> 1
            slow ends at the middle node (value 3).
            We skip the exact middle when comparing.
        4) Reverse the second half starting from slow (for even)
           or slow->next (for odd).
        5) Compare first half and reversed second half node-by-node.
        6) (Optional) Restore the list by reversing the second half back.

    This is the standard optimal solution for interviews.
*/

class OptimalPalindromeSolution {
public:
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true; // 0 or 1 node → palindrome

        // Step 1: Find middle using slow & fast pointer
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // At this point:
        // If length is odd, fast != nullptr, slow is at middle.
        // If even, fast == nullptr, slow is at start of second half.

        ListNode* secondHead = nullptr;

        if (fast != nullptr) {
            // Odd length: skip the middle node
            // Example: 1 -> 2 -> 3 -> 2 -> 1
            // slow at 3, second half starts at slow->next (the 2)
            secondHead = reverseList(slow->next);
        } else {
            // Even length: second half starts at slow
            // Example: 1 -> 2 -> 2 -> 1
            // slow at first 2 of the second half
            secondHead = reverseList(slow);
        }

        // Step 2: Compare first half and reversed second half
        ListNode* firstHead = head;
        ListNode* temp2 = secondHead;

        bool isPalin = true;

        while (temp2 != nullptr) {
            if (firstHead->val != temp2->val) {
                isPalin = false;
                break;
            }
            firstHead = firstHead->next;
            temp2 = temp2->next;
        }

        // (Optional) Step 3: Restore the list to original form
        // reverseList(secondHead); // if you want to keep the list unchanged

        return isPalin;
    }
};


/*
    ============================================================================
    APPROACH 2: Using a Stack (O(n) time, O(n) space)
    ============================================================================
    IDEA:
        - Push all values into a stack.
        - Traverse the list again from head:
            - Pop from stack and compare with current node's value.
        - If all match → palindrome.

    This is conceptually simple but uses extra memory.
*/

class StackPalindromeSolution {
public:
    bool isPalindrome(ListNode* head) {
        stack<int> st;
        ListNode* temp = head;

        // Push all values to stack
        while (temp != nullptr) {
            st.push(temp->val);
            temp = temp->next;
        }

        // Compare with values popped from stack
        temp = head;
        while (temp != nullptr) {
            int top = st.top();
            st.pop();
            if (temp->val != top) {
                return false;
            }
            temp = temp->next;
        }

        return true;
    }
};


/*
    ============================================================================
    HELPER FUNCTIONS FOR TESTING (Optional)
    ============================================================================
*/

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

void printList(ListNode* head) {
    while (head != nullptr) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << "\n";
}


/*
    ============================================================================
    MAIN (Optional) — Demo
    ============================================================================
*/
int main() {
    // Example Palindrome: 1 -> 2 -> 3 -> 2 -> 1
    ListNode* head1 = buildList({1, 2, 3, 2, 1});

    // Example Non-Palindrome: 1 -> 2 -> 3
    ListNode* head2 = buildList({1, 2, 3});

    OptimalPalindromeSolution optSol;
    StackPalindromeSolution stSol;

    cout << "List 1: ";
    printList(head1);
    cout << "Optimal: " << (optSol.isPalindrome(head1) ? "Palindrome" : "Not Palindrome") << endl;
    cout << "Stack  : " << (stSol.isPalindrome(head1) ? "Palindrome" : "Not Palindrome") << endl;

    cout << "\nList 2: ";
    printList(head2);
    cout << "Optimal: " << (optSol.isPalindrome(head2) ? "Palindrome" : "Not Palindrome") << endl;
    cout << "Stack  : " << (stSol.isPalindrome(head2) ? "Palindrome" : "Not Palindrome") << endl;

    return 0;
}
