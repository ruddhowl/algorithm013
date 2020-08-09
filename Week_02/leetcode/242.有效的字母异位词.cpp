/*
 * @lc app=leetcode.cn id=242 lang=cpp
 *
 * [242] 有效的字母异位词
 */

// @lc code=start
class Solution {
public:
    bool isAnagram(string s, string t) {
        int ssize = s.size(), tsize = t.size();
        if(ssize != tsize) return false;
        int map[128] = {0};//unicodezi->65535
        for(int i = 0; i < ssize; ++i) {
            map[s[i]] += 1;
        }
        for(int i = 0; i < ssize; ++i) {
			if((map[t[i]] -= 1) == -1) return false;
        }
        return true;
    }
};
// @lc code=end

