
// 21. Merge Two Sorted Lists

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy(0);
        ListNode* current = &dummy;

        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val <= list2->val) {
                current->next = list1;
                list1 = list1->next;
            } 
            else {
                current->next = list2;
                list2 = list2->next;
            }

            current = current->next;
        }

        // Attach the remaining nodes
        if (list1 != nullptr) {
            current->next = list1;
        } 
        else {
            current->next = list2;
        }

        return dummy.next;
    }
};

