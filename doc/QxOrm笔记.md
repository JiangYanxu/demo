# 笔记
## 学到了什么？
### cmake
```bash
# MinGW Debug Build
cmake -D_QX_STATIC_BUILD=ON -D_QX_UNITY_BUILD=ON -DCMAKE_BUILD_TYPE=Debug -S . -B build_mingw -G "MinGW Makefiles"
cmake --build build_mingw --config Debug -j 22
cmake --install build_mingw --prefix "../QxOrm_1_5_0" --config Debug
# MinGW Release Build
cmake -D_QX_STATIC_BUILD=ON -D_QX_UNITY_BUILD=ON -DCMAKE_BUILD_TYPE=Release -S . -B build_mingw -G "MinGW Makefiles"
cmake --build build_mingw --config Release -j 22
cmake --install build_mingw --prefix "../QxOrm_1_5_0" --config Release
# MSVC Debug Build
cmake -D_QX_STATIC_BUILD=ON -D_QX_UNITY_BUILD=ON -DCMAKE_BUILD_TYPE=Debug -S . -B build_msvc -G "Visual Studio 17 2022"
cmake --build build_msvc --config Debug -j 22
cmake --install build_msvc --prefix "../QxOrm_1_5_0" --config Debug
# GCC Debug Build
cmake -D_QX_STATIC_BUILD=ON -D_QX_UNITY_BUILD=ON -DCMAKE_BUILD_TYPE=Debug -S . -B build
cmake --build build --config Debug -j 22
cmake --install build --prefix "../QxOrm_1_5_0" --config Debug
```
### 天坑

### 宏
```cpp
// exprot.hpp
#ifndef EXPORT_HPP
#define EXPORT_HPP

#include <QxOrm.h>
#ifdef BUILD_MY_DEMO
#define QX_MY_DEMO_EXPORT QX_DLL_EXPORT_HELPER
#define QX_REGISTER_HPP_MY_DEMO  QX_REGISTER_HPP_EXPORT_DLL
#define QX_REGISTER_CPP_MY_DEMO  QX_REGISTER_CPP_EXPORT_DLL
#else
#define QX_MY_DEMO_EXPORT QX_DLL_IMPORT_HELPER
#define QX_REGISTER_HPP_MY_DEMO  QX_REGISTER_HPP_IMPORT_DLL
#define QX_REGISTER_CPP_MY_DEMO  QX_REGISTER_CPP_IMPORT_DLL
#endif

#endif // EXPORT_HPP
```
#### 说明
* 文档说要通过`QX_REGISTER_HPP`与`QX_REGISTER_CPP`宏来注册, 也好用.
  上面`export.hpp`内容是参考官方例子写出来的, 贴在这里目的是做个记录.
### 修改主键默认类型, 默认为`long`
```cpp
QX_REGISTER_PRIMARY_KEY(Person, uint64_t)
QX_REGISTER_HPP_MY_DEMO(Person, qx::trait::no_base_class_defined, 0)
```
* `QX_REGISTER_PRIMARY_KEY`必须在`QX_REGISTER_HPP_MY_DEMO`前面.
### 联合主键(跳过)
### 私有声明友元(跳过)
### 