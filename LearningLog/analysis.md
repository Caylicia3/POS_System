# 分析&梳理
## main.cpp
### do-while循环
- 可以直接改成while(true){}循环，这里没有改的原因是当时写的时候改过几次，其中有一版退出循环（结束程序）的条件不像现在这样在写在switch case循环里，而是写在do-while(里面)，后来发现运行效果不理想就又改了，但是这个do-while循环被保存下来了。

### cin>>
- cin>>与if条件判断合并，一次性完成两步。
- `cin.clear(); ` 清除cin的错误状态          
  `cin.ignore(10000, '\n');` 丢掉这一行错误输入,此行代码的意思是：从输入缓冲区里丢弃（忽略）最多 10000 个字符，或者直到遇到换行符 \n 为止（换行符也会被丢弃）。

  添加该两行代码的目的：输入定义的是int类型。但如果输入不是int型，会读取失败，此时cin 会设置内部的状态标志 failbit（失败位）；之后 cin 处于“错误状态”，后续所有输入操作都会直接失败，不再真正读取；如果不恢复，程序就会陷入死循环或无法继续输入。

  cin.clear() 不带参数时，会把流的状态设置为 goodbit，也就是“一切正常”。它只修改流的状态，不碰输入缓冲区里的任何字符。

  此时：cin 状态变成 failbit；缓冲区里还留着 非法输入\n。如果只调用：cin.clear();流状态恢复正常了，但缓冲区里的 非法输入\n 还在。下一次 cin >> x 又会读到 非法输入，又失败。所以通常还要配合：cin.ignore(10000, '\n');把这一行错误输入丢掉。

  其他的解决方法：本项目的其他部分通常采用string输入字符串再用if或switch case判断，回避了cin>>输入状态错误的情况。

- 在会用到getline()的情况前加上了cin.ignore(10000, '\n');//去掉缓冲区剩下的 \n，避免自动读取\n。

### switch case
- break用于离开switch case

## menu.cpp
### ShowMenu()函数
- 形参：日期int date  和流水号int num
- 输出（主）菜单面板

### clearScreen()函数
- 作用：清屏——清空当前终端/命令行窗口里的内容，让界面看起来像“刷新”了一样。

>void clearScreen() {
>    #ifdef _WIN32  // 如果是 Windows 系统
>        system("cls");
>    #else          // 如果是 Linux 或 macOS 系统
>        system("clear");
>    #endif
>}

\#ifdef _WIN32 // 预处理指令，"如果 _WIN32 这个宏已经被定义了，就编译下面的代码。"更进一步，可以简单理解成：“如果当前是在 Windows 系统下编译……”
_WIN32 是 Windows 编译环境通常会自动定义的宏。

\#else //就是：否则编译另一部分。

\#endif //就是：条件编译到这里结束。

- \#ifdef 和 if 有什么区别：
if
↓
程序运行时判断

\#ifdef
↓
编译之前判断
- 
宏 → 预处理器处理的东西
\#define → 定义宏
\#ifdef → 判断宏是否存在
\#else → 否则
\#endif → 条件编译结束
### Redirect()函数
- 作用：伪跳转。通过暂停和清屏达到伪跳转的效果
this_thread::sleep_for(chrono::seconds(2)); //暂停两秒
- 拆解：
 - this_thread可以简单理解成：“当前正在运行的这个线程”——POS 程序正常情况下就是一个主线程在运行。
 - sleep_for 可以理解成：让当前线程暂停一段时间。
 - this_thread::sleep_for(chrono::seconds(2));就是：让当前线程暂停 2 秒。注意，它不是：“让电脑停 2 秒”而是：让当前程序的当前线程暂时不继续执行。
 - chrono是 C++ 标准库里的一个命名空间，专门处理：时间、时间间隔、时钟等东西。seconds 是其中表示“秒”的一种时间单位。chrono 是 std 里面的一个命名空间。
 - chrono::seconds(2)可以理解成：创建一个“2秒”的时间长度。
 - this_thread::sleep_for//需要头文件：<thread>
 - chrono::seconds()//需头文件：<chrono>
 - 加上命名空间std:
   `std::this_thread::sleep_for(std::chrono::seconds(2));`

### Exit()函数
>void Exit(){
>    cout << "Exiting In 5 Seconds." << endl;
>    this_thread::sleep_for(chrono::seconds(5));
>    clearScreen();
>}
具体情况同Redirect()函数。

### ReturnMenu()函数
>void ReturnMenu(){
>    cout << "Returning to Main Menu In 2 Seconds..." << endl;
>    this_thread::sleep_for(chrono::seconds(2));
>    clearScreen(); 
>}
具体情况同Redirect()函数。

### Refresh()函数
>void Refresh(){
>    cout << "Refresh In 2 Seconds..." <<endl;
>    this_thread::sleep_for(chrono::seconds(2));
>    clearScreen();
>}
具体情况同Redirect()函数。

## product.cpp
### 全局变量：const double discount = 2;
- 作用；用于满减优惠计算，便于后续修改。

### vector<Product> CreateProduct(const string& filename)函数
- 作用：通过`product.csv`文件生成存储结构体类型 Product 对象的动态数组——`products`。
- 函数形参：const string& filename
 - 拆解：const 表示常量，函数内部不能通过该引用修改原对象。& 表示引用传递，函数不会为形参创建一份新的 string 副本，而是直接引用调用时传入的对象。（只读引用）。会减少拷贝带来的时间和内存开销。
- ifstream:输入流的一种——文件输入流，来自<fstream>头文件。
 - ifstream 可以理解成一种“类类型（class type）”，而：ifstream file(filename);是在用这个类型创建一个对象 file。
 - 全称：ifstream = input file stream
- ofstream (与ifstream对应)
 - 全称：ofstream = output file stream文件输出流
- fstream 既可以读，也可以写
- ifstream是类型；
file是对象名。
- std::ifstream 是 C++ 标准库提供的一个类。
ifstream file;就是在创建一个 ifstream 对象。
"product.csv"是传给构造函数的参数。
- getline(file,line);这里的 file 必须是一个可以作为输入流使用的对象。而 ifstream 本身就是一种输入流类型。所以它能配合 getline()。可以理解为：“从 file 这个文件输入流里，把一整行数据读到 line 中。”
- 通过在while循环开始之前使用getline(file,line)读取并丢弃第一行，以达到跳过表头的作用。
- 为什么要使用类stringstream ss(line):getline(stringstream,string,char)函数要求第二个参数是一个 string，第三个参数是分隔符。
 - getline(ss,name,',');含义：从ss中读取内容到name中，直到读到','为止。
- 为什么要用stringstream类型拆解输入而不直接拆解字符串line:其实也可以，但是写出来stringstream会更简洁明了。

直接操作string找逗号：
size_t p1 = line.find(',');
size_t p2 = line.find(',', p1 + 1);
size_t p3 = line.find(',', p2 + 1);

string name = line.substr(0, p1);
string barcode = line.substr(p1 + 1, p2 - p1 - 1);
string pre_price = line.substr(p2 + 1, p3 - p2 - 1);
string stock_str = line.substr(p3 + 1);
最后再：
double price = stod(pre_price);
int stock = stoi(stock_str);

- ss >> stock;（ss里是字符串类型，stock是int类型，但可以直接这样）>> 可以自动按照 后面的类型（int） 去解析。
- products.push_back(product);向动态数组中添加元素
- 补充：malloc在C中常用于手动申请动态内存。
- return products;把生成的结果通过返回值返回。（如果不通过返回值返回，也可以通过引用或指针，让函数直接修改调用者传入的 vector）

### void ShowProductInfo(const string& barcode) & bool Judge(string& line1, string& line2, string& line3, const string& barcode, bool& valid)
- 最开始采用的是直接在源代码中输入，后来把商品信息通过csv文件管理后改成了通过csv动态读取。
- 新思路：可以直接使用CreateProduct()函数生成结构体数组，结合for范围循环判断。
- if(Judge(line1, line2, line3, barcode, valid)){}中的Judge是自定义函数。
- Judge()的作用：判断条形码是否为有效输入，valid是用来判断文件是否正常打开的。ShowProductInfo函数里没写valid = 0的情况，是因为valid = 0的情况在Judge()里已经处理了。

### void Case1()
- 通过while循环检测是否应该退出(`exit` || `quit`)

### void Case2(int date, int& num, const bool isVIP)
分析的是重写版，原版逻辑不清，执行起来很困难。
- cin.ignore(1000,'\n');//处理回车，因为getline会读取回车。（读取！=存入\n）

getline(cin, input2);会把这一行读到的内容取出来，并把结尾的换行 \n 从输入流中取走，但不会把 \n 存进 input2。
cin >> n;回车产生的 \n 还留在输入缓冲区里。
于是下一句：getline(cin, input);一看到这个 \n，就认为：“这一行结束了。”所以直接读到一个空字符串。
- getline(cin, input2);
 - getline函数：读取一整行输入。
 - cin即 标准输入流，通常就是键盘输入。
 - getline(cin, ...)就是：从键盘输入中读取一整行。
 - 对比：前面出现过的getline(file, line);是：从文件输入流 file 中读取一整行。
 - 理解：getline(从哪里读[流], 读到哪里[变量])。getline(cin, input2);即从键盘输入（cin>>）中读取一整行，并把读取到的内容存进 input2。
- 使用stringstream来依次处理一排中读取到的内容。
- 使用int record（也可换为bool型）来记录到底要不要输出添加商品后会显示的当前购物车。
- for范围循环：
遍历 products 中的每个元素，用 product 这个名字访问它，不复制（在未使用const的情况下可修改）。
for(auto& product : products){
  if(input2 == product.barcode){
    if(product.stock == 0){
      StockCheck = false;
      }
  }
}

 - auto:自动判断后面的变量是什么类型
  - 使用原因：Product product(偷懒不想写类型名Product)
 - 语法：
for (类型 变量 : 容器) {
    // 对变量进行操作
}
 - 含义：把 容器 里面所有元素依次遍历一遍。
 - 使用引用的原因：
for (Product product : products)相当于：每次把容器里的 Product 复制一份给 product。

for (Product& product : products)就是：
product 是容器中那个元素本身的引用。

for (const Product& product : products)意思是：用引用访问原来的元素，但不允许通过 product 修改它。（相当于只读）
- input2 = input2.substr(1);含义：把 input2 从下标 1 开始，到字符串末尾的内容取出来，再重新赋值给 input2。

- 函数整体思路：（DuplicateCheck()详见admin.cpp）
 - 通过while循环实现重复读取和退出判定。
 - 通过DuplicateCheck()函数判断条形码是否有效。
 - 通过bool StockCehck判断库存是否足够。
 - 检查首位是'-'来进入减少商品功能。
 - bool QuantityCheck判断购物车中的商品数量是否足够。
 - 涉及到关于结账部分的内容时有会员判定，决定是否打折。
 - 当处理完一行的输入后再判断（record）是否需要输出添加商品后的购物车内的信息。

## sale.cpp
### void Record(int date,int& num,const vector<Product>& products,double total)
记录结账记录的函数
- ofstream file("sale.csv",ios::app);ios::app：(append)追加写入——每次写入内容时，都写到文件末尾，不覆盖原来的内容。
如果直接写ofstream file("sale.csv");默认通常是清空已有内容后重新写。
- file << date;可以直接使用<<写入。
往csv文件里输入','便于后续内容的读取。
- 
auto now = chrono::system_clock::now();
 - 目的：获取电脑当前的本地时间，并把它按照 小时:分钟:秒 的格式写入 sale.csv。
 - 拆解：system_clock可以理解成：系统时钟。也就是电脑当前的时间。::now()意思：获取现在这一刻。
- 
time_t currentTime = chrono::system_clock::to_time_t(now);
 - 目的：把时间点转换成 time_t。
 刚才得到的：now，是 C++ chrono 体系中的一个“时间点”。但是：localtime()这种传统 C/C++ 时间函数并不能直接读取。所以把它转换成：time_t
 - to_time_t(now)可以理解成：把 now 转换成 time_t。
 - 含义（理解）：把刚才获得的当前时间点转换成传统的 time_t 时间格式，并保存到 currentTime。
- 
file << "," << put_time(localtime(&currentTime), "%H:%M:%S") << ",";
 - localtime(&currentTime)//把 currentTime 的地址传给 localtime。（&为取址符）
 - localtime()可简单理解为:把 currentTime 转成本地时间结构。（这个“时间信息”里面会包含：年月日时分秒...）
 - put_time(..., "%H:%M:%S")的作用是：按照指定格式，把时间格式化成字符串一样的输出内容。
 - %H:%M:%S 是时间格式：
 %H→小时
 %M→分钟
 %S→秒
 中间的：`:`就是普通的冒号。
 - file << ...：把内容写进 sale.csv。
 - 总结：
① 获取电脑当前时间
        ↓
② 转换成 time_t
        ↓
③ 转成本地时间
        ↓
④ 按 时:分:秒 的格式格式化
        ↓
⑤ 写入 sale.csv

### int GetToday()
通过销售记录输出今天的天数
（如果想要真的只要执行了Day + 1就进入下一天，哪怕没结帐，重启后依然保留天数，可以重新建一个csv文件保存息。）
- 逻辑：不断输入销售记录中的天数，将记录中出现的最大天数保存下来，当做最终·算出的天数输出。

### int GetTodayNum(int date)
通过天数和销售记录记录流水号。读取到最大数字后再输出最大值+1。

### void Case3(int& date,int& num)
通过引用直接修改日期和流水号。

### void Case4(const int day)
因为输入中会有空格，所以通过getline读取一排，再统一处理。

### void Case5()
- ofstream file("sale.csv");会清空文件。
- file << "Date,number_of_sales/num,system_time,Receipt Items,total_sales_amount" << endl;填入表头

### bool VIPcheck()
判断是否是会员。

### void Case7()
直接打印销售记录和营业额统计结果。

### void AmountReport(ifstream& file)
通过cnt判断是否为同一天的销售记录，在统计同一天的销售记录的同时，记录最高营业额是多少。

## admin.cpp
### void Case6()
输入密码进入管理员模式

### bool VerifyPassword()
判断密码是否正确（三次机会）。

### void AdminMenu()
进入管理员模式菜单。

### void AdminCase1()

### void AdminCase2()

### bool NumCheck(string input)
- input.empty()判断 input 这个字符串是不是空的。返回一个 bool：若input为空字符串则返回true,若是其他（包含只有空格的情况）会返回false。（空字符串和只有空格不是一回事。）
输入安全检测。
 - 补充：input.size() == 0
在判断字符串是否为空时，效果基本一样。empty() 表达得更直接。
empty() = “里面有没有东西？”
size() = “里面有多少个字符？”
- for(char c : input){
    if(!isdigit(c))
      return false;
  }
  - for(char c : input):把 input 里的每一个字符依次取出来，每次都叫它 c。
  - isdigit() 是 C++ 提供的一个判断字符是不是数字的函数。isdigit(c)意思：判断 c 是不是数字字符 '0' ~ '9'。返回 bool：是数字字符，返回true,如果不是，返回false。
  - ! 是“取反”：把 true 变成 false，把 false 变成 true。
  - 注意：input是string类型，里面的每一个元素是字符char类型，而不是string类型。
  - 总结：该函数逐一检测字符串的每一位是不是数字字符。（该函数逐一检测字符串的每一位是不是数字字符。通过检测后，对于正常范围内的纯数字字符串，可以进一步使用 stoi() 将其转换为 int。）

### void RecreateProduct(const vector<Product>& products)
重新填回商品信息。

### bool PriceCheck(string input)
检查一个字符串能不能完整地表示一个数字，包括小数（不包括负数），和NumCheck区分。
- try{
    ...
}你可以暂时把它理解成：尝试执行这一段代码，如果里面发生异常，就交给后面的 catch 处理。因为后面：stod(input, &pos);可能因为输入不是合法数字而产生异常。
- size_t pos;这里定义了一个变量：专门用来记录 stod() 解析到了字符串的什么位置。
- stod(input, &pos);stod：string → double也就是把字符串转换成 double。&pos它的作用是：告诉 stod：把“解析到哪里了”这个位置记录到 pos 中。
 - pos的作用：检查整个字符串是不是都被成功解析成了数字。而不是只检查：字符串开头有没有一部分是数字。（因为如果字符串只有开头是数字也能解析出来）
- catch(...){
    return false;
}这里的：...表示：捕获任意类型的异常。

### void AdminCase3()

### bool DuplicateCheck(const string& add, const string& data_member)
条形码查重（也可用于检测条形码输入是否有效）
for范围循环遍历。

### void Check()
