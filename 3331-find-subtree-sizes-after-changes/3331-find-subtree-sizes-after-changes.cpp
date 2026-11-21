
class Solution {
public:
    vector<vector<int>> adj, newAdj;
    vector<int> ans;
    vector<int> last[26];

    void dfs1(int node, string &s) {

        int ch = s[node] - 'a';

        // Add current node to its character stack
        last[ch].push_back(node);

        // Process children in the ORIGINAL tree
        for (int child : adj[node]) {

            int c = s[child] - 'a';

            int newParent;

            // Find closest matching ancestor
            if (!last[c].empty()) {
                newParent = last[c].back();
            } 
            else {
                newParent = node;
            }

            // Attach child to its new parent
            newAdj[newParent].push_back(child);

            // Continue DFS using original tree
            dfs1(child, s);
        }

        // Backtrack
        last[ch].pop_back();
    }

    int dfs2(int node) {

        int size = 1;

        for (int child : newAdj[node]) {
            size += dfs2(child);
        }

        ans[node] = size;

        return size;
    }

    vector<int> findSubtreeSizes(vector<int>& parent, string s) {

        int n = parent.size();

        adj.resize(n);
        newAdj.resize(n);
        ans.resize(n);

        // Build original tree
        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        // Construct modified tree
        dfs1(0, s);

        // Calculate subtree sizes
        dfs2(0);

        return ans;
    }
};
