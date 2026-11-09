class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        int n = arrival.size();
        vector<int> count(k, 0); // Stores the number of requests handled by each server
        
        // Min-priority queue to track busy servers: {finish_time, server_index}
        // Servers are ordered by their finish_time, then by index (implicitly by pair comparison)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> busy;
        
        // Set to track available server indices for O(log k) lowest-index retrieval
        // `std::set` keeps elements sorted, allowing efficient `lower_bound` and `begin()`
        set<int> available;
        for (int i = 0; i < k; ++i) {
            available.insert(i);
        }
        
        for (int i = 0; i < n; ++i) {
            int current_arrival_time = arrival[i];
            
            // Step 1: Free all servers whose requests have completed by the current arrival time
            while (!busy.empty() && busy.top().first <= current_arrival_time) {
                available.insert(busy.top().second); // Add server back to available set
                busy.pop();
            }
            
            // Step 2: If no servers are available, drop the request
            if (available.empty()) {
                continue;
            }
            
            // Step 3: Find the preferred server based on circular assignment
            int preferred_start_index = i % k;
            auto it = available.lower_bound(preferred_start_index);
            
            int server_idx_to_assign;
            if (it == available.end()) {
                // No server available from preferred_start_index to k-1, wrap around
                it = available.begin();
                server_idx_to_assign = *it;
            } else {
                // Found a server at or after preferred_start_index
                server_idx_to_assign = *it;
            }
            
            // Step 4: Assign the request to the chosen server
            count[server_idx_to_assign]++;
            available.erase(it); // Remove server from available set
            
            // Add server to busy queue with its new finish time
            busy.push({current_arrival_time + load[i], server_idx_to_assign});
        }
        
        // Step 5: Find the maximum number of requests handled
        int max_requests = 0;
        for (int c : count) {
            max_requests = max(max_requests, c);
        }
        
        // Step 6: Collect all server indices that handled the maximum number of requests
        vector<int> result;
        for (int i = 0; i < k; ++i) {
            if (count[i] == max_requests) {
                result.push_back(i);
            }
        }
        
        return result;
    }
};