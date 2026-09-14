# 学习日志 - 2026年9月14日

## 今日学习内容
- enum class（枚举类）
//可用于admin.cpp中的DulicateCheck函数，但是本项目中未采用该写法
enum class CheckType{
    Name,
    Barcode
};
bool DuplicateCheck(string add, CheckType type){

    vector<Product> products = CreateProduct("product.csv");

    for(Product product : products){

        if(type == CheckType::Barcode && product.barcode == add){
            return false;
        }

        if(type == CheckType::Name && product.name == add){
            return false;
        }
    }

    return true;
}
调用举例：
DuplicateCheck("001", CheckType::Barcode);
DuplicateCheck("cola", CheckType::Name);
- 
- 

## 遇到的坑 & 解决方案
- **坑**：find() 是 string 的成员函数，用来查找某个字符/字符串的位置。
  - **解决**：返回值不是bool，是string::size_type
  所以想用来判断有没有，要借助string::npos
  if(New.find(',') != string::npos)
{
    cout << "Has comma";
}
- **坑**：追加写入文件时注意是否换行
  - **解决**：追加时记得在最后写<<endl;若不确定文件最后有没有换行：
方法1（最简单）：读取最后一个字符（推荐你现在用）
逻辑：
打开文件
看文件最后一个字符是不是 \n
如果不是，先补一个换行
再写新内容
例如：
bool NeedNewLine(string filename)
{
    ifstream file(filename, ios::binary);
    file.seekg(-1, ios::end);
    char last;
    file.get(last);
    return last != '\n';
}
ofstream file("product.csv", ios::app);
if(NeedNewLine("product.csv"))
{
    file << '\n';
}
file << "cola,001,3.5\n";
- **坑**：其实：endl
也会换行：
等价：file << price << '\n' << flush;
但是写文件时通常更推荐：'\n'
因为：endl 会强制刷新缓冲区，大量写文件时效率低，你的项目规模没影响，但养成习惯比较好。
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
- **坑**：
  - **解决**：
## 今日学到的命令
- 
- 

## 待办
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