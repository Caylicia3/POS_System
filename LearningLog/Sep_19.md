# 学习日志 - 2026年9月19日

## 今日学习内容
- 完成调试

## 遇到的坑 & 解决方案
- **坑**：void AmountReport(std::ifstream file);没写&，出现编译错误（.h文件里没写命名空间）
  - **解决**：void AmountReport(std::ifstream& file);
  为什么 .cpp 里能用，.h 里却报错？
因为你可能在 sale.cpp 里写了：using namespace std;
于是：ifstream可以直接写。
但 sale.h 是一个独立的头文件，不能假设包含它的 .cpp 一定提前写了：using namespace std;
而且一般也不建议在头文件里写：using namespace std;
所以头文件里最好明确写：std::ifstream
- **坑**：bool VIPcheck()
{
    ...
}
某条执行路径走到了函数末尾，却没有 return。
bool VIPcheck(){
    cout << "Are you a member of this store? Enter 1 if yes, 0 if no." << endl;
    string VIP;
    while(cin >> VIP){
        if(VIP == "1"){
            Redirect();
            return true;
        }
        else if(VIP == "0"){
            Redirect();
            return false;
        }
        else{
            cout << "Error 32 : Invalid Input." << endl;
        }
    }
}
为什么看似怎么走都有返回值但是会报错？
  - **解决**：存在无法进入循环的情况
cin >> VIP
    ↓
输入失败
    ↓
while 条件为 false
    ↓
跳出 while
    ↓
函数结束
所以最后要补上return值

解决方法二：
此函数目的其实是不断要求用户输入，直到输入 1 或 0。那么从这个函数的设计意图来看，while(true) 更贴近逻辑：
while(true){
    cin >> VIP;
    if(VIP == "1"){
        Redirect();
        return true;
    }
    else if(VIP == "0"){
        Redirect();
        return false;
    }
    else{
        cout << "Error 32 : Invalid Input." << endl;
    }
}
这时编译器也不会说“可能走到函数末尾”，因为两个合法分支最终都会 return，而 while(true) 本身没有正常结束路径。
不过这里还有一个区别：while(cin >> VIP) 会在输入流失败时跳出；while(true) 在输入流失败后还需要考虑如何处理 cin 的失败状态。
- **坑**：sale.cpp里忘加sale.h头文件
  - **解决**：
- **坑**：不要手动去删除sale.csv文件的记录，会导致后面checkout追加时出现多的空行，导致查看销售记录和销售报告时出错。（如果一定要手动删，请确保删除后光标在csv文件里提行！因为追加时会在原文件后直接开始）开始运行前确定sale.csv文件是空的（初始状态）（不然很容易读取出错）
  - **解决**：可以加入一个空行检测
  if(line.empty()){
        continue;
    }

- **坑**：git推送到远端仓库的commit和tag是分开的，建议先推送commit后再推送tag
  - **解决**：
  git commit -m "release: v0.1.5"
  git tag -a v0.1.5 -m "First stable release"
  git push
  git push origin --tags  或   git push origin v0.1.5
- **坑**：
  - **解决**：
- **坑**：
  - **解决**：
- **坑**：
  - **解决**：
- **坑**：
  - **解决**：
## 今日学到的命令
- git ls-remote --tags origin查看远端仓库所有tag
- 

## 待办
- 
- 
- 
- 