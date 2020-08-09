/*
 * @lc app=leetcode.cn id=347 lang=cpp
 *
 * [347] 前 K 个高频元素
 */

// @lc code=start
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int size = nums.size();
        vector<int> ans;
        unordered_map<int, int> map;
        priority_queue<pair<int,int> > que;
        for(int i = 0; i < size; ++i) {
            if(map.find(nums[i]) == map.end()) map.insert(pair<int, int>(nums[i], 1));
            else map[nums[i]]++;
        }
        for(unordered_map<int, int>::iterator it = map.begin(); it != map.end(); it++) que.push({it->second, it->first});
        while(k--) {
            ans.push_back(que.top().second);
            que.pop();
        }
        return ans;
    }
};
// @lc code=end

