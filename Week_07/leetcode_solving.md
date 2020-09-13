#### [208. Implement Trie (Prefix Tree)](https://leetcode-cn.com/problems/implement-trie-prefix-tree/)

```C++
/**
 * Your Trie struct will be instantiated and called as such:
 * Trie* obj = trieCreate();
 * trieInsert(obj, word);
 
 * bool param_2 = trieSearch(obj, word);
 
 * bool param_3 = trieStartsWith(obj, prefix);
 
 * trieFree(obj);
*/
```

1、C语言实现

```C
typedef struct trie{
    bool end;
    struct trie* next[26];
} Trie;

/** Initialize your data structure here. */

Trie* trieCreate() {
    Trie *root = (Trie *)malloc(sizeof(Trie));
    memset(root, 0, sizeof(*root));
    return root; 
    // return (Trie*)calloc(0, sizeof(Trie)); // 为什么这样会报错
}

/** Inserts a word into the trie. */
void trieInsert(Trie* obj, char * word) {
    Trie *tri = obj;
    for(int i = 0; word[i] != '\0'; ++i) {
        int idx = word[i] - 'a';
        if(tri->next[idx] == NULL) { // 这里会报错
            tri = tri->next[idx] = trieCreate();
        } else {
            tri = tri->next[idx];
        }
    }
    tri->end = true;
}

/** Returns if the word is in the trie. */
bool trieSearch(Trie* obj, char * word) {
    int len = strlen(word);
    if(0 == len) return true;
    Trie* trie = obj;
    for(int i = 0; i < len; ++i) {
        int idx = word[i] - 'a';
        if((trie = trie->next[idx]) == NULL) {
            return false;
        }
    }
    return trie->end;
}

/** Returns if there is any word in the trie that starts with the given prefix. */
bool trieStartsWith(Trie* obj, char * prefix) {
    int len = strlen(prefix);
    if(0 == len) return true;
    Trie* trie = obj;
    for(int i = 0; i < len; ++i) {
        int idx = prefix[i] - 'a';
        if((trie = trie->next[idx]) == NULL) {
            return false;
        }
    }
    return true;
}

void trieFree(Trie* obj) {
    if(obj == NULL) return;
    for(int i = 0; i < 26; ++i) {
        trieFree(obj->next[i]);
    }
    free(obj);
}
```

2、C++语言实现

```C++
class Trie {
public:
    Trie() {
        root = new TrieNode();
    }
    void insert(string word) {
        TrieNode *curr = root;
        for (int i = 0; i < word.size(); i++) {
            if (curr->child_table.count(word[i]) == 0) curr->child_table[word[i]] = new TrieNode();
            curr = curr->child_table[word[i]];                
        }
        curr->end = 1;
    }
    bool search(string word) {
        return find(word, 1);
    }
    bool startsWith(string prefix) {
        return find(prefix, 0);
    }
private:
    struct TrieNode {
        map<char, TrieNode*>child_table;
        int end;
        TrieNode(): end(0) {}
    };
    TrieNode* root;
    bool find(string s, int exact_match) {
        TrieNode *curr = root;
        for (int i = 0; i < s.size(); i++) {
            if (curr->child_table.count(s[i]) == 0) return false;
            else curr = curr->child_table[s[i]];
        }
        if (exact_match) return (curr->end) ? true : false;
        else return true;
    }
};
```



#### [212. Word Search II](https://leetcode-cn.com/problems/word-search-ii/)

1、DFS、递归回溯

超出时间限制

```C++
class Solution {
    vector<string> res;
    int dir[4][2] = {1, 0, 0, 1, -1, 0, 0, -1}; //0: up, 1: right, 2: down, 3: left 
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        int row = board.size(), col, size = words.size();
        if(0 == row || 0 == size) return {};
        else col = board[0].size();
        if(0 == col) return {};
        vector<vector<bool>> visit(row, vector<bool>(col, false));
        for(int i = 0; i < size; ++i) {
            if(find_first(board, words[i], visit)) res.push_back(words[i]);
        }
        return res;
    }
    bool find_first(vector<vector<char>>& board, string& word, vector<vector<bool>>& visit) {
        int row = board.size(), col = board[0].size();
        for(int i = 0; i < row; ++i) {
            for(int j = 0; j < col; ++j) {
                if(find_all(board, word, visit, i, j, 0, -1)) return true;
            }
        }
        return false;
    }
    bool find_all(vector<vector<char>>& board, string& word, vector<vector<bool>>& visit, int row, int col, int idx, int from) {
        if(word.size() == idx) return true;
        if(row >= board.size() || row < 0 || col < 0 || col >= board[0].size()) return false;
        if(visit[row][col] || word[idx] != board[row][col]) return false;
        visit[row][col] = true;
        for(int i = 0; i < 4; ++i) {
            // if(-1 != from && (from + 2) % 4 == i) continue;
            if(find_all(board, word, visit, row + dir[i][0], col + dir[i][1], idx + 1, i)) {
                visit[row][col] = false;
                return true;
            }
        }
        visit[row][col] = false;
        return false;
    }
};
```

2、trie tree、DFS、set去重

```C++
class Solution {
private:
    // structs and functions below are trie-tree related
    struct trieNode{
        bool end;
        unordered_map<char, trieNode*> mp;
        trieNode(): end(false) {}
    };
    trieNode* root;
    void createTrie(vector<string>& words) {
        root = new trieNode();
        for(auto word : words) {
            insertWord(word);
        }
    }
    void insertWord(string& word) {
        trieNode* cur = root;
        for(int i = 0, size = word.size(); i < size; ++i) {
            char c = word[i];
            if(cur->mp.find(c) == cur->mp.end()) cur->mp[c] = new trieNode();
            cur = cur->mp[c];
        }
        cur->end = true;
    }
    // other elements below
    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; //0: up, 1: right, 2: down, 3: left 
    set<string> st;
    vector<string> res;
    void find(vector<vector<char>>& b, vector<vector<bool>>& v, int row, int col, trieNode* cur, string str) {
        if(cur->end) st.insert(str);
        if(row < 0 || col < 0 || row >= b.size() || col >= b[0].size() || v[row][col]) return;
        char c = b[row][col];
        if(0 == cur->mp.size() || cur->mp.find(c) == cur->mp.end()) return;
        v[row][col] = true; // drill down
        for(int i = 0; i < 4; ++i) {
            find(b, v, row + dir[i][0], col + dir[i][1], cur->mp[c], str + c);
        }
        v[row][col] = false; // restate
    }
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        int row = board.size(), num = words.size();
        if(0 == row || 0 == num) return {};
        int col = board[0].size();
        if(0 == col) return {};
        vector<vector<bool>> visit(row, vector<bool>(col, false));
        createTrie(words);
        for(int i = 0; i < row; ++i) {
            for(int j = 0; j < col; ++j) {
                find(board, visit, i, j, root, "");
            }
        }
        for(set<string>::iterator it = st.begin(); it != st.end(); ++it) {
            res.push_back(*it);
        }
        return res;
    }
};
```

3、trie tree、DFS

通过及时删除字典树中已经匹配的单词来去重，尝试未成功

```C++
class Solution {
private:
    // structs and functions below are trie-tree related
    struct trieNode{
        bool end;
        unordered_map<char, trieNode*> mp;
        trieNode(): end(false) {}
    };
    trieNode* root;
    void createTrie(vector<string>& words) {
        root = new trieNode();
        for(auto word : words) {
            insertWord(word);
        }
    }
    void insertWord(string& word) {
        trieNode* cur = root;
        for(int i = 0, size = word.size(); i < size; ++i) {
            char c = word[i];
            if(cur->mp.find(c) == cur->mp.end()) cur->mp[c] = new trieNode();
            cur = cur->mp[c];
        }
        cur->end = true;
    }
    bool deleteWord(string word, int idx, trieNode*& cur) {
        char c = word[idx];
        if(idx == word.size()) {
            printf("idx = %d, cur->mp.size() = %d, delete the end\n", idx, cur->mp.size());
            if(cur->end && cur->mp.size() == 0) {cur = nullptr;return true;}
            else return cur->end = false;
        }
        if(deleteWord(word, idx + 1, cur->mp[c])) {
            delete(cur->mp[c]);
            cur->mp[c] = nullptr;
            cur->mp.erase(c);
            printf("delete success, mp.size() = %d, cur = %p\n", cur->mp.size(), cur);
            if(cur->end == true || cur->mp.size() != 0) {printf("delete cur = %p\n", cur);return false;}
            else return true;
        }
        else return false;
    }
    // other elements below
    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; //0: up, 1: right, 2: down, 3: left 
    vector<string> res;
    void find(vector<vector<char>>& b, vector<vector<bool>>& v, int row, int col, trieNode*& cur, string str) {
        if(cur != nullptr && cur->end) {
            res.push_back(str);
            deleteWord(str, 0, root);
            printf("delete done\n");
            printf("end cur = %p\n", cur);
            // cur = nullptr;
        }
        if(row < 0 || col < 0 || row >= b.size() || col >= b[0].size() || v[row][col]) return;
        char c = b[row][col];
        printf("befor dir cur = %p\n", cur);
        if(cur == nullptr || 0 == cur->mp.size() || cur->mp.find(c) == cur->mp.end()) return;
        v[row][col] = true; // drill down
        for(int i = 0; i < 4; ++i) {
            if(cur == nullptr) return;
            else printf("dir cur = %p\n", cur);
            find(b, v, row + dir[i][0], col + dir[i][1], cur->mp[c], str + c);
        }
        v[row][col] = false; // restate
    }
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        int row = board.size(), num = words.size();
        if(0 == row || 0 == num) return {};
        int col = board[0].size();
        if(0 == col) return {};
        vector<vector<bool>> visit(row, vector<bool>(col, false));
        createTrie(words);
        for(int i = 0; i < row; ++i) {
            for(int j = 0; j < col; ++j) {
                find(board, visit, i, j, root, "");
            }
        }
        printf("set.size = %d\n", root->mp.size());
        return res;
    }
};
```

4、trie tree、DFS

通过及时删除字典树中已经匹配的单词来去重，只修改标记，没有真的删除节点元素

```C++
class Solution {
private:
    // structs and functions below are trie-tree related
    struct trieNode{
        bool end;
        bool isexist;
        unordered_map<char, trieNode*> mp;
        trieNode(): end(false), isexist(true) {}
    };
    trieNode* root;
    void createTrie(vector<string>& words) {
        root = new trieNode();
        for(auto word : words) {
            insertWord(word);
        }
    }
    void insertWord(string& word) {
        trieNode* cur = root;
        for(int i = 0, size = word.size(); i < size; ++i) {
            char c = word[i];
            if(cur->mp.find(c) == cur->mp.end()) cur->mp[c] = new trieNode();
            cur = cur->mp[c];
        }
        cur->end = true;
    }
    bool deleteWord(string word, int idx, trieNode*& cur) {
        char c = word[idx];
        if(idx == word.size()) {
            if(cur->end && cur->mp.size() == 0) return true;
            else return cur->end = false;
        }
        if(deleteWord(word, idx + 1, cur->mp[c])) {
            cur->mp[c]->isexist = false;
            if(cur->end == true || cur->mp.size() != 0) return false;
            else return true;
        }
        else return false;
    }
    // other elements below
    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; //0: up, 1: right, 2: down, 3: left 
    vector<string> res;
    void find(vector<vector<char>>& b, vector<vector<bool>>& v, int row, int col, trieNode*& cur, string str) {
        if(cur->isexist == false) return;
        if(cur->end) {
            res.push_back(str);
            deleteWord(str, 0, root);
        }
        if(row < 0 || col < 0 || row >= b.size() || col >= b[0].size() || v[row][col]) return;
        char c = b[row][col];
        if(0 == cur->mp.size() || cur->mp.find(c) == cur->mp.end()) return;
        v[row][col] = true; // drill down
        for(int i = 0; i < 4; ++i) {
            find(b, v, row + dir[i][0], col + dir[i][1], cur->mp[c], str + c);
        }
        v[row][col] = false; // restate
    }
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        int row = board.size(), num = words.size();
        if(0 == row || 0 == num) return {};
        int col = board[0].size();
        if(0 == col) return {};
        vector<vector<bool>> visit(row, vector<bool>(col, false));
        createTrie(words);
        for(int i = 0; i < row; ++i) {
            for(int j = 0; j < col; ++j) {
                find(board, visit, i, j, root, "");
            }
        }
        return res;
    }
};
```



#### [79. Word Search](https://leetcode-cn.com/problems/word-search/)

1、递归回溯

```C++
class Solution {
    vector<string> res;
    int dir[4][2] = {1, 0, 0, 1, -1, 0, 0, -1}; //0: up, 1: right, 2: down, 3: left 
public:
    bool exist(vector<vector<char>>& board, string word) {
        int row = board.size(), col;
        if(0 == row) return {};
        else col = board[0].size();
        if(0 == col) return {};
        vector<vector<bool>> visit(row, vector<bool>(col, false));
        if(find_first(board, word, visit)) return true;
        return false;
    }
    bool find_first(vector<vector<char>>& board, string& word, vector<vector<bool>>& visit) {
        int row = board.size(), col = board[0].size();
        for(int i = 0; i < row; ++i) {
            for(int j = 0; j < col; ++j) {
                if(find_all(board, word, visit, i, j, 0, -1)) return true;
            }
        }
        return false;
    }
    bool find_all(vector<vector<char>>& board, string& word, vector<vector<bool>>& visit, int row, int col, int idx, int from) {
        if(word.size() == idx) return true;
        if(row >= board.size() || row < 0 || col < 0 || col >= board[0].size()) return false;
        if(visit[row][col] || word[idx] != board[row][col]) return false;
        visit[row][col] = true;
        for(int i = 0; i < 4; ++i) {
            if(find_all(board, word, visit, row + dir[i][0], col + dir[i][1], idx + 1, i)) {
                visit[row][col] = false;
                return true;
            }
        }
        visit[row][col] = false;
        return false;
    }
};
```

#### [547. Friend Circles](https://leetcode-cn.com/problems/friend-circles/)

1、并查集 Union-Find Set

```C++
class Union_Find {
    vector<int> parent;
public:
    int cnt;
    Union_Find(int N) {
        cnt = N;
        parent.resize(N);
        for(int i = 0; i < N; ++i) {
            parent[i] = i;
        }
    }
    void Union(int i, int j) {
        int iroot = Find(i);
        int jroot = Find(j);
        if(iroot == jroot) return;
        else {
            parent[iroot] = jroot;
            --cnt;
        }
    }
    int Find(int idx) {
        while(parent[idx] != idx) {
            idx = parent[idx];
        }
        return idx;
    }
};
class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        int len = M.size();
        Union_Find* UFS = new Union_Find(len);
        for(int i = 0; i < len; ++i) {
            for(int j = 0; j < i; ++j) {
                if(1 == M[i][j]) UFS->Union(i, j);
            }
        }
        return UFS->cnt;
    }
};
```



2、DFS

```C++
class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        int len = M.size(), cnt = 0;
        if(0 == len) return 0;
        vector<bool> visited(len, false);
        for(int i = 0; i < len; ++i) {
            if(!visited[i]) {
                ++cnt;
                dfs(M, i, visited);
            }
        }
        return cnt;
    }
    void dfs(vector<vector<int>>& M, int i, vector<bool>& visited) {
        visited[i] = true;
        for(int j = 0, col = M.size(); j < col; ++j) {
            if(1 == M[i][j] && !visited[j]) dfs(M, j, visited);          
        }
    }
};
```

3、BFS

```C++
class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        int len = M.size(), cnt = 0;
        if(0 == len) return 0;
        vector<bool> visited(len, false);
        queue<int> que; 
        for(int i = 0; i < len; ++i) {
            if(visited[i]) continue;
            que.push(i);
            ++cnt;
            while(que.size() != 0) {
                int front = que.front();
                que.pop();
                visited[front] = true;
                for(int j = 0; j < len; ++j) {
                    if(1 == M[front][j] && !visited[j]) que.push(j);
                }
            }
        }
        return cnt;
    }
};
```



4、删除标记

```C++
class Solution {
    int cnt = 0;
public:
    int findCircleNum(vector<vector<int>>& M) {
        int row = M.size();
        if(0 == row) return 0;
        int col = M[0].size();
        if(0 == col) return 0;
        for(int i = 0; i < row; ++i) {
            if(1 == M[i][i]) ++cnt;
            else continue;
            count(M, i);
        }
        return cnt;
    }
    void count(vector<vector<int>>& M, int row) {
        if(0 == M[row][row]) return;
        else M[row][row] = 0;
        int col = M[0].size();
        for(int j = 0; j < col; ++j) {
            if(0 == M[row][j]) continue;
            else M[row][j] = 0;
            count(M, j);
        }
    }
};
```
