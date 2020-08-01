/*
 * @lc app=leetcode.cn id=70 lang=cpp
 *
 * [70] 爬楼梯
 */

// @lc code=start
class Solution {
public:
    int climbStairs(int n) {
        if(1 == n) return 1;
        else if(2 == n) return 2;
        else return climbStairs(n - 1) + climbStairs(n - 2);
    }
};
// @lc code=end

