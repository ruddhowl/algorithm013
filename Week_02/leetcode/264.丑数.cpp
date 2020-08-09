/*
 * @lc app=leetcode.cn id=264 lang=cpp
 *
 * [264] 丑数 II
 */

// @lc code=start
class Solution {
public:
    int nthUglyNumber(int n) {
		set<int> set;
        set.insert(1);
        priority_queue<long, vector<long>, greater<long>> que;
        que.push(1);
        long top;
        int ugly[] = {2, 3, 5};
        for(int i = 0; i < n; ++i) {
            top = que.top();
            que.pop();
            for(auto a : ugly) {
                long tmp = a * top;
                if(!set.count(tmp)) {
                    set.insert(tmp);
                    que.push(tmp);
                }
            }
        }
        return top;
    }
};
// @lc code=end

