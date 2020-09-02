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
                if(text1[i - 1] == text2[j - 1])dp[i][j] = dp[i - 1][j - 1] + 1;
                else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[m][n];
    }
};
```

#### [70. Climbing Stairs](https://leetcode-cn.com/problems/climbing-stairs/)

1、

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

#### [152. Maximum Product Subarray](https://leetcode-cn.com/problems/maximum-product-subarray/)