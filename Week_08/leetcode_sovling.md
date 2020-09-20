# 第八周

### 位运算

#### [191. Number of 1 Bits](https://leetcode-cn.com/problems/number-of-1-bits/)

1、位运算

```C++
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int cnt = 0;
        while(n != 0) {
            if(n & 1 != 0) ++cnt;
            n >>= 1;
        }
        return cnt;
    }
};
```

2、位运算

公式 n &= (n - 1) 每次把最后一个一消掉

```C++
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int cnt = 0;
        while(n != 0) {
            ++cnt;
            n &= (n - 1);
        }
        return cnt;
    }
};
```

#### [231. Power of Two](https://leetcode-cn.com/problems/power-of-two/)

位运算

1、

```C++
class Solution {
public:
    bool isPowerOfTwo(int n) {
        if(0 == n || INT_MIN == n) return false;
        if(n & (n - 1)) return false;
        else return true;
    }
};
```

2、

-x = ~x - 1

if x is pow of 2: 

​	x & (-x) == x

```C++
class Solution {
public:
    bool isPowerOfTwo(int n) {
        if(0 == n) return false;
        long x = n;
        // return x & (-x) == x;
        return x & (~x + 1) == x; // C++用这样的方法会出问题，不知道为什么
    }
};
```



#### [190. Reverse Bits](https://leetcode-cn.com/problems/reverse-bits/)

1、位运算

```C++
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        int cnt = 32;
        uint32_t res = 0;
        while(cnt--) {
            res <<= 1;
            if(n & 1) ++res;
            n >>= 1;
        }
        return res;
    }
};
```

#### [52. N-Queens II](https://leetcode-cn.com/problems/n-queens-ii/)

1、位图

```C++
class Solution {
    int res = 0;
    int col = 0, r_diagonal = 0, l_diagonal = 0;
public:
    int totalNQueens(int n) {
        backtracing(n, 0);
        return res;
    }
    void backtracing(int n, int level) {
        if(n == level) {
            ++res;
            return;
        }
        int x = level, y;
        for(y = 0; y < n; ++y) {
            int c = 1 << y, r = 1 << (x - y + n), l = 1 << (x + y);
            if((c & col) || (r & r_diagonal) || (l & l_diagonal)) continue; //r = 1 << (abs(x - y)); xxx
            col ^= c; r_diagonal ^= r; l_diagonal ^= l;
            backtracing(n, level + 1);
            col ^= c; r_diagonal ^= r; l_diagonal ^= l;
        }
    }
};
```

#### [338. Counting Bits](https://leetcode-cn.com/problems/counting-bits/)

1、位运算

```C++
class Solution {
    vector<int> res;
public:
    vector<int> countBits(int num) {
        for(int i = 0; i <= num; ++i) { 
            int n = i, cnt = 0;
            while(n != 0) {
                ++cnt;
                n &= (n - 1);
            }
            res.push_back(cnt);
        }
        return res;
    }
};
```

2、利用之前的结果提高问题求解的速度、这算动态规划吗，不算！

```C++
class Solution {
    vector<int> res;
public:
    vector<int> countBits(int num) {
        res.resize(num + 1);
        res[0] = 0;
        for(int i = 1; i <= num; ++i) { 
            res[i] = res[i - 1] + 1;
            int pre = i - 1;
            if(pre & 1){
                int tmp = 1;
                while(pre & tmp) {
                    --res[i];
                    tmp <<= 1;
                }
            }
        }
        return res;
    }
};
```

3、动态规划

```C++

```



### LRUCache

#### [146. LRU Cache](https://leetcode-cn.com/problems/lru-cache/)

```C++
/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
```

1、hash、deque

```C++
class LRUCache {
private:
    struct node{
        struct node *pre, *post;
        int key, value;
        node(int _key = 0, int _value = 0) : key(_key), value(_value), pre(NULL), post(NULL) {}
    };

    int _capacity, _remain;
    unordered_map<int, node*> mp;
    node *_head, *_tail;

    void _move_to_tail(node* it) {
        if(it->post != NULL) it->post->pre = it->pre;
        if(it->pre != NULL) it->pre->post = it->post;
        _tail = it;
    }

    void _add_to_tail(node* it) {
        it->pre = _tail; it->post = NULL;
        _tail = it;
        mp[it->key] = it;
    }

public:
    LRUCache(int capacity) {
        _remain = _capacity = capacity;
        _head = _tail = NULL;
    }
    
    int get(int key) {
        auto it = mp.find(key);
        if(it == mp.end()) return -1;
        _move_to_tail(it->second);
        return it->second->value;
    }
    
    void put(int key, int value) {
        auto it = mp.find(key);
        if(it != mp.end()) {
            it->second->value = value;
            _move_to_tail(it->second);
        }
        else {
            node* it = _head;
            if(0 == _remain) {
                _head = it->post;
                mp.erase(it->key);
                it->key = key; it->value = value;
                _add_to_tail(it);
            } else {
                _remain--;
                it = new node(key, value);
                _add_to_tail(it);
            }
            if(_capacity - _remain == 1) _head = it;
        }
        return;
    }
};
```

