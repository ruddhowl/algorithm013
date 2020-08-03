/*
 * @lc app=leetcode.cn id=42 lang=cpp
 *
 * [42] 接雨水
 */

// @lc code=start
class Solution {
public:
    int trap(vector<int>& height) {
        int size = height.size();
        int ans = 0;
        for(int i = 0; i < size; ++i) {
            int lmax, rmax;
            lmax = rmax = height[i];
            for(int j = i - 1; j >= 0; --j) {
                if(height[j] > lmax) lmax = height[j];
            }
            for(int j = i + 1; j < size; ++j) {
                if(height[j] > rmax) rmax = height[j];
            }
            ans += ((lmax > rmax) ? lmax : rmax) - height[i]; 
        }
        return ans;
    }
};
// @lc code=end

