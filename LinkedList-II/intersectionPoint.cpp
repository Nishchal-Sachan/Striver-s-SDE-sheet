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
    PROBLEM: Intersection of Two Linked Lists
    ============================================================================
    Two singly linked lists may or may not intersect.

    If they intersect:
        At some node, both lists share the SAME node (by address, not by value),
        and from that node, their remaining tail is identical.

    GOAL:
        Return the intersection node (first common node) OR nullptr if no intersection.

    NOTE:
        We are NOT allowed to modify the original list structures.
*/



/*
    ============================================================================
    1️⃣ APPROACH 1 — BRUTE FORCE (O(n * m))
    ============================================================================
    IDEA:
        - For every node in list B (head2), traverse entire list A (head1)
          and check if any node in A has the same address.
        - The first time temp1 == temp2, we found the intersection.

    TIME COMPLEXITY:
        O(lenA * lenB)

    SPACE COMPLEXITY:
        O(1)

    This approach is simple but very inefficient for large lists.
*/
class BruteForceSolution {
public:
    ListNode* getIntersectionNode(ListNode* head1, ListNode* head2) {

        // For each node in list2:
        while (head2 != nullptr) {

            // Traverse list1 from beginning
            ListNode* temp = head1;

            while (temp != nullptr) {
                if (temp == head2) {
                    // Found common node by address -> intersection
                    return head2;
                }
                temp = temp->next;
            }

            // Move to next node in list2
            head2 = head2->next;
        }

        // No intersection found
        return nullptr;
    }
};



/*
    ============================================================================
    2️⃣ APPROACH 2 — LENGTH DIFFERENCE METHOD
    ============================================================================
    CORE IDEA:
        - If two lists intersect, then their tails (from intersection onwards)
          are exactly the same.
        - Intersection is purely determined by alignment from the end.

    STEPS:
        1. Compute lengths of both lists: len1, len2.
        2. Compute difference: diff = abs(len1 - len2).
        3. Advance the head of the longer list by 'diff' steps.
           → Now both pointers are equally far from the tail.
        4. Move both pointers one step at a time until:
             - They meet at the intersection node, or
             - Both become nullptr (no intersection)

    TIME COMPLEXITY:
        O(len1 + len2)

    SPACE COMPLEXITY:
        O(1)
*/
class LengthDifferenceSolution {
public:
    int getLength(ListNode* head) {
        int len = 0;
        while (head != nullptr) {
            len++;
            head = head->next;
        }
        return len;
    }

    ListNode* getIntersectionNode(ListNode* head1, ListNode* head2) {

        int len1 = getLength(head1);
        int len2 = getLength(head2);

        // Bring both pointers to the same distance from the tail
        int diff = len1 - len2;

        // If diff is positive, list1 is longer
        // If diff is negative, list2 is longer
        if (diff > 0) {
            while (diff--) head1 = head1->next;
        } else {
            diff = -diff;
            while (diff--) head2 = head2->next;
        }

        // Move both pointers together until they meet or reach end
        while (head1 != nullptr && head2 != nullptr) {
            if (head1 == head2) {
                return head1;   // intersection found
            }
            head1 = head1->next;
            head2 = head2->next;
        }

        return nullptr; // no intersection
    }
};



/*
    ============================================================================
    3️⃣ APPROACH 3 — HASHING / VISITED SET
    ============================================================================
    IDEA:
        - Traverse list1 and store every node's address in an unordered_set.
        - Then traverse list2, and for each node, check if it exists in the set.
        - The first node found in the set is the intersection point.

    TIME COMPLEXITY:
        O(len1 + len2)

    SPACE COMPLEXITY:
        O(len1) or O(len2)

    This is easier to think about but uses extra memory.
*/
class HashingSolution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {

        unordered_set<ListNode*> visited;

        // Store all nodes of list A
        ListNode* temp = headA;
        while (temp != nullptr) {
            visited.insert(temp);
            temp = temp->next;
        }

        // Traverse list B and check if any node belongs to the set
        temp = headB;
        while (temp != nullptr) {
            if (visited.find(temp) != visited.end()) {
                // First common node found
                return temp;
            }
            temp = temp->next;
        }

        return nullptr; // no intersection
    }
};



/*
    ============================================================================
    4️⃣ APPROACH 4 — TWO POINTERS SWITCHING HEADS (Optimal & Elegant)
    ============================================================================
    This is the MOST FAMOUS and INTERVIEW-FAVORITE approach.

    IDEA:
        Let:
            A length = a
            B length = b
            Intersection length (common tail) = c

        Unique parts are:
            A: (a - c) before intersection
            B: (b - c) before intersection

        We use two pointers:
            p1 starts at headA
            p2 starts at headB

        Traverse:
            p1 moves along A, then jumps to B
            p2 moves along B, then jumps to A

        Distances:
            Path of p1 = a + b
            Path of p2 = b + a

        If there is an intersection:
            After at most a + b steps, p1 and p2 meet at the intersection node.

        If no intersection:
            Both will end up as nullptr at the same time.

    LOGIC:
        while (p1 != p2) {
            p1 = (p1 == nullptr) ? headB : p1->next;
            p2 = (p2 == nullptr) ? headA : p2->next;
        }

    TIME COMPLEXITY:
        O(a + b)

    SPACE COMPLEXITY:
        O(1)

    No extra space, no length calculation, super elegant.
*/
class TwoPointerSolution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {

        if (!headA || !headB) return nullptr;

        ListNode* p1 = headA;
        ListNode* p2 = headB;

        // Loop until they meet OR both become nullptr
        while (p1 != p2) {

            // Move pointer forward, or switch to other list's head when reaching end
            p1 = (p1 == nullptr) ? headB : p1->next;
            p2 = (p2 == nullptr) ? headA : p2->next;
        }

        // Either intersection node OR nullptr
        return p1;
    }
};



/*
    ============================================================================
    MAIN (Optional Demo)
    ============================================================================
*/
int main() {

    // Construct sample intersecting lists:
    // A: 1 -> 2 -> 8 -> 9
    // B:    3 -> 8 -> 9

    ListNode* inter = new ListNode(8);
    inter->next = new ListNode(9);

    ListNode* headA = new ListNode(1);
    headA->next = new ListNode(2);
    headA->next->next = inter;

    ListNode* headB = new ListNode(3);
    headB->next = inter;

    BruteForceSolution brute;
    LengthDifferenceSolution lenDiff;
    HashingSolution hashSol;
    TwoPointerSolution twoPtr;

    ListNode* res1 = brute.getIntersectionNode(headA, headB);
    ListNode* res2 = lenDiff.getIntersectionNode(headA, headB);
    ListNode* res3 = hashSol.getIntersectionNode(headA, headB);
    ListNode* res4 = twoPtr.getIntersectionNode(headA, headB);

    cout << "BruteForceSolution       : " << (res1 ? to_string(res1->val) : "None") << endl;
    cout << "LengthDifferenceSolution : " << (res2 ? to_string(res2->val) : "None") << endl;
    cout << "HashingSolution          : " << (res3 ? to_string(res3->val) : "None") << endl;
    cout << "TwoPointerSolution       : " << (res4 ? to_string(res4->val) : "None") << endl;

    return 0;
}
