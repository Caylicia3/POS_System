# 学习日志 - 2026年9月11日

## 今日学习内容
- 正在学习写入CSV格式文件（ofstream）ofstream file("sales.csv");这表示打开 sales.csv 准备写入。
- !file 和 !file.is_open() 有什么区别:
file.is_open()：仅仅检查这个流对象是否成功关联到了一个实际的文件（即是否成功打开）。
!file：检查的是整个流的状态。它不仅包含了“文件是否打开”，还包含了“之前读写是否发生错误”。
刚打开文件时：为了语义清晰，推荐使用 !file.is_open()。因为它明确告诉看代码的人：“我是在检查文件有没有成功打开”。
读写操作后：推荐使用 !file 或 file.fail()，用来检查刚才的操作是否成功。
- 暂停程序+清屏this_thread::sleep_for(chrono::seconds(5));
            clearScreen();（自定义函数，可跨系统使用）
- auto now = ...
auto 是 C++ 的自动类型推导。编译器会根据右边表达式的类型，自动决定 now 是什么类型。
now 的类型一旦被 auto 推导出来，就固定了，之后不能再改成别的类型。
-  C++中，主要是在函数参数场景下比较：
 写法	                是否拷贝	   能否修改原对象	                能绑定什么	                                  常见用途
const string& barcode	不拷贝	        不能	                      非 const 左值、const 左值、临时对象/字面量	只读输入参数，最常用
string& barcode	        不拷贝	         能	                          只能绑定非 const 左值	                       输出参数、输入输出参数
const string barcode	会拷贝一份副本	不能改这个副本，也改不了原对象	 任何能构造出 string 的实参	                  需要只读副本，但通常不推荐用于大对象
- (重复学习)std::getline(file, line);
会从 file 中不断读取字符，直到遇到换行符 '\n'。
读到的内容存进 line。
换行符 '\n' 会被读走，但不会存入 line。
如果文件里一行是 hello world，那么 line 就是 "hello world"。
空格不会被当作分隔符，所以整行内容都会读进来。
- （重复学习）getline(ss, line, 's'); 是 std::getline 的三参数版本，用法是：
从输入流 ss 中读取字符，直到遇到分隔符 's' 为止，把读取到的内容（不包括 's'）存入字符串 line，并把这个 's' 从流中消耗掉。
- 读取输入的前五个字符:substr()   input.substr(开始位置, 读取长度)
- 读取所有内容，包括空格 getline(cin, input);（一排）
- 怎样去掉字符串的前几位。
std::string s = "sales 2026-09-11";
s.erase(0, 6);   // 从下标 0 开始，删除 6 个字符
// s 变成 "2026-09-11"
第一个参数 0：起始位置。
第二个参数 6：删除的字符个数。
如果字符串长度不足 6，erase 会把能删的都删掉，不会抛异常。
所以这样写很安全：
## 遇到的坑 & 解决方案
- **坑**：普通打开可能会覆盖原来的内容：如果不加 ios::app，默认是 ios::out 模式，每次打开文件都会清空原有内容。
  - **解决**：追加写入 ofstream file("sales.csv", ios::app);file << "你要写入的内容";新的内容就会写到文件末尾，而不会把之前的交易记录覆盖掉。完整写法是：std::ios::app
- **坑**：检查文件是否打开成功
  - **解决**：写文件时，强烈建议加个判断，防止文件因为被其他软件占用或权限不足而打开失败。
- **坑**：别忘记在写完数据后加上 file.close(); （虽然会自动关闭但是这样更好）
  - **解决**：
- **坑**：如何读取电脑当前系统时间，然后写进 sales.csv
  - **解决**：可通过<iomanip>更改输出格式
- **坑**：想要实现功能：自定义day，但是涉及到后续读写csv表格、排序、流水号记录等等问题，所以简化为只能增加天数。
  - **解决**：
- **坑**：传入函数的参数类型，到底是double还是int，到底要不要&，要不要加const
  - **解决**：
- **坑**：sale.h文件中无法识别vector类型
#include 的本质是“无脑复制粘贴”。当 .cpp 里写了 #include "sale.h" 时，编译器会把 sale.h 里的所有代码原封不动地粘贴到 .cpp 里。
编译器是从上往下读代码的。如果在 sale.h 里看到 vector，但在这之前没有见过 <vector> 的定义，它就会报错：'vector' does not name a type。
  - **解决**：如果 sale.h 自己不自带 <vector>，那么任何包含它的 .cpp 文件，都必须在包含 sale.h 之前先包含 <vector>，这极其容易出错。
#ifndef SALE_H
#define SALE_H

#include <vector>   // ✅ 必须加上这个！
#include "product.h" // ✅ 如果 Product 是在 product.h 里定义的，也要包含
- **坑**：注意这里必须写 std::vector，而不是 vector
  - **解决**：void Record(int date, int& num, const std::vector<Product>& products, double total);
- **坑**：头文件里包头文件的重复包含，在 C++ 中，同一个类被定义两次，是编译错误（重定义错误）。
  - **解决**：头文件保护符（Include Guards）
  一个标准的 product.h 长这样：

cpp
// product.h
#ifndef PRODUCT_H   // 如果 PRODUCT_H 没有被定义过
#define PRODUCT_H   // 那就定义 PRODUCT_H

class Product {
    // ... 类的代码
};

#endif              // 结束条件编译

虽然 #ifndef 是 C++ 标准写法，但写起来有点啰嗦。现在绝大多数编译器（GCC, Clang, MSVC）都支持一种更简单的写法：

cpp
// product.h
#pragma once   // 一句话搞定，保证这个头文件在一个 .cpp 中只被包含一次

class Product {
    // ...
};
- **坑**：循环包含（Circular Inclusion）
如果 A.h 包含了 B.h，而 B.h 又包含了 A.h，即使有保护符，也可能出问题（比如 A 里用到了 B 的类，B 里用到了 A 的类，编译器会晕）。
  - **解决**：这时候需要用前向声明（Forward Declaration）。尽量少包含：能用前向声明（class Product;）就少 #include，能让你的代码编译更快。
比如：

cpp
// sale.h
#pragma once
#include <vector>

class Product; // 前向声明：告诉编译器有这么个类，先别管它长什么样

void Record(int date, int& num, const std::vector<Product>& products, double total);
这样 sale.h 就不需要包含 product.h 了，只要在 sale.cpp 里包含 product.h 来实际操作 Product 对象即可。这能大幅减少编译时间。
- **坑**：该放在循环外的东西放在了循环里
  - **解决**：
- **坑**：程序重启以后怎么知道是第几单/流水号
  - **解决**：方法一：程序启动时读取 CSV，找到今天最大的 serial（流水号num）。详见（自定义函数）int GetTodayNum(int date)
  方法二：全局流水号
- **坑**：string转int型
  - **解决**：stoi  int a = stoi(string b)
s  +  to + i
│     │    │
string  to  int
常用类型转换string → int
stoi()

string → double
stod()

int → string
to_string()
- **坑**：C++ 是每个 .cpp 文件单独编译的。一定要确认.cpp中有没有相应的头文件（包括函数原则声明）
  - **解决**：
- **坑**：if 语句的括号很容易写错
  - **解决**：
- **坑**：输入时/n在缓冲区，被getiline读到了。
  - **解决**：
## 今日学到的命令
- g++ -std=c++17 -Wall -Wextra -g *.cpp -o POS.exe

## 待办
- 思路：想要写入记录，首先要记录日期（自定义day）、时间（取系统时间）、
- 
- 
- 