## 第九周

### 高级动态规划

#### [746. Min Cost Climbing Stairs](https://leetcode-cn.com/problems/min-cost-climbing-stairs/)

1、
$$
\begin{cases}
dp[i] = min(dp[i - 2] + cost[i],\ dp[i - 1] + cost[i]);
\end{cases}
$$


```C++
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int size = cost.size();
        if(0 == size) return 0;
        if(1 == size) return cost[0];
        if(2 == size) return min(cost[0], cost[1]);
        vector<int> dp;
        dp.resize(size);
        dp[0] = cost[0]; dp[1] = cost[1];
        for(int i = 2; i < size; ++i) {
            dp[i] = min(dp[i - 2], dp[i - 1]) + cost[i];
        }
        return min(dp[size - 1], dp[size - 2]);
    }
};
```



#### [72. Edit Distance](https://leetcode-cn.com/problems/edit-distance/)

1、动态规划
$$
\begin{cases}
dp[i][j] = dp[i - 1][j - 1]; &word1[i] == word2[j]\\
dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1; & word1[i] != word2[j]
\end{cases}
$$


```C++
class Solution {
public:
    int minDistance(string word1, string word2) {
        int size1 = word1.size(), size2 = word2.size();
        // boundry condition
        if(0 == size1) return size2;
        else if(0 == size2) return size1;
        vector<vector<int>> dp(size2, vector<int>(size1, 0));
        // set boundry
        bool is_same_word_found = false;
        for(int i = 0; i < size1; ++i) { // 这里可以不用这么复杂
            if(word1[i] != word2[0] && !is_same_word_found) {
                dp[0][i] = i + 1;
            } else {
                is_same_word_found = true;
                dp[0][i] = i;
            }
            printf("%d ", dp[0][i]);
        }
        printf("\n");
        is_same_word_found = false;
        for(int i = 0; i < size2; ++i) {
            if(word1[0] != word2[i] && !is_same_word_found) {
                dp[i][0] = i + 1;
            } else {
                is_same_word_found = true;
                dp[i][0] = i;
            }
            printf("%d ", dp[i][0]);
        }
        printf("\n");
        for(int i = 1; i < size2; ++i) { // 这里的遍历顺序违背了程序的局部性原理，需要改进
            for(int j = 1; j < size1; ++j) {
                if(word1[j] == word2[i]) dp[i][j] = dp[i - 1][j - 1];
                else dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
                printf("%d ", dp[i][j]);
            }
            printf("\n");
        }
        return dp[size2 - 1][size1 - 1];
    }
};
```



#### [300. Longest Increasing Subsequence](https://leetcode-cn.com/problems/longest-increasing-subsequence/)

1、暴力、两重循环、从前往后、错误解法

```C++
// [10,9,2,5,3,4]
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int size = nums.size(), res = 1, max;
        if(0 == size) return 0;
        for(int i = 0; i < size - 1; ++i) {
            int tmp = nums[i]; max = 1;
            for(int j = i + 1; j < size; ++j) {
                if(nums[j] > tmp) {
                    tmp = nums[j];
                    ++max;
                }
            }
            if(max > res) res = max;
        }
        return res;
    }
};
```



2、两层循环、从后往前、数组记录每一个从头开始的序列的LIS

```C++
// [1,3,6,7,9,4,10,5,6]
// 又是错误解法！
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int size = nums.size(), res = 1;
        if(0 == size) return 0;
        vector<int> dp(size, 1);
        for(int i = 1; i < size; ++i) {
            int tmp = nums[i];
            for(int j = i - 1; j >= 0; --j) {
                if(nums[j] < tmp) {
                    dp[i] = dp[j] + 1;
                    break;
                }
            }
            if(dp[i] > res) res = dp[i];
        }
        return res;
    }
};
```

3、动态规划
$$
dp数组记录序列中每个数所对应的最大长度 \\
dp[i] = max(dp[j]) + 1;\ 0 <= j < i， nums[j] < nums[i]
$$


```C++
// 终于对了
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int size = nums.size(), res = 1;
        if(0 == size) return 0;
        vector<int> dp(size, 1);
        for(int i = 1; i < size; ++i) {
            int tmp = nums[i];
            for(int j = i - 1; j >= 0; --j) {
                if(nums[j] < tmp && dp[i] < dp[j] + 1) {
                    dp[i] = dp[j] + 1;
                }
            }
            if(dp[i] > res) res = dp[i];
        }
        return res;
    }
};
```

4、贪心、二分查找

下次把草稿本带上，找一个简单样例，画图，这样更容易发现规律

len数组记录每一个长度所对应的目前遍历过的最小值

```C++
class Solution {
    int binary_search(vector<int>& nums, int target, int l, int r) {
        if(l > r) return -1;
        int tmp = (l + r) / 2;
        if(tmp == r && nums[tmp] < target) return tmp;
        if(tmp < r && nums[tmp] < target && nums[tmp + 1] >= target) return tmp;
        if(nums[tmp] >= target) return binary_search(nums, target, l, tmp - 1);
        if(nums[tmp] < target) return binary_search(nums, target, tmp + 1, r);
        return -1;
    }
public:
    int lengthOfLIS(vector<int>& nums) {
        int size = nums.size(), post = 0;
        if(0 == size) return 0;
        vector<int> len(size, nums[0]);
        for(int i = 1; i < size; ++i) {
            int idx = binary_search(len, nums[i], 0, post);
            if(len[post] < nums[i]) idx = post;
            else if(len[0] > nums[i]) len[0] = nums[i];
            if(-1 != idx) {
                if(idx == post) {
                    ++post;
                    len[post] = nums[i];
                }
                else if(len[idx + 1] > nums[i]) len[idx + 1] = nums[i];
            }
        }
        return post + 1;
    }
};
```



#### [91. Decode Ways](https://leetcode-cn.com/problems/decode-ways/)

1、递归

```C++
class Solution {
    int res = 0;
public:
    int numDecodings(string s) {
        if(s.size() == 0) return 0;
        recur(s, -1);
        return res;
    }
    void recur(string s, int l) {
        int size = s.size();
        if(l == size - 1) ++res;
        else if(l > size) return;
        else {
            if(s[l + 1] != '0') recur(s, l + 1);
            if((s[l + 1] != '0' && s[l + 1] != '0') && l < size - 2 && ((s[l + 1] < '2') || (s[l + 1] == '2' && s[l + 2] <= '6'))) recur(s, l+ 2);
        }
    }
};
```

2、动态规划、错误版本
$$
\begin{cases}
dp[i] = dp[i - 1];\\
dp[i] = dp[i - 1] + dp[i - 2]; (s[i - 1] < '2') || (s[i - 1] == '2'\ \&\&\ s[i] <= '6')
\end{cases}
$$
输入："10"

输出：0

预期：1

"10"可以解码成J

‘0’只是无法单独解码

```C++
class Solution {
public:
    int numDecodings(string s) {
        int size = s.size();
        if(0 == size) return 0;
        for(int i = 0; i < size; ++i) if(s[i] == '0') return 0;
        if(1 == size) return 1;
        vector<int> dp(size, 0);
        if(2 <= size) {
            dp[0] = 1;
            dp[1] = (s[0] < '2' || s[0] == '2' && s[1] <= '6') ? 2 : 1;
        }
        for(int i = 2; i < size; ++i) {
            if(s[i - 1] < '2' || s[i - 1] == '2' && s[i] <= '6') dp[i] = dp[i - 1] + dp[i - 2];
            else dp[i] = dp[i - 1];
        }
        return dp[size - 1];
    }
};
```

3、动态规划

前面的解法错误的原因都是因为审题不清

```c++
class Solution {
public:
    int numDecodings(string s) {
        int size = s.size();
        if(0 == size) return 0;
        if(1 == size) return s[0] == '0' ? 0 : 1;
        vector<int> dp(size, 0);
        if(2 <= size) {
            if(s[0] == '0') return 0;
            dp[0] = 1;
            if(s[1] != '0') dp[1] = (s[0] < '2' || s[0] == '2' && s[1] <= '6') ? 2 : 1;
            else if(s[0] > '2') return 0;
            else dp[1] = 1;
        }
        for(int i = 2; i < size; ++i) {
            if(s[i] == '0') {
                if(s[i - 1] > '0' && s[i - 1] <= '2') dp[i] = dp[i - 2];
                else return 0;
            }
            else if(s[i - 1] != '0' && s[i - 1] < '2' || s[i - 1] == '2' && s[i] <= '6') dp[i] = dp[i - 1] + dp[i - 2];
            else dp[i] = dp[i - 1];
        }
        return dp[size - 1];
    }
};
```

