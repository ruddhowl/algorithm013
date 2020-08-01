/*
 * @lc app=leetcode.cn id=70 lang=cpp
 *
 * [70] 爬楼梯
 */

// @lc code=start
int level[1000] = {0};
class Solution {
public:
    int climbStairs(int n) {
        if(1 == n) return level[1] = 1;
        else if(2 == n) return level[2] = 2;
        else return ((level[n - 2] != 0) ? level[n - 2] : (level[n - 2] = climbStairs(n - 2))) + ((level[n - 1] != 0) ? level[n - 1] : (level[n - 1] = climbStairs(n - 1)));
    }
};
// @lc code=end

