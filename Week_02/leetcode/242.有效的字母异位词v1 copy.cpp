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
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        for(int i = 0; i < ssize; ++i) {
            if(s[i] != t[i]) return false;
		}
        return true;
    }
};
// @lc code=end

