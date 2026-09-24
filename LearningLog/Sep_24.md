# 学习日志 - 2026年9月24日
梳理到了sale.cpp
## 今日学习内容
- fstream和streamstring的区别：
 - fstream：负责“和文件打交道”
 - stringstream：负责“和字符串打交道”
 - 为什么不能直接用 ifstream 替代代码中streamstring的部分。因为 ifstream 面对的是：整个文件。而 stringstream 面对的是：当前这一行字符串。
 getline(file, line);     // 第一层：从文件读取一整行
 stringstream ss(line);   // 第二层：解析这一整行
 - 总结：
 文件：
ifstream   → 读文件
ofstream   → 写文件
fstream    → 读 + 写文件
字符串：
istringstream   → 从字符串读
ostringstream   → 向字符串写
stringstream    → 字符串读 + 写
- 读取!=存入：getline会读取\n但不会存入，会把\n直接消耗掉。
- substr() 的基本用法：
 - string.substr(开始位置)；
   input2.substr(1)就是：从下标 1 开始截取。
 - s.substr(2, 3);意思是：从下标 2 开始，取 3 个字符。
- 

## 遇到的坑 & 解决方案
- **坑**：Case4 stoi()忘记检查string是否能转成数字
  - **解决**：加入NumCheck()进行检查

## 待办
- 学习指针
- 简化展示流程
- 学习类与对象
