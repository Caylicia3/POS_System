# 学习日志 - 2026年9月23日

## 今日学习内容
- 回顾main.cpp menu.cpp product.cpp
- <fstream>中的类：
 - ifstream:输入流的一种——文件输入流，来自<fstream>头文件。
  - ifstream 可以理解成一种“类类型（class type）”，而：ifstream file(filename);是在用这个类型创建一个对象 file。
  - 全称：ifstream = input file stream
 - ofstream (与ifstream对应)
  - 全称：ofstream = output file stream文件输出流
 - fstream 既可以读，也可以写
- ifstream作用汇总：ifstream 主要可以做这些事：

 - 读取
string line;
getline(file, line);//读取一整行。
也可以：
int x;
file >> x;//用 >> 读取数据。
 - 判断文件是否成功打开
if (!file.is_open()) {
    cout << "Failed to open file";
}
is_open() 可以检查：
文件现在是不是成功打开着。判断读取有没有出错
例如：
if (file.fail()) {
    ...
}
可以检查流是否进入失败状态。

- 还有：
file.eof()
用于判断是否到达文件末尾。

关闭文件
file.close();//表示:关闭这个文件输入流。
不过 ifstream 对象生命周期结束时，会自动关闭文件，所以很多情况下你不手动 close() 也可以。

 - 控制文件读取位置
它还可以移动“读取指针”，例如：
file.seekg(...);
以及：file.tellg();用于获取/移动当前读取位置。

## 待办
- 学习指针
- 简化展示流程
- 学习类与对象

