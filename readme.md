# 记录
## 目的
*   记录每个demo中的过程或知识点
*   doc文件夹是总结性的文档
## todo
* plantuml 需要补充一个操作记录的文档。
* learn_qxorm_manual 目前是mingw，改成msvc，并且总结一下。或让这个顶层项目适应mingw。
* LearnOpenGL 缺笔记，需要整理。
* 研究完QxOrm再来搞QxEntityEditor。
* 3D打印，OpenSCAD
* 键盘固件：电源模块、蓝牙模块
  * nasm 汇编
* CMake 高级技巧
  * 交叉编译
  * 除了mingw还有什么? `llvm`; `msys2`; `cygwin`
    * 异常实现方式？
* 试试各种库
  * C++ 日志库：`log4qt`; `log4cplus`; `log4cpp`
  * OpenSSL、zlib、boost
* 线性代数 - OpenGL - OpenCV
* gitmind中整理过来、还有其他笔记、幕布、WorkFlowy
* 路由、nas
  * OpenVPN
* 去读[GNU Coding Standards](https://www.gnu.org/prep/standards/)
* 把vscode插件整理整理
* 把chrome插件与网址整理整理




## Flex与Bison的尝试（flex_bison_demo）
### 知识点
*   解析器生成器，用于生成代码（语言）的解析器（代码）。已知有三种：Bison、Yacc、Lemon
*   词法分析器生成器，根据输入的正则表达式规则，生成词法分析器。词法分析器用于将文本分割成词法单元`tokens`。
*   Flex长与解析器生成器配合使用
    *   Flex：处理流，将其分解成一个词法单元
    *   解析器生成器：使用词法单元，基于语法规则构造更高层的结构（如抽象语法树）。
### 操作步骤
1.  安装软件`sudo apt-get install flex bison`