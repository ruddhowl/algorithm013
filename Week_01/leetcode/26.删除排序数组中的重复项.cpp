/*
 * @lc app=leetcode.cn id=26 lang=cpp
 *
 * [26] 删除排序数组中的重复项
 */

// @lc code=start
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int size = nums.size();
        if(0 == size) return 0;
        int tmp = 0;
        int cnt = 1;
        for(int i = 1; i < size; ++i) {
            if(nums[i] != nums[tmp]) {
                nums[++tmp] = nums[i];
                ++cnt;
            }
        }
        return cnt;
    }
};;
// @lc code=end

