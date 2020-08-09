/*
 * @lc app=leetcode.cn id=429 lang=cpp
 *
 * [429] N叉树的层序遍历
 */

// @lc code=start
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<vector<int>> result;
    vector<vector<int>> levelOrder(Node* root) {
        if (root == nullptr) {
            return result;
        }
        result.emplace_back(vector<int>{root->val});
        queue<Node*> que;
        que.push(root);
        
        while (!que.empty()) {
            int queSize = que.size();
            vector<int> vec;
            for (int i = 0; i < queSize; ++i) {
                auto element = que.front();
                que.pop();
                for (auto x : element->children) {
                    vec.emplace_back(x->val);
                    que.push(x);
                }
            }
            if (vec.size() > 0) {
                result.emplace_back(vec);
            }
        }
        return result;
    }
};
// @lc code=end

