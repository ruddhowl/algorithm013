# 学习笔记

## 递归

引入：树是用递归定义的，所以天生就很适合用递归的思想来解决树相关的问题。

要点：

函数递归的本质就是**循环执行相同的函数体**。

**递归跟栈**有相同的特点，所以通常递归能解决的问题，都可以转换成栈的问题。

找**最近可重复性子问题**来解决问题，把复杂问题拆解成更小的重复的子问题，来降低复杂度。

重复性也有优劣之分，如果找到的重复子问题，仍然过于复杂，需要考虑是否有更简单的更优的子问题。

借助**数学归纳法**的思想，来帮助理解递归。

### 泛型递归的代码模板

```C++
// C/C++
//边界条件，先是当前层次的预处理逻辑，然后深入到下一层，逐渐往递归的边界靠近，最后逐级返回，每一层再做剩余的收尾工作。
void recursion(int level, int param) { 
  // recursion terminator
  if (level > MAX_LEVEL) { 
    // process result 
    return ; 
  }
  // process current logic 
  process(level, param);
  // drill down 
  recursion(level + 1, param);
  // reverse the current level status if needed
}
```

```python
# Python
def recursion(level, param1, param2, ...): 
    # recursion terminator 
    if level > MAX_LEVEL: 
	   process_result 
	   return 
    # process logic in current level 
    process(level, data...) 
    # drill down 
    self.recursion(level + 1, p1, ...) 
    # reverse the current level status if needed
```

```java
// Java
public void recur(int level, int param) { 
  // terminator 
  if (level > MAX_LEVEL) { 
    // process result 
    return; 
  }
  // process current logic 
  process(level, param); 
  // drill down 
  recur( level: level + 1, newParam); 
  // restore current status 
}
```

```javascript
// JavaScript
const recursion = (level, params) =>{
   // recursion terminator
   if(level > MAX_LEVEL){
     process_result
     return 
   }
   // process current level
   process(level, params)
   //drill down
   recursion(level+1, params)
   //clean current level status if needed
}
```



### 需要警惕的误区：

不要人肉搜索，也就是忍住想要自己模拟递归过程的冲动。



## 分治、回溯

本质上都是递归，都是通过子问题来解决问题，同样需要找重复性。

回溯算法实际上一个类似枚举的搜索尝试过程，主要是在搜索尝试过程中寻找问题的解，当发现已不满足求解条件时，就“回溯”返回，尝试别的路径。回溯法是一种选优搜索法，按选优条件向前搜索，以达到目标。但当探索到某一步时，发现原先选择并不优或达不到目标，就退回一步重新选择，这种走不通就退回再走的技术为回溯法，而满足回溯条件的某个状态的点称为“回溯点”。许多复杂的，规模较大的问题都可以使用回溯法，有“通用解题方法”的美称

遍历所有可能的情况，在每一种情况的多个关口进行判断，及时剪枝

又称“试探法”，类比深度遍历

···python
def backtrace():
  for choice in choices:
    # set state
    # process
    if true:
      backtrace() # drill down
    # revert state
```





