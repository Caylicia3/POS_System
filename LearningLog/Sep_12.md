# 学习日志 - 2026年9月12日

## 今日学习内容
- 做项目时需要提前规划好，比如提前把管理员模式和收银员模式分开，不然后期拓展很困难，需要修改很多前面留存的问题
- 范围 for 循环（range-based for loop）。
  - 主要用于遍历容器里的每一个元素。
for (元素类型 变量名 : 容器)
{
    // 对变量进行操作
}
for(int x : nums)可以理解成：从 nums 里面依次拿出每一个元素，把它复制给变量 x，然后执行循环体。
具体用法：
for(int x : nums){
  cout << x << endl;
}

  - 和普通 for 循环比较
for(int i = 0; i < nums.size(); i++)
{
    cout << nums[i] << endl;
}

范围 for：
for(int x : nums)
{
    cout << x << endl;
}

二者等价。范围 for 的优点：不需要写下标  不容易越界  可读性更强
  - 最大的坑：复制问题（类似形参和实参的坑）
for(Product p : products)
{
    p.price = 100;
}

实际上：没有修改商品价格。
因为：Product p 是复制了一份 Product。每循环一次，创建一个新的 Product 类型变量 p（局部变量（local variable）），然后把容器里的当前元素复制给它。
为什么必须写类型？
因为 C++ 是静态类型语言。编译器必须知道：p是什么类型。
for(auto p : products)这里：auto 的意思：让编译器根据右边推断类型。
编译器看到：auto p   知道：products里面装的是Product
所以自动变成：for(Product p : products)

如果想修改原对象：
避坑方法：引用&
看：for(Product& p : products)
这里：没有创建新的 Product。
而是：
products里面的对象
        ↑
        |
        p
p 是它的别名(alias)。
所以：p.price = 100;  等价：products[i].price = 100;

  - const引用（最推荐读取）
如果只是查看：
for(const Product& p : products)
{
    cout << p.name << endl;
}这是工程中最常见写法   
好处：1.不复制(若复制大型对象会浪费性能) 2.不能修改(防止误操作)

  - 可以嵌套：
  eg.vector<vector<int>> cart;
  二维：
for(auto row : cart)
{
    for(auto x : row)
    {
        cout << x;
    }
}
  - 一个容易踩的大坑：不能边遍历边删除
for(Product& p : products)
{
    if(p.price == 0)
    {
        products.erase(...);
    }
}危险。
原因：范围 for 内部实际上使用了迭代器：
iterator ---> 当前元素
你删除元素：vector改变   iterator失效
可能：崩溃   跳过元素   未定义行为
如果要删除：（现代 C++：）erase-remove 或者普通 iterator。
  - 普通 iterator:
如果你需要遍历并删除：
不要用范围 for。
用 iterator：
for(auto it = products.begin(); it != products.end(); )
{
    if(it->price == 0)
    {
        it = products.erase(it);
    }
    else
    {
        it++;
    }
}
重点：
it = products.erase(it);
为什么这样
因为：erase() 会返回删除元素之后的位置。
例如： 删除前：
        it
        ↓
[cola][zero][water]
执行：
it = erase(it);
删除后：
[cola][water]
       ↑
       it

它自动指向下一个元素。
所以安全。
  - rase-remove（现代 C++ 常用）
删除所有价格为 0 的商品。
以前可能想：
for(auto it=products.begin(); it!=products.end();)
{
    if(it->price==0)
        it=products.erase(it);
    else
        it++;
}可以。
但是 C++ 有一个经典写法：
products.erase(
    remove_if(products.begin(),
              products.end(),
              [](Product& p)
              {
                  return p.price == 0;
              }),
    products.end()
);
这个叫：erase-remove idiom（擦除-移除惯用法）
拆开：第一步：
remove_if(...)
不是删除。它只是：把不需要的元素移动到后面。  
例如：
原：
[cola][zero][water][zero]
执行：
[cola][water][?][?]
然后返回一个位置：

                 ↓
               新逻辑结尾
第二步：
erase()
真正删除后面的垃圾区域。
最后：
[cola][water]
为什么叫 erase-remove？
因为两个函数合作：
remove_if
        ↓
移动元素
erase
        ↓
真正删除
所以：
erase + remove
叫：erase-remove
  - 其他遍历方法：
    - 普通for循环
    - 迭代器
例如：
vector<Product>::iterator it;
for(it = products.begin(); it != products.end(); it++)
{
    cout << it->name;
}
这个和范围 for 更接近。end()
不是最后一个元素。
而是：
(eg.)
cola
lollipop
noodles
             ↑
            end()
表示：已经结束的位置


- getline(cin >> ws, input);//包含了两个操作：cin >> ws;getline(cin, name);只是 C++ 允许把它们连写。
- 
- 

## 遇到的坑 & 解决方案
- **坑**：file.close() 后，file 变量没有消失。
  - **解决**：使用fstream时注意命名的区别。
- **坑**：修改密码的逻辑应该是写入新密码——验证新密码——覆盖旧密码，而不是写入新密码——覆盖旧密码——验证新密码——成功/重新返回旧密码
  - **解决**：
- **坑**：如果是默认方式打开 ofstream，一旦创建成功打开文件，原来的内容就会被清空。
  - **解决**：注意使用ofstream打开文件的位置
- **坑**：cin,getline()混用，cin>>读取数据时，会停止在空白字符处，作为结束标志的空白字符（常见是换行符 \n）不会被提取走，仍然留在输入缓冲区，后续getline()作为结束标志的空白字符（常见是换行符 \n）不会被提取走，仍然留在输入缓冲区，造成错误;
  - **解决**：
  方法1：在各个板块统一cin和getline
  方法2：在cin 后接 cin.ignore()//从输入流中读取并丢弃字符，通常用来清除输入缓冲区里不需要的内容，尤其是 cin >> 之后残留的换行符。
  cin.ignore(n,delim)
  最多丢弃 n 个字符；
  如果中途遇到字符 delim，就停止，并且 delim 本身也会被丢弃；
  默认写法 cin.ignore() 表示丢弃 1 个字符，通常就是换行符 '\n'。
  方法三：使用 ws   更适合处理前面的空白：
  cin >> age;
  getline(cin >> ws, name);//ws 会吞掉前面的空白字符。
  //ws 是 C++ 标准库里的一个输入流操作符（manipulator），全名是：std::ws  作用：读取并丢弃输入缓冲区开头所有的空白字符。
  空白字符包括：
  空格 ' '
  换行符 '\n'
  制表符 '\t'
getline(cin >> ws, input);//包含了两个操作：cin >> ws;getline(cin, name);只是 C++ 允许把它们连写。
为什么可以写 cin >> ws 放进 getline？
关键点：>> 运算符会返回输入流本身。
比如：
cin >> ws
执行完以后，它仍然是一个：istream&类型。
所以：
getline(cin >> ws, name);实际上等价于：getline( (cin >> ws), name );
也就是：
先：cin >> ws得到清理后的输入流
然后：getline(这个输入流, name)

- **坑**：ws 会吃掉所有开头空白,不管有几个
  - **解决**：需要保留输入开头的空格时，就不能用 ws

## 今日学到的命令
- 
- 

## 待办
- 把新价格写入product.csv文件
- sales 1/checkout//优化
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