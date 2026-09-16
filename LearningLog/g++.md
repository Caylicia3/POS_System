- g++ -std=c++17 -Wall -Wextra -g *.cpp -o POS.exe
- g++ main.cpp menu.cpp product.cpp sale.cpp -o POS.exe -static -static-libgcc -static-libstdc++   //release
- git log --oneline --graph --all  //查看提交图
- g++ -std=c++17 *.cpp -o POS.exe -static   //release(Windows系统)
- g++ -std=c++17 *.cpp -o POS -static   //release(Linux系统)
- clang++ -std=c++17 *.cpp -arch x86_64 -arch arm64 -o POS    //release(macOS系统)

- 总结：
# Windows
g++ -std=c++17 *.cpp -o POS.exe -static

# Linux
g++ -std=c++17 *.cpp -o POS -static

# macOS（Intel + Apple Silicon）
clang++ -std=c++17 *.cpp -arch x86_64 -arch arm64 -o POS