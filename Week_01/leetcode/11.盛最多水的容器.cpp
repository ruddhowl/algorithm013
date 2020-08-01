/*
 * @lc app=leetcode.cn id=11 lang=cpp
 *
 * [11] 盛最多水的容器
 */

// @lc code=start
#include <vector>
using namespace std;
/*
*思路：
*步骤：
*定义两个bool类型的标记数组
*从数组两端分别往相反的方向遍历，
*各自用一个辅助变量记录遍历到当前索引所遇到的最大值，
*在遍历的过程中，每当遇到比辅助变量记录的值更大的元素的时候，
*把标记数组对应索引位置的元素设为true，同时更新辅助变量
*/
class Solution {
public:
    int maxArea(vector<int>& height) {
        int size = height.size();
        vector<int> index, rindex;
        index.push_back(0);
        rindex.push_back(size - 1);
        int tmp = height[0], rtmp = height[size - 1];
        for(int i = 1; i < size; ++i)
        {
            if(tmp < height[i])
            {
                index.push_back(i);
                tmp = height[i];
            }
        }
        for(int i = size -2; i >= 0; --i)
        {
            if(rtmp < height[i])
            {
                rindex.push_back(i);
                rtmp = height[i];
            }
        }
        int area = 0;
        int len = index.size(), rlen = rindex.size();
        for(int i = 0; i < len; ++i)
        {
            for(int j = 0; j < rlen && rindex[j] > index[i]; ++j)
            {
                int tmp, min = height[index[i]] < height[rindex[j]] ? height[index[i]] : height[rindex[j]];
                area = area > (tmp = (rindex[j] - index[i]) * min) ? area : tmp;
            }
        }
        return area;
    }
};
// @lc code=end

