
class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {

        // Build adjacency list
        vector<vector<pair<int, int>>> adj(n);

        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];

            adj[u].push_back({v, w});
        }

        // dist[node][count]
        vector<vector<long long>> dist(n, vector<long long>(k + 1, LLONG_MAX));

        // {distance, node, consecutive count}
        using State = tuple<long long, int, int>;

        priority_queue<State, vector<State>, greater<State>> pq;

        // Starting node
        dist[0][1] = 0;
        pq.push({0, 0, 1});

        while (!pq.empty()) {

            auto [cost, node, count] = pq.top();
            pq.pop();

            // Ignore outdated states
            if (cost != dist[node][count]) {
                continue;
            }

            // Destination reached
            if (node == n - 1) {
                return cost;
            }

            for (auto [next, weight] : adj[node]) {

                int newCount;

                if (labels[node] == labels[next]) {
                    newCount = count + 1;
                }
                else {
                    newCount = 1;
                }

                // More than k consecutive characters
                if (newCount > k) {
                    continue;
                }

                long long newCost = cost + weight;

                if (newCost < dist[next][newCount]) {

                    dist[next][newCount] = newCost;

                    pq.push({newCost, next, newCount});
                }
            }
        }

        return -1;
    }
};
