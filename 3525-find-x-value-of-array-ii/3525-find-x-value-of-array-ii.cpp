class Solution {
public:
    struct Node {
        int prod;
        int cnt[5];

        Node(int k = 1) {
            prod = 1 % k;
            for (int i = 0; i < 5; i++) {
                cnt[i] = 0;
            }
        }
    };

    int n, k;
    vector<Node> tree;

    Node merge(Node &A, Node &B) {
        Node C(k);

        // Product of the complete segment
        C.prod = (A.prod * B.prod) % k;

        // Prefixes completely inside A
        for (int r = 0; r < k; r++) {
            C.cnt[r] += A.cnt[r];
        }

        // Prefixes which contain all of A
        // and then a prefix of B
        for (int r = 0; r < k; r++) {
            int newRem = (A.prod * r) % k;
            C.cnt[newRem] += B.cnt[r];
        }

        return C;
    }

    void build(int node, int l, int r, vector<int>& nums) {
        if (l == r) {
            tree[node].prod = nums[l] % k;
            tree[node].cnt[tree[node].prod] = 1;
            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid, nums);
        build(node * 2 + 1, mid + 1, r, nums);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int idx, int value) {
        if (l == r) {
            tree[node] = Node(k);

            tree[node].prod = value % k;
            tree[node].cnt[tree[node].prod] = 1;

            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid) {
            update(node * 2, l, mid, idx, value);
        } else {
            update(node * 2 + 1, mid + 1, r, idx, value);
        }

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    Node query(int node, int l, int r, int ql, int qr) {
        // No overlap
        if (qr < l || r < ql) {
            return Node(k);
        }

        // Complete overlap
        if (ql <= l && r <= qr) {
            return tree[node];
        }

        int mid = (l + r) / 2;

        Node left = query(node * 2, l, mid, ql, qr);
        Node right = query(node * 2 + 1, mid + 1, r, ql, qr);

        return merge(left, right);
    }

    vector<int> resultArray(vector<int>& nums,
                            int k,
                            vector<vector<int>>& queries) {

        this->n = nums.size();
        this->k = k;

        tree.resize(4 * n + 5);

        build(1, 0, n - 1, nums);

        vector<int> ans;

        for (auto &q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Persistent update
            update(1, 0, n - 1, index, value);

            // We need all prefixes of nums[start ... n-1]
            Node res = query(1, 0, n - 1, start, n - 1);

            ans.push_back(res.cnt[x]);
        }

        return ans;
    }
};