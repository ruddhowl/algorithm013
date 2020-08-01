/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
 */

// @lc code=start
#include <vector>
#include <map>
using namespace std;
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int size = nums.size();
        map<int, int> m;
        vector<int> r;
        for(int i = 1; i < size; ++i)
        {
            m[nums[i]] = i; 
        }
        for(int i = 0, dif = target - nums[0]; i < size; ++i, dif = target - nums[i])
        {
            if(m[dif] && m[dif] != i)
            {
                r.push_back(i);
                r.push_back(m[target - nums[i]]);
                return r;
            }
        }
        return r;
    }
};
// @lc code=end

