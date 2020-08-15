## 第三周

#### [509. Fibonacci Number](https://leetcode-cn.com/problems/fibonacci-number/)

0 ≤ `N` ≤ 30.

1、暴力递归

Fibonacci本来是不适合用递归来解决的，因为包含太多的重复计算；只不过跟递归的特点类似，递归的形式也很简单，所以被很多教材用于介绍递归的应用。

C++

```C++
class Solution {
public:
    int fib(int N) {
        if(N <= 1) return N;
        return fib(N - 1) + fib(N - 2);
    }
};
```

2、递归、数组记录状态

C++

```c++
class Solution {
public:
    vector<int> tmp;
    int fib(int N) {
        tmp.resize(N + 1);
        return gen(N);
    }
    int gen(int N) {
        if(N <= 1) return N;
        return tmp[N] ? tmp[N] : (tmp[N] = gen(N - 1) + gen(N - 2));
    }
};
```

```c++
class Solution {
public:
    int tmp[31]; //备忘录
    int fib(int N) {
        if(N <= 1) return N;
        return tmp[N] ? tmp[N] : (tmp[N] = fib(N - 1) + fib(N - 2));
    }
};
```

3、迭代

C++

```c++
class Solution {
public:
    int fib(int N) {
        if(N <= 1) return N;
        int prepre = 0, pre = 1, res;
        for(int i = 2; i <= N; ++i) {
            res = pre + prepre;
            prepre = pre;
            pre = res;
        }
        return res;
    }
};
```

4、动态规划

推导式：F(N) = F(N - 1) + F(N - 2); 



#### [22. Generate Parentheses](https://leetcode-cn.com/problems/generate-parentheses/)

1、递归

C++

```c++
/*
**最开始的思路为，以第一组括号包含不同对数的括号，把问题分成两个子问题，其一为第一对括号包含的有效括号序列，
**另一个子问题为未被包含的括号序列。这个重复子问题，转化成代码的时候遇到了困难。
**于是，最后放弃了这个思路。重复子问题也有优劣之分，我们要找出多种不同的分法，选择相对最优的那一种。
*/
class Solution {
public:
    vector<string> res;
    vector<string> generateParenthesis(int n) {
        generate(n, 0, 0, "");
        return res;
    }
	void generate(int n, int left, int right, string str) {
        if(left == n && right == n) res.push_back(str);
        else {
            if(left < n) generate(n, left + 1, right, str + '(');
        	if(right < left) generate(n, left, right + 1, str + ')');
        }
    }
};
```

2、递推，归纳，找规律

python

```python
class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        if n == 0:
            return []
        
        pre = ['',]
        for _ in range(n):
            now = set() # use set to remove duplicate items
            for st in pre:
                n = len(st)
                for index in range(n + 1):
                    now.add(st[:index]+'()'+st[index:])
            pre = now
        return list(pre)
```

#### [104. Maximum Depth of Binary Tree](https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/)

```C++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
```

1、递归

C++

```C++
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(root == nullptr) return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};
```

#### [111. Minimum Depth of Binary Tree](https://leetcode-cn.com/problems/minimum-depth-of-binary-tree/)

1、递归

C++

```C++
class Solution {
    int min = INT_MAX;
public:
    int minDepth(TreeNode* root) {
        if(!root) return 0; //corner case!!!
        find(root, 1);
        return min;
    }
    void find(TreeNode* root, int depth) {
        if(root == nullptr) return;
        if(!root->left && !root->right && depth < min) min = depth;
        else {
            find(root->left, depth + 1);
            find(root->right, depth + 1);
        }
    }
};
```

```C++
class Solution {
public:
    int minDepth(TreeNode* root) {
        if(root == nullptr) return 0;
        int left = minDepth(root->left), right = minDepth(root->right);
        if(left && right) return (left < right ? left : right) + 1;
        return left ? left + 1 : right + 1;
    }
};
```

2、迭代、层次遍历

#### [297. Serialize and Deserialize Binary Tree](https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree/)

1、



#### [50. Pow(x, n)](https://leetcode-cn.com/problems/powx-n/)

1、递归，快速幂

T: O(log(n)); S: O(log(n))

C++

```c++
/*
遇到这种问题应该要考虑是否有超出数据类型表示范围的情况
测试用例：
1.00000
-2147483648
超出int范围
double myPow(double x, int n)
*/
class Solution {
public:
    double myPow(double x, long long n) {
        return (n >= 0) ? pow(x, n) : 1.0 / pow(x, -n);
    }
    double pow(double x, long long n) {
        if(0 == n) return 1.0;
        double tmp = myPow(x, n / 2);
        return (n % 2) ? tmp * tmp * x : tmp * tmp;   
    }
};
```

执行用时：**0 ms** 内存消耗：**5.8 MB**

2、迭代、快速幂

T: O(log(n)); S: O(1)

C++

```c++
class Solution {
public:
    double myPow(double x, long n) {
        double res = 1.0;
        long m = ((n >= 0) ? n : -n);
        while(m > 0) {
            (m % 2) && (res *= x);
            x *= x;
            m >>= 1;
        }
        return (n >= 0) ? res : (1.0 / res);
    }
};
```
执行用时：**4 ms **内存消耗：**6.1 MB** 

为什么第二个程序反而执行的慢了，而且占用空间更大了？希望助教老师老师能够解答

#### [78. Subsets](https://leetcode-cn.com/problems/subsets/)

1、递归、回溯

T: O(n^2); S: O(n)

C++

```C++
class Solution {
public:
    vector<vector<int>> res;
    vector<int> tmp;
    vector<vector<int>> subsets(vector<int>& nums) {
        res.push_back(tmp);
        gen(nums, 0, nums.size());
        return res;
    }
    void gen(vector<int>& nums, int level, int ceiling) {
        if(level == ceiling) return;
        for(int i = level; i < ceiling; ++i) {
            tmp.push_back(nums[i]);
            res.push_back(tmp);
            gen(nums, i + 1, ceiling);
            tmp.pop_back();
        }
    }
};
```

2、迭代

T: O(n^2); S: O(n)

C++

```C++
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> subsets(vector<int>& nums) {
        int ceiling = nums.size(), size = 1, level = -1;
        res.push_back({});
        while(++level < ceiling) {
            for(int i = 0; i < size; ++i) {
                vector<int> tmp = res[i];
                tmp.push_back(nums[level]);
                res.push_back(tmp);
            }
            size = res.size();
        }
        return res;
    }
};
```

#### [169. Majority Element](https://leetcode-cn.com/problems/majority-element/)

1、哈希统计次数

C++

```C++
class Solution {
public:
    unordered_map<int, int> mp;
    int majorityElement(vector<int>& nums) {
        int size = nums.size();
        int bound = size / 2;
        for(int i = 0; i < size; ++i) {
            if(mp.find(nums[i]) == mp.end()) mp.insert({nums[i], 1});
            else ++mp[nums[i]];
        }
        for(int i = 0; i < size; ++i) {
            if(mp[nums[i]] > bound) return nums[i];
        }
        return 0;
    }
};
```

2、排序

3、随机化

4、递归、分治

5、抵消

C++

```C++
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int count = 1, res = nums[0], size = nums.size();
        for(int i = 1; i < size; ++i) {
            if(nums[i] == res) ++count;
            else if(1 == count) res = nums[++i];
            else --count;
        }
        return res;
    }
};
```

#### [17. Letter Combinations of a Phone Number](https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number/)

1、递归、回溯

C++

```C++
class Solution {
public:
    unordered_map<char, string> mp = {
        {'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"}, 
        {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}
    };
    vector<string> res;
    vector<string> letterCombinations(string digits) {
        int size = digits.size();
        if(0 == size) return res; //corner case!!!
        gen(digits, "", 0, size);
        return res;
    }
    void gen(string& digits, string tmp, int level, int size) {
        if(level == size) res.push_back(tmp);
        else {
            int sz = mp[digits[level]].size();
            for(int i = 0; i < sz; ++i) { //backtrace
                gen(digits, tmp + mp[digits[level]][i], level + 1, size);
            }
        }
    }
};
```



#### [51. N-Queens](https://leetcode-cn.com/problems/n-queens/)

1、递归、回溯

C++

```C++
class Solution {
private:
    vector<vector<string>> res;
    set<int> cols, xy_dif, xy_sum;
    vector<string> vectmp;
public:
    vector<vector<string>> solveNQueens(int n) {
        gen(n, 0);
        return res;
    }
    void gen(int n, int row) {
        if(row == n) res.push_back(vectmp);
        else {
            string strtmp;
            strtmp.resize(n, '.');
            for(int col = 0; col < n; ++col) {
                if(cols.find(col) == cols.end() && xy_dif.find(row - col) == xy_dif.end() && xy_sum.find(row + col) == xy_sum.end()) {
                    cols.insert(col); //set state
                    xy_dif.insert(row - col);
                    xy_sum.insert(row + col);
                    strtmp[col] = 'Q';
                    vectmp.push_back(strtmp);
                    gen(n, row + 1); //drill down
                    vectmp.pop_back(); //revert state
                    strtmp[col] = '.';
                    cols.erase(cols.find(col));
                    xy_dif.erase(xy_dif.find(row - col));
                    xy_sum.erase(xy_sum.find(row + col));
                }
            }
        }
    }
};
```

执行用时：**52 ms** 内存消耗：**10.6 MB**

```c++
class Solution {
private:
    static const int M = 20;
    int cols[M], dg[M], rdg[M]; //dg: diaginal; flag_arrays
    vector<string> a;
    vector<vector<string>> res;
public:
    vector<vector<string>> solveNQueens(int n) {
        a.resize(n, string(n, '.')); //initialize
        dfs(0, n);
        return res;
    }
    void dfs(int row, int n) { //backtrace
        if (row == n) res.push_back(a);
        else {
            for (int col = 0; col < n; ++col) {
                if (!cols[col] && !dg[row - col + n] && !rdg[row + col]) { //prune
                    a[row][col] = 'Q'; //set state
                    cols[col] = dg[row - col + n] = rdg[row + col] = 1;
                    dfs(row + 1, n); //drill down
                    a[row][col] = '.'; //revert state
                    cols[col] = dg[row - col + n] = rdg[row + col] = 0;
                }
            }
        }
    }
};
```

执行用时：**8 ms** 内存消耗：**7.7 MB**

```C++
class Solution {
public:
    std::vector<std::vector<std::string> > solveNQueens(int n) {
        std::vector<std::vector<std::string> > res;
        std::vector<std::string> nQueens(n, std::string(n, '.'));
        /*
        flag[0] to flag[n - 1] to indicate if the column had a queen before.
        flag[n] to flag[3 * n - 2] to indicate if the 45° diagonal had a queen before.
        flag[3 * n - 1] to flag[5 * n - 3] to indicate if the 135° diagonal had a queen before.
        */
        std::vector<int> flag(5 * n - 2, 1);
        solveNQueens(res, nQueens, flag, 0, n);
        return res;
    }
private:
    void solveNQueens(std::vector<std::vector<std::string> > &res, std::vector<std::string> &nQueens, std::vector<int> &flag, int row, int &n) {
        if (row == n) {
            res.push_back(nQueens);
            return;
        }
        for (int col = 0; col != n; ++col)
            if (flag[col] && flag[n + row + col] && flag[4 * n - 2 + col - row]) {
                flag[col] = flag[n + row + col] = flag[4 * n - 2 + col - row] = 0;
                nQueens[row][col] = 'Q';
                solveNQueens(res, nQueens, flag, row + 1, n);
                nQueens[row][col] = '.';
                flag[col] = flag[n + row + col] = flag[4 * n - 2 + col - row] = 1;
            }
    }
};
```

python

```python
def solveNQueens(self, n):
    def DFS(queens, xy_dif, xy_sum):
        p = len(queens)
        if p==n:
            result.append(queens)
            return None
        for q in range(n):
            if q not in queens and p-q not in xy_dif and p+q not in xy_sum: 
                DFS(queens+[q], xy_dif+[p-q], xy_sum+[p+q])  
    result = []
    DFS([],[],[])
    return [ ["."*i + "Q" + "."*(n-i-1) for i in sol] for sol in result]
```



#### [236. Lowest Common Ancestor of a Binary Tree](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/)

1、递归、回溯

**每次递归都可能会遇到四种情况**
1. p、q其中一个等于当前子树根节点
2. p、q都在左子树中
3. p、p都在右子树中
4. p、q分别在左右子树中

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == nullptr) return nullptr;
        if(root == p || root == q) return root;//1
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        if(left != nullptr && right != nullptr) return root;//4
        return ((left != nullptr) ? left : right);//2、3
    }
};
```

2、存储父节点

#### [105. Construct Binary Tree from Preorder and Inorder Traversal](https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)

1、递归、遍历中序序列寻找根节点的索引

C++

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return build(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
    }
    TreeNode* build(vector<int>& preorder, vector<int>&inorder, int prel, int prer, int inl, int inr) {
        if(inl > inr) return nullptr;
        TreeNode* root = new TreeNode(preorder[prel]);
        if(inl == inr) return root;
        int tmp = inl;
        while(preorder[prel] != inorder[tmp]) tmp++;
        root->left = build(preorder, inorder, prel + 1, prel + tmp - inl, inl, tmp - 1);
        root->right = build(preorder, inorder, prel + tmp -inl + 1, prer, tmp + 1, inr);
        return root;
    }
};
```

2、递归、通过哈希加快查找中序索引的速度

C++

```c++
class Solution {
public:
    unordered_map<int, int> mp;
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        for(int last = inorder.size() - 1; last >= 0; --last) mp.insert({inorder[last], last});
        //通过insert以及pair插入元素: mp.insert(pair<int, int>(inorder[last], last));
        return build(preorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
    }
    TreeNode* build(vector<int>& preorder, int prel, int prer, int inl, int inr) {
        if(inl > inr) return nullptr;
        TreeNode* root = new TreeNode(preorder[prel]);
        if(inl == inr) return root;
        int tmp = mp[preorder[prel]];
        root->left = build(preorder, prel + 1, prel + tmp - inl, inl, tmp - 1);
        root->right = build(preorder, prel + tmp -inl + 1, prer, tmp + 1, inr);
        return root;
    }
};
```

```c++
class Solution {
public:
    unordered_map<int, int> mp;
    int pre = 0;
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        for(int last = inorder.size() - 1; last >= 0; --last) mp.insert({inorder[last], last});
        return build(preorder, 0, preorder.size() - 1);
    }
    TreeNode* build(vector<int>& preorder, int inl, int inr) {
        if(inl > inr) return nullptr;
        TreeNode* root = new TreeNode(preorder[pre]);
        int tmp = mp[preorder[pre++]];
        root->left = build(preorder, inl, tmp - 1);
        root->right = build(preorder, tmp + 1, inr);
        return root;
    }
};
```

3、迭代、栈

C++

先序遍历序列中相邻的两个节点，假设先后节点分别为u、v，则u和v的关系只可能是两种：

1. v是u的左节点
2. v是u（或u的某一个祖先节点）的右节点

借助栈，可以迭代计算每一个节点的左右子节点

```c++

```



#### [77. Combinations](https://leetcode-cn.com/problems/combinations/)

1、回溯Backtrack

C++

```c++
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> combine(int n, int k) {
        vector<int> tmp;
        gen(n, k, 1, tmp);
        return res;
    }
    void gen(int n, int k, int first, vector<int> tmp) {
        if(tmp.size() == k) res.push_back(tmp);
        else {
            for(int i = first; i <= n; ++i) {
                tmp.push_back(i);
                gen(n, k, i + 1, tmp);//drill down
                tmp.pop_back();//recall
            }
        }
    }
};
```

2、回溯优化：剪枝

C++

```C++
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> combine(int n, int k) {
        vector<int> tmp;
        gen(n, k, 1, tmp);
        return res;
    }
    void gen(int n, int k, int first, vector<int> tmp) {
        if(tmp.size() == k) res.push_back(tmp);
        else {
            int cut = n - (k - tmp.size()) + 1;//剪枝
            for(int i = first; i <= cut; ++i) {
                tmp.push_back(i);
                gen(n, k, i + 1, tmp);
                tmp.pop_back();
            }
        }
    }
};
```

#### [46. Permutations](https://leetcode-cn.com/problems/permutations/)

1、回溯，标记数组

T:O(); S:O(nums.size())

C++

```c++
class Solution {
public:
    vector<vector<int>> res;
    vector<int> tmp;
    vector<vector<int>> permute(vector<int>& nums) {
        int size = nums.size();
        //bool *tag = new bool(size);//这样有问题，堆栈溢出，为什么？
        vector<bool> tag;
        tag.resize(size);
        gen(nums, size, tag);
        return res;
    }
    void gen(vector<int>& nums, int size, vector<bool>& tag) {
        if(tmp.size() == size) res.push_back(tmp);
        else {
            for(int i = 0; i < size; ++i) {
                if(!tag[i]) {
                    tag[i] = true; tmp.push_back(nums[i]);
                    gen(nums, size, tag);
                    tag[i] = false; tmp.pop_back();
                }
            }
        }
    }
};
```

2、回溯，交换

C++

```c++
class Solution {
public:
    vector<vector<int>> res;
    vector<int> tmp;
    vector<vector<int>> permute(vector<int>& nums) {
        int size = nums.size();
        gen(nums, size, 0);
        return res;
    }
    void gen(vector<int>& nums, int size, int first) {
        if(tmp.size() == size) res.push_back(tmp);
        else {
            for(int i = first; i < size; ++i) {
                swap(nums[i], nums[first]);
                tmp.push_back(nums[first]);
                gen(nums, size, first + 1);
                tmp.pop_back();
                swap(nums[i], nums[first]);
            }
        }
    }
};
```

#### [47. Permutations II](https://leetcode-cn.com/problems/permutations-ii/)

1、回溯

C++

```c++
class Solution {
public:
    vector<vector<int>> res;
    vector<int> tmp;
	vector<vector<int>> permuteUnique(vector<int>& nums) {
        int size = nums.size();
        gen(nums, size, 0);
        return res;
    }
    void gen(vector<int>& nums, int size, int first) {
        if(tmp.size() == size) res.push_back(tmp);
        else {
            set<int> st;
            for(int i = first; i < size; ++i) {
                if(st.find(nums[i]) != st.end()) continue; //Prohibit duplications
                else st.insert(nums[i]);
                swap(nums[i], nums[first]); tmp.push_back(nums[first]);
                gen(nums, size, first + 1); //dril down
                swap(nums[i], nums[first]); tmp.pop_back(); //restore state
            }
        }
    }
};
```

