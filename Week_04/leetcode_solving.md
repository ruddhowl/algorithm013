### 深度优先和广度优先遍历

#### [102. Binary Tree Level Order Traversal](https://leetcode-cn.com/problems/binary-tree-level-order-traversal/)

虽然题目是层次遍历，但并没有限制遍历的方式，只要能得到最终的结果即可，所以不要被题目的名称限制了思维的发散性。

1、BFS

```C++
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(nullptr == root) return {};
        vector<vector<int>> res;
        queue<TreeNode*> que;
        que.push(root);
        while(!que.empty()) {
            res.push_back(vector<int>());
            for(int size = que.size(); size > 0; --size) {
                TreeNode* front = que.front();
                que.pop();
                res.back().push_back(front->val);
                if(front->left) que.push(front->left);
                if(front->right) que.push(front->right);
            }
        }
        return res;
    }
};
```

2、DFS

```C++
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(nullptr == root) return {};
        dfs(root, 0);
        return res;
    }
    void dfs(TreeNode* root, int level) {
        if(nullptr == root) return;
        if(level >= res.size()) res.push_back(vector<int>());
        res[level].push_back(root->val);
        dfs(root->left, level + 1);
        dfs(root->right, level + 1);
    }
};
```



#### [433. Minimum Genetic Mutation](https://leetcode-cn.com/problems/minimum-genetic-mutation/)



#### [22. Generate Parentheses](https://leetcode-cn.com/problems/generate-parentheses/)

1、DFS（对递归状态树的深度优先遍历）

2、BFS？



#### [200. Number of Islands](https://leetcode-cn.com/problems/number-of-islands/)

一开始的想法，另外创建一个辅助二维数组，记录岛屿是否被访问。但事实是没有必要这样做，直接把遍历到的位置置为0即可，题目没有限制不能改变传递过来的数组。应该先把一个题目的限制条件，搞清楚才是。

1、DFS

2、BFS



### 贪心

一种通过每一步的最优来达到总体最优的算法思想

#### [455. Assign Cookies](https://leetcode-cn.com/problems/assign-cookies/)

1、排序、贪心

C++

```C++
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        int gsize = g.size(), ssize = s.size();
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int g_idx = 0, s_idx = 0;
        while(g_idx < gsize && s_idx < ssize) {
            g[g_idx] <= s[s_idx] ? (++g_idx, ++s_idx) : ++s_idx;
        }
        return g_idx;
    }
};
```

#### [122. Best Time to Buy and Sell Stock II](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/)

1、三指针

这个思路中，股票的买卖次数最少，但题目没有要求这一点。

```C++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        int pre = 0, post = 1, low = -1, res = 0;
        while(post < size) {
            if(-1 == low) { //not set low_index
                if(prices[post] > prices[pre]) {
                    low = pre;
                }
            } else {
                if(prices[post] < prices[pre]) {
                    res += prices[pre] - prices[low];
                    low = -1;
                }
            }
            ++post;
            ++pre;
        }
        return (-1 == low) ? res : (res + prices[pre] - prices[low]);
    }
};
```

2、贪心

```C++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size(), res = 0;
        for(int pre = 0, post = 1; post < size; ++pre, ++post) {
            if(prices[post] > prices[pre]) res += prices[post] - prices[pre];
        }
        return res;
    }
};
```

#### [55. Jump Game](https://leetcode-cn.com/problems/jump-game/)

1、找零

题目要看清！只要到最后一个位置就可以了，所以最后一个位置的元素值不重要。

只有元素值为0的位置可能使得最终不能到达最后一个位置，所以从前往后遍历只要找到元素值为0的位置，就用一个内循环，往前遍历看能不能跳过该位置，如果不能直接返回false。

```C++
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int size = nums.size(), i;
        if(1 == size) return true; //corner case!!!
        for(i = size - 2; i >= 0; --i) { //size - 1 xxxxxx
            if(nums[i] == 0) {
                int tmp = i - 1;
                while(tmp >= 0 && nums[tmp] <= (i - tmp)) tmp--;
                if(tmp < 0) return false;
                i = tmp;
            }
        }
        return i < 0;
    }
};
```

2、贪心

遍历求解每个元素能达到的最远的位置，遍历的范围由当前已经遍历到的能达到的最远位置决定。

```C++
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int size = nums.size();
        int endpoint = 0;
        for(int i = 0; i <= endpoint && i < size; ++i) {
            if(i + nums[i] > endpoint) endpoint = nums[i] + i;
        }
        return endpoint >= size - 1;
    }
};
```

### 二分查找

#### [69. Sqrt(x)](https://leetcode-cn.com/problems/sqrtx/)

分析：平方根只会在（0，x）之间出现

1、迭代实现的二分查找

```C++
//测试数据：2147395599，integer overflow will happen if data type int used
class Solution {
public:
    int mySqrt(long long x) {
        long long left = 0, right = x, mid, pre, post;
        while(left <= right) {
            mid = (left + right) / 2;
            pre = mid * mid, post = (mid + 1) * (mid + 1);
            if(pre <= x && post > x) return mid;
            if(pre < x) left = mid + 1;
            if(pre > x) right = mid - 1;
        }
        return 0;
    }
};
```

2、牛顿迭代法

```C++
class Solution {
public:
    int mySqrt(long long x) {
        if(0 == x) return 0;
        double pre = x, cur = x;
        while(1) {
            cur = 0.5 * (pre + x / pre);
            if(fabs(cur - pre) < 1e-7) break;
            pre = cur;
        }
        return cur;
    }
};
```

```C++
/*
输入：2147395600
输出：46339
预期：46340
输入：5
结果：无限循环
*/
class Solution {
public:
    int mySqrt(long long x) {
        long long res = x, tmp = x * x;
        while(tmp > x) {
            res = res / 2 + x / (2 * res);
            tmp = res * res;
        }
        return res;
    }
};
```



3、快指针

参考shell排序的思路，通过一次跳的更远来加快求得答案的速度，但在这道题上，并不能有效降低数量级，还会导致处理小数值的时候消耗更多的计算资源。

#### [33. Search in Rotated Sorted Array](https://leetcode-cn.com/problems/search-in-rotated-sorted-array/)

要求时间复杂度不高于O(logn)

1、二分查找找分界点、递归实现二分查找

利用修改判断条件的二分查找找到分界点、然后把数组恢复成单调有序的状态，恢复的时间复杂度为O(n)，这个解法很麻烦，是我故意为之，目的是处理更多的边界情况，涉及更多的知识点。

C++

```C++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int size = nums.size();
        int boundaryIndex = findBoundary(nums, 0, size - 1);
        recoverArray(nums, boundaryIndex);
        for(int i = 0; i < size; i++) {
            printf("%d ", nums[i]);
        }
        int res = findTarget(nums, target, 0, size - 1);
        return (res == -1) ? res : (res + boundaryIndex) % size;
    }
    int findBoundary(vector<int>& nums, int left, int right) {
        if(right < left) return 0;
        int tmp = (left + right) / 2;
        if(tmp == 0) return (right == 0) ? 0 : (nums[1] < nums[0] ? 1 : 0);
        if(nums[tmp] < nums[tmp - 1]) return tmp;
        if(nums[tmp] < nums[0]) return findBoundary(nums, left, tmp - 1);
        else return findBoundary(nums, tmp + 1, right);
    }
    void recoverArray(vector<int>& nums, int boundary) { //时间复杂度O(n)
        overturnArray(nums, 0, boundary - 1);
        overturnArray(nums, boundary, nums.size() - 1);
        overturnArray(nums, 0, nums.size() - 1);
    }
    void overturnArray(vector<int>& nums, int left, int right) {
        for(int tmp; left < right; ++left, --right) {
            tmp = nums[left];
            nums[left] = nums[right];
            nums[right] = tmp;
        }
    }
    int findTarget(vector<int>& nums, int target, int left, int right) {
        if(left > right) return -1;
        int tmp = (left + right) / 2;
        if(nums[tmp] == target) return tmp;
        if(nums[tmp] < target) return findTarget(nums, target, tmp + 1, right);
        if(nums[tmp] > target) return findTarget(nums, target, left, tmp - 1);
        return -1;
    }
};
```

2、二分查找

利用修改判断条件的二分查找直接找目标元素

判断条件通过列举所有情况求得，没有找到捷径之前，那就用最朴素的方法来获取答案，这才是更经济的选择。

```C++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        return binarySearch(nums, target, 0, nums.size() - 1);
    }
    int binarySearch(vector<int>& nums, int target, int left, int right) {
        if(left > right) return -1;
        if(left == right) return (nums[left] == target) ? left : -1;
        int tmp = (left + right) / 2;
        if(nums[tmp] == target) return tmp;
        if(nums[tmp] > nums[0] && target <= nums[tmp] && target >= nums[0] || (nums[tmp] < nums[0] && ((target > nums[tmp] && target >= nums[0]) || target < nums[tmp]))) return binarySearch(nums, target, left, tmp - 1);
        else return binarySearch(nums, target, tmp + 1, right);
        return -1;
    }
};
```