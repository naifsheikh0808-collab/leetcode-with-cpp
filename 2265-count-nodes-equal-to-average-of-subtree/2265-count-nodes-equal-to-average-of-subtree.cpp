class Solution {
public:
    int ans = 0;

    // Returns {sum of subtree, number of nodes in subtree}
    pair<int, int> dfs(TreeNode* root) {
        if (root == nullptr)
            return {0, 0};

        auto left = dfs(root->left);
        auto right = dfs(root->right);

        int sum = root->val + left.first + right.first;
        int count = 1 + left.second + right.second;

        // Integer division gives floor(sum / count)
        if (root->val == sum / count)
            ans++;

        return {sum, count};
    }

    int averageOfSubtree(TreeNode* root) {
        dfs(root);
        return ans;
    }
};