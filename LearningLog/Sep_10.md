# 学习日志 - 2026年9月10日

## 今日学习内容
- for (Product product : products) {
    cout << product.name << " "
         << product.barcode << " "
         << product.price << endl;
}
- const std::string& line 的意思是：

line 是一个对 std::string 对象的“常量引用”，也就是某个字符串的只读别名。

它通常出现在函数参数里，表示这个函数接收一个字符串，但不会修改它，也不会拷贝它。
- & 在 C++ 里有三种常见含义
写法	含义	例子
&变量	取地址	int* p = &a;
类型&	声明引用	int& r = a;
a & b	按位与	int c = a & b;
- 引用是什么？
引用就是给一个已经存在的对象起个别名。

cpp
int a = 10;
int& r = a;   // r 是 a 的别名
r = 20;       // 等价于 a = 20
r 不是新变量，它和 a 是同一个东西。

对 r 的操作，就是对 a 的操作。

引用必须在定义时绑定到某个对象，之后不能换。

## 遇到的坑 & 解决方案
- **坑**：注释里误写了‘\’导致程序无法正常运行
  - **解决**：

## 今日学到的命令
- `git init`：初始化本地仓库
- `git remote add origin [网址]`：关联远程仓库

## 待办
- 学习制作项目
- 学习类与对象
- 学习用CSV 格式记录
- 学习stringstream