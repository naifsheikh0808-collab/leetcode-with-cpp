class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        int minDistance = INT_MAX;
        int maxDistance = -1;

        int firstCritical = -1;
        int prevCritical = -1;

        ListNode* prev = head;
        ListNode* curr = head->next;

        int pos = 1;

        while (curr != nullptr && curr->next != nullptr) {
            ListNode* next = curr->next;

            bool isCritical =
                (curr->val > prev->val && curr->val > next->val) ||
                (curr->val < prev->val && curr->val < next->val);

            if (isCritical) {
                if (firstCritical == -1) {
                    // First critical point
                    firstCritical = pos;
                } else {
                    // Distance from previous critical point
                    minDistance = min(minDistance, pos - prevCritical);

                    // Distance from first critical point
                    maxDistance = max(maxDistance, pos - firstCritical);
                }

                prevCritical = pos;
            }

            prev = curr;
            curr = next;
            pos++;
        }

        if (maxDistance == -1) {
            return {-1, -1};
        }

        return {minDistance, maxDistance};
    }
};