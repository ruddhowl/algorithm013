#include <cstdio>
#include <unordered_map>
using namespace std;


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
        if(it == _head && _capacity - _remain != 1) _head = _head->post;
        if(it->post != NULL) it->post->pre = it->pre;
        if(it->pre != NULL) it->pre->post = it->post;
        _tail->post = it;
        if(_tail != it) it->pre = _tail; 
        it->post = NULL;
        _tail = it;
    }

    void _add_to_tail(node* it) {
        if(_tail != NULL) _tail->post = it;
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
        auto itr = mp.find(key);
        node* it = _head;
        if(itr != mp.end()) {
            it = itr->second;
            it->value = value;
            _move_to_tail(it);
        }
        else {
            printf("%d, _head: %p\n", _remain, _head);
            if(0 == _remain) {
                _head = it->post;
                mp.erase(it->key);
                it->key = key; it->value = value;
                mp[key] = it;
                _move_to_tail(it);
            } else {
                _remain--;
                it = new node(key, value);
                _add_to_tail(it);
                
            }
        }
        if(_capacity - _remain == 1) _head = it;
        printf("it: %p, %p\n", it, _head);
        return;
    }
};
int main() {
    LRUCache *lRUCache = new LRUCache(2);
    lRUCache->put(2, 1); // cache is {1=1}
    // lRUCache->put(2, 2); // cache is {1=1, 2=2}
    lRUCache->get(2);    // return 1
    lRUCache->put(1, 2); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    lRUCache->get(2);    // returns -1 (not found)
    lRUCache->get(3);    // return 3
    lRUCache->put(2, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    lRUCache->get(1);    // return -1 (not found)
    lRUCache->get(3);    // return 3
    lRUCache->get(4);    // return 4

}

