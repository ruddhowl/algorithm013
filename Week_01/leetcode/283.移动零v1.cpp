/*
 * @lc app=leetcode.cn id=283 lang=cpp
 *
 * [283] 移动零
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
       int size = nums.size();
       int tmp = 0;
       for(int i = 0; i < size; ++i) {
           if(nums[i] != 0)
               nums[tmp++] = nums[i];
       }
       while (tmp < size) nums[tmp++] = 0;
    }
};
// @lc code=end

