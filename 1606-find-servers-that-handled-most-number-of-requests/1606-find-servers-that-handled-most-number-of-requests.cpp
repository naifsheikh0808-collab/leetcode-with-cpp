class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {

        set<int> available;

        // Initially, all servers are available
        for (int i = 0; i < k; i++) {
            available.insert(i);
        }

        // {completion_time, server_id}
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > busy;

        vector<int> count(k, 0);

        for (int i = 0; i < arrival.size(); i++) {

            // Free all servers whose requests have completed
            while (!busy.empty() && busy.top().first <= arrival[i]) {

                int server = busy.top().second;

                available.insert(server);

                busy.pop();
            }

            // If all servers are busy, drop the request
            if (available.empty()) {
                continue;
            }

            // Preferred server
            int target = i % k;

            // Find the first available server >= target
            auto it = available.lower_bound(target);

            // If no such server exists, wrap around to the beginning
            if (it == available.end()) {
                it = available.begin();
            }

            int server = *it;

            // Remove server from available set
            available.erase(it);

            // Increase request count
            count[server]++;

            // Add server to busy heap
            busy.push({arrival[i] + load[i], server});
        }

        // Find maximum number of requests handled
        int maxi = *max_element(count.begin(), count.end());

        vector<int> ans;

        // Collect all busiest servers
        for (int i = 0; i < k; i++) {
            if (count[i] == maxi) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};