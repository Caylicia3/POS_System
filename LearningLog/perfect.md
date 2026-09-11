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