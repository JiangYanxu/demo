# 再次重装！

## 重装过程记录
### 已看过
#### D盘
|路径|进度|
|:-|:-|
|Program Files|1|
|Program Files (x86)|1|
|KICAD|把用户文档文件夹中内容放进去了|
|`D:\Project\Qt`,`D:\Project\Workspace`||
|`TOM/普中HC6800-ES V2.0开发板资料/嵌入式编程入门系列`||
#### E盘
|路径|进度|
|:-|:-|
|公司资料||

### 重装过程中注意
* home文件夹名别叫11249

### 重装完毕后代办
* 修改软件默认安装目录
* Hyper-V
* qt - 日志

## 代办
* 电梯卡扣破解程序
* gcc开源代码
* 树莓派？


***
### 技术相关
* MASM
* powerdesigner
* INCHRON Tool-Suite

### 解压即用
* frp - 内网穿透
  ```ini
  [common]
  server_addr = 10.1.0.10
  server_port = 24680
  token = 940798

  [stcp-visitor]
  type = stcp
  role = visitor
  server_name = HXRemoteDesktop
  sk = jiangzhendong
  bind_addr = 127.0.0.1
  bind_port = 24681
  ```
  ```powershell
  $proc_frpc = Start-Process D:\Unzip_Program_Files\frp_0.38.0_windows_amd64\frpc.exe `
      -PassThru -ArgumentList "-c D:\Unzip_Program_Files\frp_0.38.0_windows_amd64\frpc_HXRemoteDesktop.ini"
  Start-Sleep -s 1
  $proc_mstsc = Start-Process mstsc.exe `
    -PassThru -ArgumentList "-c D:\Unzip_Program_Files\frp_0.38.0_windows_amd64\frpc_HXRemoteDesktop.ini"
  $proc_mstsc.WaitForExit()
  $proc_frpc.Kill()
  ```
  ```powershell
  START powershell -WindowStyle Hidden "D:\Unzip_Program_Files\frp_0.38.0_windows_amd64\HXRemoteDesktop.ps1"
  ```