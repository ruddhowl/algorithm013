/*
 * @lc app=leetcode.cn id=61 lang=cpp
 *
 * [61] 旋转链表
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int size = nums.size();
        k %= size;
        int pre, cur, cnt = 0;
        //int m = size % k;
        //for循环的执行次数不会超过m次
        for(int start = 0; cnt < size; ++start) {
            cur = start;
            pre = nums[start];
            do {
                cur = (cur + k) % size;
                swap(pre, nums[cur]);
                ++cnt;
            } while(cur != start);
        }
        return; 
    }
};
// @lc code=end

