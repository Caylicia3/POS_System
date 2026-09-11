# [项目名称] 维护文档

## 1. 文档信息

| 项目 | 内容 |
|---|---|
| 项目名称 | [项目名称] |
| 文档版本 | v1.0 |
| 维护人 | [姓名/团队] |
| 最后更新 | YYYY-MM-DD |
| 适用分支 | main / master / [分支名] |
| 适用版本 | [版本号] |

---

## 2. 项目概述

简要说明项目用途、主要功能、目标用户。

示例：

> 本项目是一个 POS 收银系统，支持商品管理、销售、退货、销售记录查询、总营业额统计等功能。

---

## 3. 环境要求

| 类别 | 要求 |
|---|---|
| 操作系统 | Windows / Linux / macOS |
| 编译器 | g++ 支持 C++17 |
| 构建工具 | g++ / CMake / Make |
| 编辑器 | VS Code |
| 依赖库 | 无 / [依赖名称] |

编译示例：

```bash
g++ -std=c++17 *.cpp -o POS
```

运行：

```bash
./POS
```

Windows：

```powershell
.\POS.exe
```

---

## 4. 目录结构

```text
project/
├── main.cpp
├── product.h
├── product.cpp
├── sale.h
├── sale.cpp
├── utils.h
├── utils.cpp
├── product.csv
├── sales.csv
├── MAINTENANCE.md
└── README.md
```

说明：

| 文件/目录 | 说明 |
|---|---|
| main.cpp | 程序入口，主菜单循环 |
| product.h / product.cpp | 商品模块 |
| sale.h / sale.cpp | 销售模块 |
| utils.h / utils.cpp | 通用工具函数 |
| product.csv | 商品数据 |
| sales.csv | 销售记录 |

---

## 5. 功能模块

| 模块 | 文件 | 主要功能 | 主要函数 |
|---|---|---|---|
| 商品管理 | product.cpp | 创建、查询、修改商品 | CreateProduct, ShowProductInfo |
| 销售管理 | sale.cpp | 销售、退货、记录查询 | Case1, Case2, Case3 |
| 工具模块 | utils.cpp | 日期、清屏、输入处理 | GetToday, clearScreen |
| 主菜单 | main.cpp | 用户交互入口 | main |

---

## 6. 数据结构与文件格式

### 6.1 Product

```cpp
struct Product {
    std::string barcode;
    std::string name;
    double price;
    int stock;
};
```

### 6.2 SalesRecord

```cpp
struct SalesRecord {
    std::string date;
    std::string barcode;
    std::string name;
    int quantity;
    double total;
};
```

### 6.3 product.csv

格式：

```csv
barcode,name,price,stock
1001,Apple,3.5,100
1002,Banana,2.0,150
```

### 6.4 sales.csv

格式：

```csv
date,barcode,name,quantity,total
2024-01-01,1001,Apple,2,7.0
```

---

## 7. 关键函数说明

| 函数名 | 所在文件 | 参数 | 返回值 | 说明 |
|---|---|---|---|---|
| CreateProduct | product.cpp | csv 文件路径 | vector<Product> | 从 CSV 读取商品 |
| Judge | product.cpp | line1, line2, line3, barcode, valid | bool | 判断商品信息是否匹配 |
| GetToday | utils.cpp | 无 | string | 获取今天日期 |
| GetTodayNum | sale.cpp | date | int | 获取当日销售笔数 |
| Case3 | sale.cpp | date, num | void | 查看当日销售记录及总营业额 |

---

## 8. 编译与运行

### 8.1 编译

```bash
g++ -std=c++17 *.cpp -o POS
```

### 8.2 运行

Windows：

```powershell
.\POS.exe
```

Linux / macOS：

```bash
./POS
```

### 8.3 常见编译问题

| 问题 | 原因 | 解决 |
|---|---|---|
| 'string' was not declared | 缺少 `#include <string>` | 在头文件顶部添加 |
| 'xxx' was not declared in this scope | 函数未声明 | 在 .h 中声明，或在 .cpp 顶部包含对应头文件 |
| Permission denied | exe 正在运行 | 关闭程序后重新编译 |

---

## 9. 常见问题 FAQ

### Q1: 输入 `001` 为什么进入 `case 1`？

A: `cin >> int` 会把 `001` 解析为整数 `1`，前导零被忽略。

### Q2: 如何读取包含空格的整行输入？

A: 使用：

```cpp
getline(std::cin, line);
```

如果前面用过 `cin >>`，需要先：

```cpp
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
```

### Q3: 如何去掉字符串前 6 个字符？

A:

```cpp
s.erase(0, 6);
```

需要包含：

```cpp
#include <string>
```

---

## 10. 维护记录 / 变更日志

| 日期 | 版本 | 修改人 | 修改内容 |
|---|---|---|---|
| YYYY-MM-DD | v1.0 | [姓名] | 初始版本 |
| YYYY-MM-DD | v1.1 | [姓名] | 修复商品查询越界问题 |
| YYYY-MM-DD | v1.2 | [姓名] | 增加当日销售记录查询 |

---

## 11. 待办事项 TODO

- [ ] 增加销售记录按日期查询
- [ ] 增加总营业额统计
- [ ] 优化输入错误处理
- [ ] 增加单元测试
- [ ] 补充 CSV 异常处理

---

## 12. 联系方式

| 角色 | 姓名 | 邮箱/联系方式 |
|---|---|---|
| 维护人 | [姓名] | [邮箱] |
| 负责人 | [姓名] | [邮箱] |

---

## 13. 附录

### 13.1 术语表

| 术语 | 说明 |
|---|---|
| POS | Point of Sale，销售终端 |
| SKU | 库存单位 |
| CSV | 逗号分隔值文件 |

### 13.2 参考资料

- C++ Reference: https://en.cppreference.com/
- VS Code 官方文档: https://code.visualstudio.com/docs

---

> 本文档用于记录项目维护相关信息。每次修改代码后，请同步更新“维护记录”和“待办事项”。