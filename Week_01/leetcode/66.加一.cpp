/*
 * @lc app=leetcode.cn id=66 lang=cpp
 *
 * [66] 加一
 */

// @lc code=start
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int size = digits.size(), i;
        for(i = size - 1; i >= 0; --i) {
            if(9 != digits[i]) {
                ++digits[i];
                break;
            } else {
                digits[i] = 0;
            }
        }
        if(i < 0) {
            digits[0] = 1;
            digits.push_back(0);
        }
        return digits;
    }
};;
// @lc code=end

