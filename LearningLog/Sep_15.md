# 学习日志 - 2026年9月15日
- fix：加入结构体member stock
  - 已修改/检查：product.csv, product.cpp, main.cpp, admin.cpp, menu.cpp, sale.cpp
## 今日学习内容
- 完成了level0至level2（除自动化编译以外）的所有功能
- 如何实现001 002 001这种有空格输入的检测————不只是靠_getch()空白检测
- stringstream的使用场景和getline有什么区别
  - 总述：
    getline()：从输入流中读取一整段内容
    stringstream：把一段字符串当成“输入流”再次读取和解析
    - getline() ：
  核心作用：从一个输入流中读取一整行，直到遇到换行符。
    - stringstream 的作用
  把 string 变成一个可以像 cin 一样读取的流。
  例如：
string input = "001 002 003";
stringstream ss(input);
string barcode;
ss >> barcode;
第一次：barcode
得到：001
再：ss >> barcode;
得到：002
再：ss >> barcode;
得到：003
因为它会自动跳过空格。

  - 两者组合使用（最常见）
  001 002 003
流程：
cin
 |
 | getline
 ↓
string
"001 002 003"
 |
 | stringstream
 ↓
001
002
003

代码：
string input;
getline(cin,input);
stringstream ss(input);
string barcode;
while(ss >> barcode)
{
    cout << barcode << endl;
}
输出：
001
002
003
  - 
| 方法             | 读取方式  | 适合        |
| -------------- | ----- | --------- |
| `cin >>`       | 一个单词  | 菜单选项、单个条码 |
| `getline(cin)` | 整行    | 用户输入一串数据  |
| `stringstream` | 解析字符串 | 拆分、转换     |
  - stringstream 的常见场景
场景1：拆分字符串
例如：
001 002 003
↓
while(ss >> x)

场景2：CSV解析
你的：
name,barcode,price
↓
getline(ss,name,',')

场景3：字符串和数字转换
例如：string s="123";
转 int：
stringstream ss(s);
int num;
ss >> num;//类型转换问题：因为>>重载了
不过现在一般用：stoi(s);更方便。
反过来：
int num=123;
stringstream ss;
ss << num;
string s=ss.str();
得到："123"

- 总结getline()(在此项目中的用法)
getline(file,line);
第一次：从 CSV 文件读取

键盘输入：getline(cin,input);
第二次 getline：字符串流 → 字段

## 遇到的坑 & 解决方案
- **坑**：加入stock后，CreatProduct函数的赋值部分出问题，Product product{name, barcode, price, stock};
  - **解决**：把结构体中quantity和stock的顺序交换
- **坑**：添加商品/修改价格/更改内存等后没有更新内存中的 products
  - **解决**：每次需要使用product信息时都要用CreateProduct函数重新实时生成。保证数据一致性：CSV 是唯一数据源：
- **坑**：item与product混用
  - **解决**：

## 待办
- 重写product.cpp Checkout函数
- 学习类与对象
- 引用&和指针的关系