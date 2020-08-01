/*
 * @lc app=leetcode.cn id=21 lang=cpp
 *
 * [21] 合并两个有序链表
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l1 == nullptr || l2 == nullptr) {
            if(l1 != nullptr) return l1;
            else return l2;
        }
        ListNode* ans = (l1->val <= l2->val) ? l1 : l2;
        ListNode tt;
        ListNode* pre = tt;
        pre->next = l1;
        ListNode* tmp;
        while(l1 != nullptr && l2 != nullptr) {
            if(l1->val <= l2->val) {
                pre = l1;
                l1 = l1->next;
            }
            else {
                tmp = l2;
                l2 = l2->next;
                tmp->next = pre->next;
                pre->next = tmp;
                pre = tmp;
            }
        }
        if(l1 == nullptr) pre->next = l2;
        return ans;
    }
};;
// @lc code=end

