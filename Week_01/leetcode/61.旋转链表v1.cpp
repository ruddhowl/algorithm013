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
    void reverse(vector<int>& nums, int i, int j)
    {
        while(i < j) {
            swap(nums[i++], nums[j--]);
        }
    }
    void rotate(vector<int>& nums, int k) {
        int size = nums.size();
        k %= size;
        reverse(nums, 0, size - k - 1);
        reverse(nums, size - k, size - 1);
        reverse(nums, 0, size - 1);
        return; 
    }
};
// @lc code=end

