/*
 * @lc app=leetcode.cn id=42 lang=cpp
 *
 * [42] 接雨水
 */

// @lc code=start
class Solution {
public:
    int trap(vector<int>& height) {
        int size = height.size(), ans = 0;
        stack<int> stack;
        stack.push(0);
        for(int i = 1; i < size; ++i) {
            if(height[stack.top()] > height[i]) stack.push(i);
            else if(height[stack.top()] < height[i]) {
                int acc = 0, top, pre = i;
                while(!stack.empty() && (height[top = stack.top()] <= height[i])) {
                    stack.pop();
                    acc += (pre - top) * height[top];
                    pre = top;
                }
                if(stack.empty()) {
                    ans += height[top] * (i - top) - acc;
                    stack.push(i);
                } else {
                    ans += height[i] * (i - pre) - acc;
                    height[pre] = height[i];
                    stack.push(pre);
                }
            }
        }
        return ans;
    }
};
// @lc code=end

