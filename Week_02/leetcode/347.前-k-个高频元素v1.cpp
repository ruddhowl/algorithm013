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
        set<int> barrel[size + 1];
        unordered_map<int, int> map;
        for(int i = 0; i < size; ++i) {
            if(map.find(nums[i]) == map.end()) map.insert(pair<int, int>(nums[i], 1));
            else map[nums[i]]++;
        }
        for(unordered_map<int, int>::iterator it = map.begin(); it != map.end(); it++) {
            barrel[it->second].insert(it->first);
        }
        for(int i = size; i > 0; --i) {
            if(!barrel[i].empty()) {
                for(set<int>::iterator it = barrel[i].begin(); it != barrel[i].end() && ans.size() < k; ++it) {
                    ans.push_back(*it);
                }
            }
        }
        return ans;
    }
};
// @lc code=end

