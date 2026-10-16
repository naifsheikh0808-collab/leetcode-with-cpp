
class Solution {
    using ll = long long;
    static const ll MOD = 1'000'000'007;

    struct Node {
        ll sum = 0;
        ll sumSq = 0;
        ll lazy = 0;
    };

    vector<Node> tree;
    int n;

    void apply(int node, int l, int r, ll val) {
        ll len = r - l + 1;
        ll oldSum = tree[node].sum;

        tree[node].sumSq =
            (tree[node].sumSq
             + 2 * val % MOD * oldSum % MOD
             + val * val % MOD * len % MOD) % MOD;

        tree[node].sum =
            (oldSum + val * len) % MOD;

        tree[node].lazy =
            (tree[node].lazy + val) % MOD;
    }

    void push(int node, int l, int r) {
        if (tree[node].lazy == 0 || l == r)
            return;

        int mid = l + (r - l) / 2;
        ll val = tree[node].lazy;

        apply(node * 2, l, mid, val);
        apply(node * 2 + 1, mid + 1, r, val);

        tree[node].lazy = 0;
    }

    void update(int node, int l, int r,
                int ql, int qr, ll val) {
        if (qr < l || r < ql)
            return;

        if (ql <= l && r <= qr) {
            apply(node, l, r, val);
            return;
        }

        push(node, l, r);

        int mid = l + (r - l) / 2;

        update(node * 2, l, mid, ql, qr, val);
        update(node * 2 + 1, mid + 1, r, ql, qr, val);

        tree[node].sum =
            (tree[node * 2].sum
             + tree[node * 2 + 1].sum) % MOD;

        tree[node].sumSq =
            (tree[node * 2].sumSq
             + tree[node * 2 + 1].sumSq) % MOD;
    }

    ll query(int node, int l, int r,
             int ql, int qr) {
        if (qr < l || r < ql)
            return 0;

        if (ql <= l && r <= qr)
            return tree[node].sumSq;

        push(node, l, r);

        int mid = l + (r - l) / 2;

        return (query(node * 2, l, mid, ql, qr)
              + query(node * 2 + 1, mid + 1, r,
                      ql, qr)) % MOD;
    }

public:
    int sumCounts(vector<int>& nums) {
        n = nums.size();
        tree.assign(4 * n, Node());

        vector<int> last(100001, -1);
        ll ans = 0;

        for (int i = 0; i < n; i++) {
            int prev = last[nums[i]];

            // Add 1 to distinct counts of affected subarrays.
            update(1, 0, n - 1, prev + 1, i, 1);

            // Sum squares of all subarrays ending at i.
            ans = (ans + query(1, 0, n - 1, 0, i))
                  % MOD;

            last[nums[i]] = i;
        }

        return (int)ans;
    }
};
