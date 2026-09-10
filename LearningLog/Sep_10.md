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
& 在声明引用时的核心作用，就是给一个已经存在的变量起一个别名（Alias）
cpp
int a = 10;
int& r = a;   // r 是 a 的别名
r = 20;       // 等价于 a = 20
r 不是新变量，它和 a 是同一个东西。
对 r 的操作，就是对 a 的操作。
引用必须在定义时绑定到某个对象，之后不能换
假设你有一块内存，里面住着变量 a。你写 int& b = a;，这在 C++ 语法层面的意思就是：“给 a 住的这块内存，再挂一个门牌叫 b”。
a 和 b 在内存里完全重合，地址一模一样。
你不是把 a 的值复制给 b，你就是给 a 起了个外号。
以后你改 b，就是改 a。

对比记忆：
int& b = a; —— 给 a 起个别名 b（两个人共用一个身体）。
int* p = &a; —— 找 a 要一张名片（地址），交给指针 p。
- 为什么用 const std::string& 而不是 std::string？
写法	是否拷贝	能否修改原串	能否接临时值
std::string line	拷贝一份	改的是副本	可以
std::string& line	不拷贝	可以改原串	不可以
const std::string& line	不拷贝	不能改原串	可以
所以 const std::string& 是只读、高效、安全的参数写法。
- 使用for循环遍历vector动态数组
- 学习用 <iomanip> 头文件里的流操纵符（I/O Manipulators）控制输出
- 在 C++ 中，void 函数直接用 return; 就可以提前结束，不需要返回值：
## 遇到的坑 & 解决方案
- **坑**：注释里误写了‘\’导致程序无法正常运行
  - **解决**：
- **坑**:同时写几个函数，把自己绕晕了
  - **解决**：制作思维导图/流程图
    ShowMenu函数
        |
    Switch判断功能
        |__0->退出菜单
        |__1->商品信息查询
        |__2->结账功能（001、002、003查询商品信息，price,drop,checkout功能），001……需遍历vector动态数组查询是否位于序列中
        |__3->
- **坑**：C++ 标准规定，switch 的条件和 case 标签必须是整型（int, char, enum 等）或者能隐式转换为整型的类型。std::string 是一个类，不能作为 switch 的条件。
  - **解决**：用if语句替代。
- **坑**:不知道怎么结束调用的函数运行
  - **解决**：方法一：将返回值改为bool,在调用部分使用if判断是否break
  while(cin >> input2){
                if(!ShowProductInfo(input2)){
                    break;
                }
            }
            break;
- **坑**:如何返回菜单界面
  - **解决**：
  🚫 思路一：直接跳转到第9行（使用 goto 或类似跳转）
不建议。
C++ 极其不推荐使用 goto 跳回代码前面。原因如下：

变量作用域灾难：你第10行声明了 vector<Product> products = CreateProduct(...)。如果你用 goto 往回跳，这个 vector 会不断被重新构造，容易引发内存泄漏或编译错误（“跳过了变量初始化”）。

破坏代码结构：goto 会让代码变成“面条代码”，极难维护。

🚫 思路二：把读取部分封装成函数，结束后重新调用 ShowMenu()
可行，但有严重风险（内存爆栈 + 重复加载文件）。

栈溢出（Stack Overflow）：如果你在 ShowMenu() 内部或 main() 内部再次调用 main() 或 ShowMenu()，函数调用栈会越来越深。用户操作几百次，程序就会直接崩溃（Segmentation fault）。

性能浪费：你在第10行读取了 product.csv，每次重新调用 ShowMenu() 都会重新读取一遍文件，完全没必要。

✅ 标准解决方案：主循环 + 子函数封装
不要想着“跳回去”，而是把菜单和输入放进一个死循环（while(true)）或者do while循环里。只要不退出，代码执行完一个功能后，自然就会回到循环开头，重新打印菜单。
- **坑**:在范围 for 循环中，如果直接写 Product product，每次迭代都会创建一个临时副本。你在这里给 quantity++，只改了副本，原 products 容器里的商品数量保持原样。for(Product product : products)
  - **解决**：正确写法：使用引用（Product&）for(Product& product : products)
- **坑**:-<id>不能直接在barcode前加'-'，因为barcode类型是string
  - **解决**：处理input2:input2[0] == '-'：检查字符串第一个字符是不是减号
  input2.substr(1)：这是 C++ 字符串的截取函数。substr(1) 的意思是从下标 1 开始截取到最后。这样 -001 就变成了 001。头文件是<string>

- **坑**:边界（数量>0）
  - **解决**：数量边界拦截：代码里加了一个 if (product.quantity > 0) 判断。因为数量不可能减成负数（用户不能“退货”退一个根本没买的东西），这是 POS 系统的必备防御。
- **坑**:弄错函数原则声明、函数定义 和 函数使用的格式
  - **解决**：函数使用时不需要写输入参数的类型
- **坑**:把VS code里终端的命令行和git bash命令行弄混
  - **解决**：VS code编译：（所有cpp文件）g++ *.cpp -o main   运行.exe:.\main.exe
  git bash中 git add .(在已关联到remote eg.origin仓库时使用)
- **坑**:终端路径有问题
  - **解决**：使用cd等方式切换到正常路径
- **坑**:cin>>int(类型)，如果输入非int类型会出bug
  - **解决**：输入防护——eg.
      if (!(cin >> input1)) {//尝试把用户输入读进 input1，如果失败，就进入 if。
        cout << "Invalid input. Please enter a number." << endl;
        cin.clear();              // 清除 cin 的错误状态
        cin.ignore(10000, '\n');  // 丢掉这一行错误输入,此行代码的意思是：从输入缓冲区里丢弃（忽略）最多 10000 个字符，或者直到遇到换行符 \n 为止（换行符也会被丢弃）。
        continue;
      }
      cin.clear() 其实可以带参数，默认不带参数时相当于 cin.clear(std::ios::goodbit)，即恢复所有正常状态。
- **坑**:极其关键的误区：clear() 不是清空缓冲区！cin.clear() 只改状态。导致出错的那个字母 a，依然还在输入缓冲区里。如果只调用 clear()，下一次 cin >> 读到的还是那个字母 a，又会立刻崩溃。
  - **解决**：这就是为什么，它必须和 cin.ignore() 配合使用（“黄金搭档”）：
- **坑**：怎么检验输入的是不是空格
  - **解决**:不能用 cin >> ch 来判断空格，因为 cin >> ch 默认会跳过空格、制表符、换行等空白字符。
但可以用 cin.get(ch) 读入包括空格在内的字符。
- **坑**：cin.get() 只能接收 char 或 char*（字符数组），它不认识 std::string，所以不能用它来读取string类型
  - **解决**:方案一：如果只想读一个字符改成用 char 类型接收
             方案二：如果想读取一整行（包含空格）应该用 getline：
             eg.    string input3;
                    getline(cin, input3); 
- **坑**：git log指令终端分页器（less）的显示造成“重复”干扰。git log 默认进 less，会重绘屏幕 → 复制出来看着像重复
  - **解决**:简单说：git log 是“完整档案”，git log --oneline 是“精简目录”。
  常用参数组合
命令	作用
git log	完整信息，进分页器
git log --oneline	一行一个，简洁
git log --oneline -5	只看最近 5 条
git log --oneline --graph	一行一个 + 分支树状图
git log --oneline --all	显示所有分支的提交
git log -p	显示每个提交的具体代码改动
git log --stat	显示每个提交改了哪些文件、增删多少行
git log --author="Caylicia"	只看某个作者的提交
## 今日学到的命令
- `git push`：
- `git remote -v`：远程仓库

## 待办
- 学习制作项目（ongoing）
- 学习类与对象
- 学习用CSV 格式记录