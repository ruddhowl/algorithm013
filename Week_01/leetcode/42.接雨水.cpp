/*
 * @lc app=leetcode.cn id=42 lang=cpp
 *
 * [42] 接雨水
 */

// @lc code=start
class Solution {
public:
    int trap(vector<int>& height) {
        int size = height.size(), ans = 0, next;
        int left = 0, right = size - 1;
        while(left < right) {
            if(height[left] < height[right]) {
                for(next = left + 1; next < right && height[next] <= height[left]; ++next) {
                    ans += height[left] - height[next];
                }
                left = next;
            } else {
                for(next = right - 1; next > left && height[next] <= height[right]; --next) {
                    ans += height[right] - height[next];
                }
                right = next;
            }
        }
        return ans;
    }
};
// @lc code=end

