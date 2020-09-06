## 第六周

#### [62. Unique Paths](https://leetcode-cn.com/problems/unique-paths/)

1、分治

```C++
class Solution {
    int res = 0;
public:
    int uniquePaths(int m, int n) {
        recur(m, n, 1, 1);
        return res;
    }
    void recur(int m, int n, int i, int j) {
        if(i == m && j == n) {
            ++res;
            return;
        }
        if(i < m) recur(m, n, i + 1, j);
        if(j < n) recur(m, n, i, j + 1);
    }
};
```

2、分治优化、记录中间结果

```C++
class Solution {
    int tmp[100][100] = {0};
public:
    int uniquePaths(int m, int n) {
        return recur(m, n, 1, 1);
    }
    int recur(int m, int n, int i, int j) {
        if(i == m || j == n) return 1;
        if(tmp[i][j] == 0) return tmp[i][j] = recur(m, n, i + 1, j) + recur(m, n, i, j + 1);
        else return tmp[i][j];
    }
};
```

3、动态规划

```C++
// Derivation: dp[i][j] = dp[i + 1][j] + dp[i][j + 1]
class Solution {
    int dp[101][101] = {0};
public:
    int uniquePaths(int m, int n) {
        for(int i = 1; i <= n; ++i) dp[i][m] = 1;
        for(int i = 1; i <= m; ++i) dp[n][i] = 1;
        for(int i = n - 1; i >= 1; --i) {
            for(int j = m - 1; j >= 1; --j) {
                dp[i][j] = dp[i + 1][j] + dp[i][j + 1];
            }
        }
        return dp[1][1];
    }
};
```

4、动态规划、滚动数组、时间换空间

```C++
// int dp[][] = new int[2][m]; //???
// int[][] dp = new int[m][n];
class Solution {
    int dp[2][100] = {0};
public:
    int uniquePaths(int m, int n) {
        int pre = (n - 1) % 2, cur = 0;
        for(int i = 0; i < m; ++i) dp[pre][i] = 1;
        dp[n % 2][m - 1] = 1;
        for(int i = n - 2; i >= 0; --i) {
            for(int j = m - 2; j >= 0; --j) {
                cur = i % 2; pre = (i + 1) % 2;
                dp[cur][j] = dp[pre][j] + dp[cur][j + 1];
            }
        }
        return dp[cur][0];
    }
};
```

```python
class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        cur = [1] * n
        for i in range(1, m):
            for j in range(1, n):
                cur[j] += cur[j-1]
        return cur[-1]
```



#### [63. Unique Paths II](https://leetcode-cn.com/problems/unique-paths-ii/)

1、动态规划

C++

```C++
class Solution {
    long dp[100][100] = {0};
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        for(int i = n - 1; i >= 0 && obstacleGrid[m - 1][i] == 0; --i) dp[m - 1][i] = 1;
        for(int i = m - 1; i >= 0 && obstacleGrid[i][n - 1] == 0; --i) dp[i][n - 1] = 1;
        for(int i = m - 2; i >= 0; --i) {
            for(int j = n - 2; j >= 0; --j) {
                if(obstacleGrid[i][j] == 0) dp[i][j] = dp[i + 1][j] + dp[i][j + 1];
            }
        }
        
        return dp[0][0];
    }
};
```

2、动态规划、空间优化、滚动数组

java

```java
public int uniquePathsWithObstacles(int[][] obstacleGrid) {
    int width = obstacleGrid[0].length;
    int[] dp = new int[width];
    dp[0] = 1;
    for (int[] row : obstacleGrid) {
        for (int j = 0; j < width; j++) {
            if (row[j] == 1)
                dp[j] = 0;
            else if (j > 0)
                dp[j] += dp[j - 1];
        }
    }
    return dp[width - 1];
}
```



#### [1143. Longest Common Subsequence](https://leetcode-cn.com/problems/longest-common-subsequence/)

两个字符串对应二维数组

1、暴力解、递归回溯找出其中一个字符串的所有子序列

枚举所有子序列

T: O(2^m); S: O(m)

```C++
class Solution {
    int res = 0;
    string tmp;
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(), n = text2.size();
        if(m == 0 || n == 0) return 0;
        backtrace(text1, text2, 0, m, n);
        return res;
    }
    void backtrace(string& text1, string& text2, int level, int m, int n) {
        if(level == m) {
            int idx = 0, size = tmp.size();
            for(int i = 0; i < n && idx < size; ++i) {
                if(tmp[idx] == text2[i]) ++idx;
            }
            if(idx == size && res < size) res = size;
            return; //记得加上啊！
        }
        backtrace(text1, text2, level + 1, m, n);
        tmp.push_back(text1[level]);
        backtrace(text1, text2, level + 1, m, n);
        tmp.pop_back();
    }
};
```

2、动态规划
$$
dp[i][j] = 
\begin{cases}
dp[i - 1][j - 1], &text1[i - 1]\ ==\ text2[j - 1]\\
max(dp[i - 1][j],\ dp[i][j - 1]), &text1[i - 1]\ !=\ text2[j - 1]\\
\end{cases}
$$
T: O(mn); S: O(mn)

```C++
class Solution {
    int dp[1001][1001] = {0};
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(), n = text2.size();
        if(m == 0 || n == 0) return 0;
        for(int i = 1; i <= m; ++i) {
            for(int j = 1; j <= n; ++j) {
                if(text1[i - 1] == text2[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
                else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[m][n];
    }
};
```

#### [70. Climbing Stairs](https://leetcode-cn.com/problems/climbing-stairs/)

1、动态规划
$$
dp[i] = dp[i - 1] + dp[i -2]
$$

```C++
class Solution {
public:
    int climbStairs(int n) {
        if(0 == n || 1 == n) return 1;
        int dp[3] = {1,1};
        for(int i = 2; i <= n; ++i) {
            dp[2] = dp[0] + dp[1];
            dp[0] = dp[1];
            dp[1] = dp[2];
        }
        return dp[2];
    }
};
```



#### [120. Triangle](https://leetcode-cn.com/problems/triangle/)

1、动态规划、滚动数组

T: O(n^2); S: O(n)

vector<vector<int>> dp = triangle;
$$
dp[i][j]\ =\ dp[i][j]\ +\ min(dp[i + 1][j],\ dp[i + 1][j + 1])
$$

```C++
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int size = triangle.size();
        vector<int> dp;
        dp.resize(size + 1);
        for(int i = size - 1; i >= 0; --i) {
            for(int j = 0; j <= i; ++j) {
                dp[j] = triangle[i][j] + min(dp[j], dp[j + 1]);
            }
        }
        return dp[0];
    }
};
```

#### [53. Maximum Subarray](https://leetcode-cn.com/problems/maximum-subarray/)

1、遍历

```C++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int size = nums.size(), res = INT_MIN, sum = INT_MIN;
        for(int i = 0; i < size; ++i) {
            if(sum < 0) sum = nums[i];
            else if(sum >= 0) sum += nums[i];
            if(sum > res) res = sum;
        }
        return res;
    }
};
```

2、动态规划
$$
dp = max(dp + nums[i], nums[i])
$$


```C++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int size = nums.size(), res = INT_MIN, dp = -1;
        for(int i = 0; i < size; ++i) {
            dp = max(dp + nums[i], nums[i]);
            if(dp > res) res = dp;
        }
        return res;
    }
};
```



#### [152. Maximum Product Subarray](https://leetcode-cn.com/problems/maximum-product-subarray/)

1、动态规划、滚动数组

T: O(n); S: O(1)
$$
\begin{cases}
minus = min(plus * nums[i], nums[i]),\ plus = max(minus * nums[i], 0), &nums[i] < 0\\
minus = min(minus * nums[i], 0),\ plus = max(plus * nums[i], nums[i]), &nums[i] >= 0
\end{cases}
$$


```C++
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int size = nums.size(), minus = 0, plus = 0, res = INT_MIN;
        if(size == 1) return nums[0];
        for(int i = 0; i < size; ++i) {
			if(nums[i] < 0) { // 增加这个判断，虽然会增加代码的长度，但是可以避免不必要的乘法计算
                int preminus = minus;
                minus = min(plus * nums[i], nums[i]);
                plus = max(preminus * nums[i], 0);
            } else {
                minus = min(minus * nums[i], 0);
                plus = max(plus * nums[i], nums[i]);
            }
            if(plus > res) res = plus;
        }
        return res;
    }
};
```

```C++
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int size = nums.size(), minus = nums[0], plus = nums[0], res = nums[0];
        for(int i = 1; i < size; ++i) {
            int preminus = minus, preplus = plus;
            minus = min(preplus * nums[i], min(preminus * nums[i], nums[i]));
            plus = max(preplus * nums[i], max(preminus * nums[i], nums[i]));
            if(plus > res) res = plus;
        }
        return res;
    }
};
```

#### [322. Coin Change](https://leetcode-cn.com/problems/coin-change/)

1、错误解法：贪心

```C++
/*
input:
[3,11]
29
output: -1
expect: 7
*/
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        sort(coins.begin(), coins.end());
        int size = coins.size(), left = amount, res = 0;
        for(int i = size - 1; i >= 0 && left > 0; --i) {
            res += left / coins[i];
            left %= coins[i];
        }
        return (left == 0) ? res : -1;
    }
};
```

2、动态规划（完全背包问题）
$$
dp[i][s] = min(dp[i - 1][s], dp[i][s - coins[i]] + 1)
$$

```C++
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        if(amount == 0) return 0;
        // sort(coins.rbegin(), coins.rend());
        int size = coins.size();
        vector<vector<int>> dp(size, vector<int>(amount + 1, -1));
        for(int i = 0, sum = 0; sum <= amount; sum = ++i * coins[0]) dp[0][sum] = i;
        for(int i = 0; i < size; ++i) dp[i][0] = 0;
        for(int i = 1; i < size; ++i) {
            for(int j = 1; j <= amount; ++j) {
                if(j < coins[i]) {
                    dp[i][j] = dp[i - 1][j];
                } else if(dp[i - 1][j] != -1 && dp[i][j - coins[i]] != -1) {
                    dp[i][j] = min(dp[i - 1][j], dp[i][j - coins[i]] + 1);
                } else if(dp[i - 1][j] != -1){
                    dp[i][j] = dp[i - 1][j];
                } else if(dp[i][j - coins[i]] != -1) {
                    dp[i][j] = dp[i][j - coins[i]] + 1;
                }
            }
        }
        return dp[size - 1][amount];
    }
};
```

```C++
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        if(amount == 0) return 0;
        int size = coins.size();
        vector<vector<int>> dp(size, vector<int>(amount + 1, amount + 1));
        for(int i = 0, sum = 0; sum <= amount; sum = ++i * coins[0]) dp[0][sum] = i;
        for(int i = 0; i < size; ++i) dp[i][0] = 0;
        for(int i = 1; i < size; ++i) {
            for(int j = 1; j <= amount; ++j) {
                if(j < coins[i]) {
                    dp[i][j] = dp[i - 1][j];
                } else {
                    dp[i][j] = min(dp[i - 1][j], dp[i][j - coins[i]] + 1);
                }
            }
        }
        return (dp[size - 1][amount] == amount + 1) ? -1 : dp[size - 1][amount];
    }
};
```



2、动态规划、滚动数组

```C++
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        for(int i = 1; i <= amount; i++){
            for(int j = 0; j < coins.size(); j++){
                if((i - coins[j]) >= 0){
                    dp[i] = min(dp[i], dp[i - coins[j]] + 1);
                }
            }
        }
        return (dp[amount] == amount + 1) ? -1 : dp[amount];
    }
};
```

```C++
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int size = coins.size();
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        for(int i = 0; i < size; ++i) {
            for(int j = coins[i]; j <= amount; ++j) {
                dp[j] = min(dp[j], dp[j - coins[i]] + 1);
            }
        }
        return (dp[amount] == amount + 1) ? -1 : dp[amount];
    }
};
```

3、贪心变形、回溯、剪枝

```C++
class Solution {
    int ans = INT_MAX;
    void coinChange(vector<int> &coins, int amount, int c_idx, int cnt) {
        if (amount == 0) {
            ans = min(ans, cnt);
            return;
        }
        if (c_idx == coins.size()) return;
        for (int k = amount / coins[c_idx]; k >= 0 && k + cnt < ans; k--) {
            coinChange(coins, amount - k * coins[c_idx], c_idx + 1, cnt + k);
        }
    }
public:
    int coinChange(vector<int> &coins, int amount) {
        if(amount == 0) return 0;
        sort(coins.rbegin(), coins.rend());
        coinChange(coins, amount, 0, 0);
        return ans == INT_MAX ? -1 : ans;
    }
};
```

#### [198. House Robber](https://leetcode-cn.com/problems/house-robber/)

1、动态规划

T: O(n); S: O(n)

```C++
class Solution {
public:
    int rob(vector<int>& nums) {
        int size = nums.size();
        if(0 == size) return 0;
        else if(1 == size) return nums[0];
        else if(2 == size) return max(nums[0], nums[1]);
        vector<int> dp(size, 0);
        dp[0] = nums[0]; dp[1] = max(nums[0], nums[1]);
        for(int i = 2; i < size; ++i) {
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }
        return dp[size - 1];
    }
};
```

2、动态规划、空间优化

T: O(n); S: O(1)

```C++
class Solution {
public:
    int rob(vector<int>& nums) {
        int size = nums.size();
        if(0 == size) return 0;
        else if(1 == size) return nums[0];
        else if(2 == size) return max(nums[0], nums[1]);
        int dp[3] = {nums[0], max(nums[0], nums[1])}; //!!!
        for(int i = 2; i < size; ++i) {
            dp[2] = max(dp[1], dp[0] + nums[i]);
            dp[0] = dp[1]; dp[1] = dp[2];
        }
        return dp[2];
    }
};
```



#### [213. House Robber II](https://leetcode-cn.com/problems/house-robber-ii/)

1、动态规划、问题转化

把问题拆分成两个打家劫舍的子问题问题

```C++
class Solution {
public:
    int rob(vector<int>& nums) {
        int size = nums.size();
        if(0 == size) return 0;
        else if(1 == size) return nums[0];
        else if(2 == size) return max(nums[0], nums[1]);
        else if(3 == size) return max(nums[0], max(nums[1], nums[2]));
        int dp[3] = {nums[0], max(nums[0], nums[1])};
        for(int i = 2; i < size - 1; ++i) {
            dp[2] = max(dp[0] + nums[i], dp[1]);
            dp[0] = dp[1]; dp[1] = dp[2];
        }
        int dp2[3] = {nums[1], max(nums[1], nums[2])};
        for(int i = 3; i < size; ++i) {
            dp2[2] = max(dp2[0] + nums[i], dp2[1]);
            dp2[0] = dp2[1]; dp2[1] = dp2[2];
        }
        return dp[2] > dp2[2] ? dp[2] : dp2[2];
    }
};
```



#### [121. Best Time to Buy and Sell Stock](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/)

1、动态规划

缩小问题规模，通过子问题的解来求得最终结果

假定每一个交易日为一个阶段，每一个阶段都有三种状态，分别为：不操作、买入、卖出

状态转移方程
$$
\begin{cases}
dp[i][0] = dp[i - 1][0]\\
dp[i][1] = min(dp[i - 1][1], prices[i])\\
dp[i][2] = max(dp[i - 1][2], prices[i] - dp[i - 1][1])\\
\end{cases}
$$


```C++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        if(0 == size) return 0;
        vector<vector<int>> dp(size, vector<int>(3, 0));
        dp[0][0] = 0; dp[0][1] = prices[0]; dp[0][2] = 0;
        for(int i = 1; i < size; ++i) {
            dp[i][1] = min(dp[i - 1][1], prices[i]);
            dp[i][2] = max(dp[i - 1][2], prices[i] - dp[i - 1][1]);
        }
        return dp[size - 1][2];
    }
};
```

2、动态规划、空间优化

```C++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        if(0 == size || 1 == size) return 0;
        int buy = min(prices[0], prices[1]), sell = prices[1];
        int res = (buy > sell) ? 0 : (sell - buy);
        for(int i = 2; i < size; ++i) {
            if(prices[i] < buy) sell = buy = prices[i];
            else if(prices[i] > sell) sell = prices[i];
            int margin = sell - buy;
            if(margin > res) res = margin;
        }
        return res;
    }
};
```

此题用单调栈显得有些大材小用，因为没有必要维护过多没用的信息

#### [122. Best Time to Buy and Sell Stock II](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/)

1、动态规划

```C++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        if(0 == size || 1 == size) return 0;
        int dp[2] = {prices[0], prices[0]};
        int res = 0;
        for(int i = 1; i < size; ++i) {
            if(prices[i] <= dp[1]) {
                res += dp[1] - dp[0];
                dp[0] = dp[1] = prices[i];
            } else {
                dp[1] = prices[i];
            }
        }
        return res + dp[1] - dp[0];
    }
};
```

#### [123. Best Time to Buy and Sell Stock III](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/)

1、贪心（一次错误的尝试）

错误的尝试源于错误的假设：问题可以由子问题的最优解得到，这正是贪心的典型特征。

贪心选择了子问题的最优路径之后，其它当前次优的路径便被完全抛弃。而这道题，问题的正解却可能来自于那些被抛弃的次优路径，所以贪心不能解决该问题，但从测试的结果看来，贪心虽然得到的结果不正确，但却已经很接近正确答案了。贪心速度会快一点。

```C++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        if(0 == size || 1 == size) return 0;
        prices.push_back(-1); //方便最后的处理
        int first_margin = 0, second_margin = 0, left_merge_margin = 0, right_merge_margin = 0, margin;
        vector<int> buy(3, prices[0]), sell(3, prices[0]);
        for(int i = 1; i <= size; ++i) {
            if(prices[i] < sell[2]) {
                margin = sell[2] - buy[2];
                left_merge_margin = max((sell[1] - buy[0]), max(first_margin, second_margin));
                right_merge_margin = max((sell[2] - buy[1]), max(second_margin, margin));
                // 下面的判断选择当前能最优路径，输入序列:[15,90,20,100,10,70,30,90]
                if(left_merge_margin + margin > right_merge_margin + first_margin) {
                    first_margin = left_merge_margin;
                    second_margin = margin;
                    buy[0] = min(buy[0], buy[1]);
                    buy[1] = buy[2];
                } else {
                    second_margin = right_merge_margin;
                    buy[1] = min(buy[1], buy[2]);
                }
                sell[1] = sell[2];
                while(i < size && prices[i + 1] < prices[i]) ++i; // 3,2,1
                sell[2] = buy[2] = prices[i];
            } else {
                sell[2] = prices[i];
            }
        }
        return first_margin + second_margin;
    }
};
```

2、问题拆分

寻找两次交易的分界点

```C++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n == 0) return 0;
        int minPri = prices.front(), maxPro1 = 0; // 顺序遍历的最小pirce和最大利润
        int maxPri = prices.back(), maxPro2 = 0;  // 逆序遍历的最大price和最大利润
        vector<int> profits1(n,0), profits2(n,0); // 顺序和逆序的利润分布
        for(int i = 0; i < n; i++){
            if(prices[i] <= minPri) minPri = prices[i];
            else maxPro1 = max(maxPro1, prices[i]-minPri);
            profits1[i] = maxPro1;
            if(prices[n-i-1] >= maxPri) maxPri = prices[n-i-1];
            else maxPro2 = max(maxPro2, maxPri-prices[n-i-1]);
            profits2[n-i-1] = maxPro2;
        }
        int maxPro = profits1[n-1];
        for(int i = 0; i < n-1; i++){
            maxPro = max(maxPro, profits1[i]+profits2[i+1]);
        }
        return maxPro;
    }
};
```

3、动态规划

假定每一个交易日为一个阶段，每一个阶段分为五种状态：不操作、第一次买入或卖出、第二次买入或卖出

状态转移方程:
$$
\begin{cases}
dp[i][0] = dp[i - 1][0]\\
dp[i][1] = min(dp[i - 1][1], prices[i])\\
dp[i][2] = max(dp[i - 1][2], prices[i] - dp[i - 1][1])\\
dp[i][3] = 
\begin{cases}
min(dp[i - 1][3], prices[i]), & dp[i][2] == dp[i - 1][2]\\
prices[i], & dp[i][2] <> dp[i - 1][2]
\end{cases}\\
dp[i][4] = max(dp[i - 1][2], prices[i] - dp[i - 1][3])
\end{cases}
$$

```C++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        if(0 == size) return 0;
        vector<vector<int>> dp(size, vector<int>(5, 0));
        dp[0][0] = 0; dp[0][1] = prices[0]; dp[0][2] = 0; dp[0][3] = prices[0];
        for(int i = 1; i < size; ++i) {
            dp[i][1] = min(dp[i - 1][1], prices[i]);
            dp[i][2] = max(dp[i - 1][2], prices[i] - dp[i - 1][1]);

            if(dp[i][2] != dp[i - 1][2]) dp[i][3] = prices[i];
            else dp[i][3] = min(dp[i - 1][3], prices[i]);
            dp[i][4] = max(dp[i - 1][4], dp[i - 1][2] + prices[i] - dp[i - 1][3]);
        }
        return dp[size - 1][4];
    }
};
/*
提交记录
207 / 214 个通过测试用例
状态：解答错误
输入：[6,1,3,2,4,7]
输出：6
预期：7
*/
```

$$
\begin{cases}
dp[i][0] = dp[i - 1][0]\\
dp[i][1] = min(dp[i - 1][1],\ prices[i])\\
dp[i][2] = max(dp[i - 1][2],\ prices[i] - dp[i - 1][1])\\
dp[i][3] = min(dp[i - 1][3],\ prices[i] - dp[i - 1][2])\\
dp[i][4] = max(dp[i - 1][2],\ prices[i] - dp[i - 1][3])
\end{cases}
$$



```C++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        if(0 == size) return 0;
        vector<vector<int>> dp(size, vector<int>(5, 0));
        dp[0][0] = 0; dp[0][1] = prices[0]; dp[0][2] = 0; dp[0][3] = prices[0];
        for(int i = 1; i < size; ++i) {
            dp[i][1] = min(dp[i - 1][1], prices[i]);
            dp[i][2] = max(dp[i - 1][2], prices[i] - dp[i - 1][1]);
            dp[i][3] = min(dp[i - 1][3], prices[i] - dp[i - 1][2]);
            dp[i][4] = max(dp[i - 1][4], prices[i] - dp[i - 1][3]);
        }
        return dp[size - 1][4];
    }
};
```



#### [309. Best Time to Buy and Sell Stock with Cooldown](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/)

1、动态规划

每一个交易日为一个阶段，每个阶段有5种状态：不操作、冻结时的总利润、买入、卖出
$$
\begin{cases}
dp[i][1] = max(dp[i - 1][1], dp[i - 1][3]) \\
dp[i][2] = min(dp[i - 1][2], prices[i] - dp[i - 1][1]) \\
dp[i][3] = max(dp[i - 1][3], prices[i] - dp[i - 1][2])
\end{cases}
$$


```C++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        if(0 == size || 1 == size) return 0;
        vector<vector<int>> dp(size, vector<int>(4, 0));
        dp[0][2] = prices[0];
        for(int i = 1; i < size; ++i) {
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][3]);
            dp[i][2] = min(dp[i - 1][2], prices[i] - dp[i - 1][1]);
            dp[i][3] = max(dp[i - 1][3], prices[i] - dp[i - 1][2]);
        }
        return dp[size - 1][3];
    }
};
```



#### [188. Best Time to Buy and Sell Stock IV](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iv/)

1、动态规划

用三维数组来表示，思路会更加清晰

状态转移方程：
$$
i表示第i个交易日，k表示最多买卖次数，0，1分别表示买入和卖出\\
dp[i][k][0]表示买卖当前次数的最低成本\\
dp[i][k][1]表示买卖当前次数的最大利润\\
\begin{cases}
dp[i][k][0] = min(dp[i - 1][k][0],\ prices[i] - dp[i - 1][k - 1][1])\\
dp[i][k][1] = max(dp[i - 1][k][1],\ prices[i] - dp[i - 1][k][0])
\end{cases}
$$



```C++
// i表示第i个交易日，k表示最多买卖次数，0，1分别表示买入和卖出
// dp[i][k][0]表示买卖当前次数的最低成本
// dp[i][k][1]表示买卖当前次数的最大利润
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int size = prices.size();
        if(0 == size || 1 == size) return 0;
        if(k >= size / 2) return greedy(prices);
        prices.push_back(-1);
        vector<vector<vector<int>>> dp(size + 1, vector<vector<int>>(k + 1, vector<int>(2, 0)));
        for(int i = 0; i <= k; ++i) dp[0][i][0] = prices[0];
        for(int i = 1; i <= size; ++i) {
            for(int j = 1; j <= k; ++j) {
                dp[i][j][0] = min(dp[i - 1][j][0], prices[i] - dp[i - 1][j - 1][1]);
                dp[i][j][1] = max(dp[i - 1][j][1], prices[i] - dp[i - 1][j][0]);
            }
        }
        return dp[size][k][1];
    }
    int greedy(vector<int>& prices) {
        int size = prices.size(), res = 0;
        for(int i = 1; i < size; ++i) {
            if(prices[i] > prices[i - 1]) res += prices[i] - prices[i - 1];
        }
        return res;
    }
};
```

2、动态规划

二维数组，由三维转化而来，并没有节省空间的使用

```C++
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int size = prices.size();
        if(0 == size || 1 == size) return 0;
        if(k >= size / 2) return greedy(prices);
        vector<vector<int>> dp(size, vector<int>(k * 2 + 1, 0));
        for(int i = 1; i <= k; ++i) dp[0][i * 2 - 1] = prices[0];
        for(int i = 1; i < size; ++i) {
            for(int j = 1; j <= k; ++j) {
                int in = j * 2 - 1, out = j * 2;
                dp[i][in] = min(dp[i - 1][in], prices[i] - dp[i - 1][in - 1]);
                dp[i][out] = max(dp[i - 1][out], prices[i] - dp[i - 1][in]);
            }
        }
        return dp[size - 1][k * 2];
    }
    int greedy(vector<int>& prices) {
        int size = prices.size(), res = 0;
        for(int i = 1; i < size; ++i) {
            if(prices[i] > prices[i - 1]) res += prices[i] - prices[i - 1];
        }
        return res;
    }
};
```

3、动态规划、滚动数组优化空间

用二维数组来表示，可以转化成一维数组
$$
i表示第i个交易日，k表示最多买卖次数，0，1分别表示买入和卖出\\
\begin{cases}
dp[j][0] = min(dp[j][0], prices[i] - dp[j - 1][1])\\
dp[j][1] = max(dp[j][1], prices[i] - dp[j][0])
\end{cases}
$$


```C++
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int size = prices.size();
        if(0 == size || 1 == size) return 0;
        if(k >= size / 2) return greedy(prices);
        prices.push_back(-1);
        vector<vector<int>> dp(k + 1, vector<int>(2, 0));
        for(int i = 0; i <= k; ++i) dp[i][0] = prices[0];
        for(int i = 1; i <= size; ++i) {
            for(int j = 1; j <= k; ++j) {
                dp[j][0] = min(dp[j][0], prices[i] - dp[j - 1][1]);
                dp[j][1] = max(dp[j][1], prices[i] - dp[j][0]);
            }
        }
        return dp[k][1];
    }
    int greedy(vector<int>& prices) {
        int size = prices.size(), res = 0;
        for(int i = 1; i < size; ++i) {
            if(prices[i] > prices[i - 1]) res += prices[i] - prices[i - 1];
        }
        return res;
    }
};
```



#### [714. Best Time to Buy and Sell Stock with Transaction Fee](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/)

1、贪心的错误应用

错误解法

```C++
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int size = prices.size();
        if(0 == size || 1 == size) return 0;
        int premargin = 0, merge_margin = 0, margin = 0, res = 0;
        prices.push_back(-1);
        vector<int> buy(2, prices[0]), sell(2, prices[0]);
        for(int i = 1; i <= size; ++i) {
            if(prices[i] < sell[1]) {
                margin = sell[1] - buy[1] - fee;
                merge_margin = sell[1] - buy[0] - fee;
                premargin = max(premargin + margin, merge_margin);
                if(premargin < 0) premargin = 0;
                while(i < size && prices[i] > prices[i + 1]) ++i;
                buy[1] = prices[i];
                if(prices[i] <= buy[0]) {
                    buy[0] = prices[i];
                    res += premargin;
                    premargin = 0;
                }
            }  
            while(i < size && prices[i] <= prices[i + 1]) ++i;
            sell[1] = prices[i];
        }
        return res;
    }
};
```

2、动态规划

```C++
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int size = prices.size();
        if(0 == size || 1 == size) return 0;
        vector<vector<int>> dp(size, vector<int>(2, 0));
        dp[0][0] = prices[0] + fee;
        for(int i = 1; i < size; ++i) {
            dp[i][0] = min(dp[i - 1][0], prices[i] - dp[i - 1][1] + fee);
            dp[i][1] = max(dp[i - 1][1], prices[i] - dp[i - 1][0]);
        }
        return dp[size - 1][1];
    }
};
```

