# CMakeLists手册
## 目的
* 记录在各种场景下我能用到的`CMakeList.txt`的技巧

## 故事
### 算是坑吧
#### vscode远程连接环境变量不生效
我试图在环境变量里添加`J_PC_NAME`环境变量（在`~/.bashrc`文件末尾追加`export J_PC_NAME=xxx`）
用以在CMake项目中区分不同的计算机（环境）
但是我发现重启vscode后，cmake读不到变更。查了一下，是跑在linux上`vscode-server`程序未重启导致的。