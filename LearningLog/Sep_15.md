# 学习日志 - 2026年9月15日
- fix：加入结构体member stock
  - 已修改/检查：product.csv, product.cpp, main.cpp, admin.cpp, menu.cpp, sale.cpp
## 今日学习内容

- 
- 
- 

## 遇到的坑 & 解决方案
- **坑**：加入stock后，CreatProduct函数的赋值部分出问题，Product product{name, barcode, price, stock};
  - **解决**：把结构体中quantity和stock的顺序交换
- **坑**：添加商品/修改价格/更改内存等后没有更新内存中的 products
  - **解决**：每次需要使用product信息时都要用CreateProduct函数重新实时生成。保证数据一致性：CSV 是唯一数据源：
- **坑**：
  - **解决**：
- **坑**：
  - **解决**：
- **坑**：
  - **解决**：
- **坑**：
  - **解决**：
- **坑**：
  - **解决**：
- **坑**：
  - **解决**：
- **坑**：
  - **解决**：
## 今日学到的命令
- 
- 

## 待办
- 重写product.cpp Checkout函数
- 学习类与对象
- 加入结构体成员stock（默认初始值为10）
- 