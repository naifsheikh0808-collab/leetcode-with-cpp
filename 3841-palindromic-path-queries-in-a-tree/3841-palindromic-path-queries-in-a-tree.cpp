
#include <bits/stdc++.h>
using namespace std;

class Solution {
    struct Fenwick {
        int n;
        vector<int> bit;

        Fenwick(int n) : n(n), bit(n + 2, 0) {}

        void add(int idx, int val) {
            for (; idx <= n + 1; idx += idx & -idx) {
                bit[idx] ^= val;
            }
        }

        void rangeXor(int l, int r, int val) {
            add(l + 1, val);
            add(r + 2, val);
        }

        int pointQuery(int pos) {
            int res = 0;
            for (int idx = pos + 1; idx > 0; idx -= idx & -idx) {
                res ^= bit[idx];
            }
            return res;
        }
    };

public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        vector<vector<int>> adj(n);

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        int LOG = 1;
        while ((1 << LOG) <= n) {
            LOG++;
        }

        vector<vector<int>> up(LOG, vector<int>(n, 0));
        vector<int> depth(n, 0), tin(n), tout(n);

        // Iterative DFS to build Euler tour and LCA table
        vector<tuple<int, int, bool>> st;
        st.push_back({0, 0, false});

        int timer = 0;

        while (!st.empty()) {
            auto [u, p, exiting] = st.back();
            st.pop_back();

            if (exiting) {
                tout[u] = timer - 1;
                continue;
            }

            tin[u] = timer++;

            up[0][u] = p;

            for (int j = 1; j < LOG; j++) {
                up[j][u] = up[j - 1][up[j - 1][u]];
            }

            st.push_back({u, p, true});

            for (int i = (int)adj[u].size() - 1; i >= 0; i--) {
                int v = adj[u][i];

                if (v == p) {
                    continue;
                }

                depth[v] = depth[u] + 1;
                st.push_back({v, u, false});
            }
        }

        // Lowest Common Ancestor
        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v]) {
                swap(u, v);
            }

            int diff = depth[u] - depth[v];

            for (int j = 0; j < LOG; j++) {
                if (diff & (1 << j)) {
                    u = up[j][u];
                }
            }

            if (u == v) {
                return u;
            }

            for (int j = LOG - 1; j >= 0; j--) {
                if (up[j][u] != up[j][v]) {
                    u = up[j][u];
                    v = up[j][v];
                }
            }

            return up[0][u];
        };

        auto maskOf = [](char c) {
            return 1 << (c - 'a');
        };

        Fenwick fw(n);

        // Initialize root-to-node character masks
        for (int u = 0; u < n; u++) {
            fw.rangeXor(tin[u], tout[u], maskOf(s[u]));
        }

        vector<bool> answer;

        for (const string& q : queries) {
            string type;
            stringstream ss(q);

            int u, v;
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                int change = maskOf(s[u]) ^ maskOf(c);

                fw.rangeXor(tin[u], tout[u], change);

                s[u] = c;
            } else {
                ss >> v;

                int w = lca(u, v);

                int rootU = fw.pointQuery(tin[u]);
                int rootV = fw.pointQuery(tin[v]);

                int pathMask =
                    rootU ^ rootV ^ maskOf(s[w]);

                // A palindrome permutation allows at most
                // one character with an odd frequency.
                answer.push_back(
                    (pathMask & (pathMask - 1)) == 0
                );
            }
        }

        return answer;
    }
};
