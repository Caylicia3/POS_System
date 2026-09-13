# 学习日志 - 2026年9月13日

## 今日学习内容
- 一个有返回值的函数，调用时可以不接收它的返回值。
eg.stod(input, &pos);
- 
- 

## 遇到的坑 & 解决方案
- **坑**：回填商品信息时没写表头
  - **解决**：
- **坑**：不同的数据类型，不应该共用同一个验证规则。
  - **解决**：条形码输入检验用NumCheck(),价格输入检测用PriceCheck();
- **坑**：cin >>  后接 getline()会读取\n，导致程序自动进行到下一步
  - **解决**：cin.ignore(1000,'\n');
- **坑**：数据记得及时返回初始状态：.csv文件！
  - **解决**：
- **坑**：
  - **解决**：
- **坑**：
  - **解决**：
- **坑**：
  - **解决**：
- **坑**：
  - **解决**：
- **坑**：
  - **解决**：
## 今日学到的命令
- 
- 

## 待办
- 
- 
- 把新价格写入product.csv文件
- sales 1/checkout//输入优化
getline(cin >> ws, input);更适合输入
因为命令前面多余的空格一般没有意义，可以直接清掉。你之后解析字符串会更稳定。
- 调试管理员模式的功能
- 学习类与对象
- STL是什么
- 范围 for 内部实际上使用了迭代器：
iterator ---> 当前元素
你删除元素：
vector改变
iterator失效
是什么意思

迭代器那里没完全学懂

现代 C++ 写法：在 C++11 之后，其实可以用更简洁的 STL 算法代替手写循环：
cpp
#include <algorithm>
#include <cctype>
bool IsNumber(const string& input) {
    return !input.empty() && std::all_of(input.begin(), input.end(), ::isdigit);
}
总结来说，这段代码的作用就是：只要字符串里出现一个不是 0-9 的字符，就判定为“不是数字”；全部都是 0-9，才判定为“是数字”。

- 你的项目这里有一个更大的优化方向，比减少一次 for 更值得做：
现在：barcode -> 遍历vector查找
时间复杂度：O(n)
如果商品很多，真实系统会：unordered_map<string, Product>
变成：barcode -> 直接找到商品
接近：O(1)