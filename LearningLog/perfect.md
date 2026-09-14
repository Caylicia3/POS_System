- 输入安全检测（Error）
- 注意：条形码用string类型比int方便很多，且int无法表示001(只能表示成1)，后续各种输入和检测都可以统一成string类型
- 把跳转升级为请按任意键继续
- 密码能不能是back?貌似可以？现阶段默认可以，但若之后出现bug请从AdminCase1处修改
- 怎么实现打印所有record?(sale.csv)
- 开发清空所有历史记录的功能:清空csv所有记录（但保留第一排表头）
ofstream file("sale.csv");
默认会把原来的文件内容清空，然后重新创建/打开这个文件。

补充：本项目采用把表头写死的做法，如果不想把表头写死
void ClearSales(){
    ifstream oldFile("sale.csv");

    string header;
    getline(oldFile, header);

    oldFile.close();

    ofstream newFile("sale.csv");

    newFile << header << endl;

    newFile.close();
}
它的逻辑是：
打开 sale.csv
      ↓
读取第一行表头
      ↓
关闭
      ↓
重新以写入模式打开 sale.csv
      ↓
旧内容全部清空
      ↓
把刚才保存的表头写回去
      ↓
完成

- 怎样实现密码的边读入边输出：可以用 _getch()：#include <conio.h> 用户每按一个键，程序立即得到一个字符。

- 管理员模式运行思路：
       Case6
         |
      密码验证 ( VerifyPassword )<--|
         |_______验证失败___________|
         |
         |验证成功
         |
   进入管理员模式（AdminMenu）
         |___1.admin修改密码 AdminCase1
         |___2.setprice修改价格 AdminCase2
- 怎样添加密码验证次数限制功能：使用for循环限制次数

- 怎么分开输入的barcode和price:让用户分别输入（！因为.csv读取的问题，不能出现’,’）

- 怎么检测用户有没有输入',':想法1——使用getch实时读取每一个值进行检测;
                          想法2——输入完成后检测是否有',';
  - 想法2方案一：
string input;
getline(cin >> ws, input);
if(input.find(',') != string::npos)  //find() 会返回找到的位置。 需要头文件<string>
{
    cout << "包含逗号";
}
else
{
    cout << "没有逗号";
}
例如:string input = "abc,def";
执行：input.find(',')
返回：3
因为：
a b c , d e f
0 1 2 3 4 5 6

如果没有找到：
input.find(',')返回：string::npos
它表示：没有找到

所以判断：input.find(',') != string::npos就是：找到了逗号
  - 想法2方案二：自己写函数
  bool HasComma(string input)
{
    for(char c : input)
    {
        if(c == ',')
        {
            return true;
        }
    }

    return false;
}
  - 想法2方案三：使用 count
如果你还想知道有几个逗号：
#include <algorithm>
int count = std::count(input.begin(), input.end(), ',');
例如：input = "a,b,c";
结果：count = 2;

一个细节：
如果你检查的是字符：find(',')
用单引号：','因为它是 char。
如果检查的是字符串：find("sales")
用双引号："sales"
区别：
','     // 一个字符 char
","     // 一个字符串 string


- 问题：怎么样把新价格写入product.csv文件？
（推荐）
已经有：vector<Product> products;
所以流程：
product.csv
    |
    ↓
CreateProduct()
    |
    ↓
vector<Product>
    |
修改某个 Product.price
    |
    ↓
重新写入 product.csv （使用函数）
eg.for(auto& p : products)//注意这里：必须有引用，不然无法修改值
{
    if(p.barcode == "001")
    {
        p.price = 4.00;
    }
}

void SaveProducts(vector<Product>& products)
{
    ofstream file("product.csv");//不是追加

    file << "name,barcode,price\n";

    for(const auto& p : products)
    {
        file << p.name << ","
             << p.barcode << ","
             << p.price << "\n";
    }
}


- 输入怎么才能更安全？

- 怎么检验/保证输入全是数字：
方案1：使用int类型做输入，用if(!(cin >> a))
或int a;cin >> a;if(!cin){cout << "输入错误";}检验
问题 有一个坑：
比如：
int a;
cin >> a;
输入：123abc
结果：a = 123
而：abc还留在输入缓冲区。因为 cin 看到：123可以转换成整数，所以它认为成功。
如果你要求：用户必须输入纯数字，不能有其他字符
那么：
int a;
cin >> a;
不够严格。

cin 读取 int 时发生了什么:
cin 知道你要的是：int,所以它会尝试把字符转换成整数。
它读取：123
发现：a不是数字。
于是：“到这里为止，我已经成功得到一个整数 123。”
所以：a = 123;
此时：
缓冲区变成：
a b c \n
↑
还剩这些   并不是：(全部丢弃)

方案2：遍历每个字符（推荐）
bool IsNumber(string input)
{
    for(char c : input)
    {
        if(!isdigit(c))
        {
            return false;
        }
    }

    return true;
}
坑：还有一个边界情况：空字符串（" "也会返回true 需补充if(input.empty())
        return false;
bool IsNumber(string input)
{
    if(input.empty())
        return false;

    for(char c : input)
    {
        if(!isdigit(c))
            return false;
    }

    return true;
}
具体使用示例：
string input;
getline(cin >> ws, input);
if(IsNumber(input)){
    cout << "输入的是数字";
}else{
    cout << "输入不是数字";
}
注意：isdigit()需要头文件#include <cctype>
isdigit()作用：判断一个字符是不是十进制数字字符（即 '0' 到 '9'）。
返回值：如果是数字字符，返回非 0 值（通常视为 true）；如果不是（比如字母、空格、标点符号），返回 0（false）。
  - 注意：它只认单个字符，不认整个字符串，也不认负数、小数。
空字符串问题：如果用户什么都没输入，这个函数会返回 true。如果你希望空字符串也视为不合法，可以在开头加一句 if(input.empty()) return false;。
  - 负数和小数：这个函数不支持负数（-5）和小数（3.14），因为它只允许纯 0-9 的字符。
  - 头文件：使用 isdigit() 必须包含 <cctype>。
  - 现代 C++ 写法：在 C++11 之后，其实可以用更简洁的 STL 算法代替手写循环：
cpp
#include <algorithm>
#include <cctype>
bool IsNumber(const string& input) {
    return !input.empty() && std::all_of(input.begin(), input.end(), ::isdigit);
}
总结来说，这段代码的作用就是：只要字符串里出现一个不是 0-9 的字符，就判定为“不是数字”；全部都是 0-9，才判定为“是数字”。

方法3：
用 stoi() + 异常

也可以：

try
{
    int num = stoi(input);
    cout << "数字";
}
catch(...)
{
    cout << "不是数字";
}

但是它有一个坑：

input = "123abc"

stoi 会得到：

123

它不会认为完全错误。
所以如果你要求：

必须全部字符都是数字

那么 isdigit() 更合适。

方法3：正则表达式

可以：

regex_match(input, regex("[0-9]+"))

但是对于你的阶段和 POS 项目：

❌ 没必要。

- 输入后（不论成功还是错误）的再输入——使用while或do while循环

- 如何检测输入的string类型商品价格能否转换成double型
不能直接用 自定义的NumCheck() 检查价格，因为 isdigit() 只判断单个字符是否为数字，遇到小数点 '.' 会返回 false，导致合法的小数价格被判定为非法。
bool PriceCheck(string input)
{
    try
    {
        stod(input);
        return true;
    }
    catch(...)
    {
        return false;
    }
}
不能直接用if(!stod(New))检测，
原因1：
stod() 不是返回失败值，而是抛异常。
string New = "abc";
double price = stod(New);
不会返回：false
而是直接：terminate called after throwing an instance of 'std::invalid_argument'
原因2：
if(!stod(New)){
    cout << "Error 14: Price Must Be a Number.!" << endl;
}
stod() 返回的是 double。
例如：stod("5")
返回：5.0
然后：!5.0
结果：false
所以不会进入错误。
但是：stod("0")
返回：0.0
那么：!0.0
是：true
你的程序会认为：0元价格 = 非数字
这是错误的。
原因3：还有一个更隐蔽的问题：
stod()允许部分转换。//常错
例如：stod("5abc") 结果：5
也就是说：
string New = "5abc";
double price = stod(New);可能成功。
但是对于价格：5abc 元显然应该是非法输入。

正确方式：用异常捕获
因为 stod() 遇到非法字符会抛异常：
例如：stod("abc")
会报：invalid_argument
解决：使用size_t pos;记录转换到了哪里。
bool PriceCheck(string input)
{
    try
    {
        size_t pos;//size_t 是 C++ 标准定义的一个无符号整数类型，(表示一个非负整数) 专门用来表示对象的大小、数组长度、容器大小、索引等。（坑：它是无符号数，所以没有负数。）
        stod(input, &pos);//stod() 有第二个参数：stod(string, position)
                          //&pos 表示：把 pos 变量的地址交给函数。 &在这里是取地址符。修改 pos是通过引用/指针参数传出去的。
                          //stod() 不只是想告诉你转换结果：double还想告诉你：我转换到了字符串哪里。所以它需要修改你的 pos。
        return pos == input.size();//检验pos == input.size()为真or假
    }
    catch(...)
    {
        return false;
    }
}
try 和 catch 是什么？
这是 C++ 的异常处理机制。
因为：stod("abc")会产生异常。
如果没有处理：double x = stod("abc");程序可能直接崩溃。所以：
try
{

}
catch(...)
{

}
意思：尝试执行：
try
{
    stod(s,&pos);
}
如果成功：继续运行。
如果发生异常：
跳到：catch(...)
{
}
例如：
输入：s="abc";
执行：stod(s,&pos);
发生：invalid_argument异常
程序跳：
catch(...)
{
    return false;
}
所以：PriceCheck("abc")返回：false

catch(...) 的三个点是什么意思:
这个：
catch(...)
表示：捕获所有类型的异常。
例如：catch(const invalid_argument& e)只捕获：转换失败。
但是：catch(...)比较粗暴：任何异常都抓。对于你的价格检测：完全可以。


逻辑：
能转换
  +
全部字符都被转换
        ↓
      合法价格
s = "12.5abc"

转换：
1 2 . 5 a b c
0 1 2 3 4 5 6
stod:
1 2 . 5
-------
       ^
       pos=4

注意：stod(input, &pos);
不会改变 input 的类型，也不会改变 input 的内容。
input 仍然是：string
只是 stod() 读取了这个 string，然后返回一个新的 double 值。
举个例子：
string input = "3.5";
size_t pos;
stod(input, &pos);
执行后：input还是："3.5"   类型：string没有变化。
真正转换出来的 double 如果你想保存，需要接收返回值：double price = stod(input, &pos);

//现在的：if(New.find(',') == string::npos)逗号检测其实不需要。
因为价格转换本身已经会拒绝：3,5这种格式。
保留原因：便于提示用户为什么输入非法

- 按任意键继续功能如何实现:
方法2：真正的“任意键继续”（Windows）

因为你的环境是 Windows（PowerShell + MSYS2），可以用：

#include <conio.h>

void Pause(){
    cout << "Press any key to continue...";
    _getch();
}

然后：

Pause();

效果：

Press any key to continue...

你按：

a

或者：

Space

或者：

Enter

都会立即继续。

_getch()是什么？

它来自：

#include <conio.h>

作用：

_getch();

读取一个字符：

但是：

不需要 Enter
不会显示输入内容

例如：

char c = _getch();

如果你按：

A

那么：

c == 'A'

提醒一下：<conio.h> 是 Windows 专用，Linux/macOS 不一定有。

- product.cpp 里的 Checkout函数有bug,如果输入001 001 空格后再\n无法进行下一步，因为cin不会读取\n，建议有时间把Checkout函数重写，把功能们拆开