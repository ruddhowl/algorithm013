/*
 * @lc app=leetcode.cn id=283 lang=cpp
 *
 * [283] 移动零
 */

// @lc code=start
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int size = nums.size();
        int i = 0, j = 0;
        for(; j < size; ++j) {
            if(nums[j] != 0) {
                if(i != j) {
                    nums[i] = nums[j];
                    nums[j] = 0;
                }
                ++i;
            }
        }
    }
};
// @lc code=end

