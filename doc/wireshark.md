# Wireshark
## 目的
* 研究采集使用Wireshark的可能性。
## 思路
### 解析方向
* 目前Wireshark支持哪些协议的解析
* 编译出来的插件接口是否可以用
* 编译出来的插件是否能用mingw调用
### UI方向
* 已知Ui支持qt5.15，读读源码把插件找出来。

## `CMake`+`Visual Studio 2022`构建步骤记录
1. `git clone https://gitlab.com/wireshark/wireshark/tree/master`
1. `call qtenv2msvc.bat` : 配置好`Qt5`与`MSVC`环境。
   ```bat
   @echo off
   echo Setting up environment for Qt usage...
   set PATH=D:\Qt\5.15.2\msvc2019_64\bin;%PATH%
   call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
   ```
1. 启动`cmake-gui.exe`
   1. 指定源码路径
   1. 指定构建路径
   1. <kbd>Configure</kbd>，<kbd>Generate</kbd>，<kbd>Open Project</kbd>。
   * 过程中遇到的错误
     * 未指定`WIRESHARK_BASE_DIR`环境变量。
       设置环境变量，指定Wireshark依赖库路径，注意：**路径不能在源码路径中**。
       `WIRESHARK_BASE_DIR`:`d:/wireshark_base_dir`
     * 安装`flex`和`bison`工具。
       从[github](https://github.com/lexxmark/winflexbison/releases)上下载，解压，添加到PATH中。
     * 未找到`Qt6`
       关闭`USE_qt6`选项。
   * 还可修改`CMAKE_INSTALL_PREFIX`项，指定安装路径。
1. 右键`解决方案`，`生成解决方案`


