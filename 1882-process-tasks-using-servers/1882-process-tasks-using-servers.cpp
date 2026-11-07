class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int n = servers.size();
        int m = tasks.size();

        priority_queue<pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>> freeServers;

        priority_queue<pair<long long, pair<int, int>>,
            vector<pair<long long, pair<int, int>>>,
            greater<pair<long long, pair<int, int>>>> busyServers;

        for (int i = 0; i < n; i++) {
            freeServers.push({servers[i], i});
        }

        vector<int> ans(m);
        long long currentTime = 0;

        for (int i = 0; i < m; i++) {
            currentTime = max(currentTime, (long long)i);

            // Release servers that have completed their tasks
            while (!busyServers.empty() &&
                   busyServers.top().first <= currentTime) {

                auto curr = busyServers.top();
                busyServers.pop();

                freeServers.push(curr.second);
            }

            // If no server is free, wait for the earliest one
            if (freeServers.empty()) {
                currentTime = busyServers.top().first;

                while (!busyServers.empty() &&
                       busyServers.top().first <= currentTime) {

                    auto curr = busyServers.top();
                    busyServers.pop();

                    freeServers.push(curr.second);
                }
            }

            // Select the server with minimum weight and index
            auto [weight, index] = freeServers.top();
            freeServers.pop();

            ans[i] = index;

            // Assign the task and update server availability
            busyServers.push({
                currentTime + tasks[i],
                {weight, index}
            });
        }

        return ans;
    }
};