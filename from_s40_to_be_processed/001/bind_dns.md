# 简单的阅读笔记

## 进度相关
### 书名《DNS与BIND》第五版
书在百度网盘上有

## 干货
### 命令总结
|命令|说明|
|:-|:-|
|`nslookup www.baidu.com. 114.114.114.114`|向IP上的名称服务器查询域名的IP地址|
|`nslookup 8.8.8.8`|查询8.8.8.8.in-addr.arpa对应的域名|
|`named-checkconf`|测试`/etc/bind/named.conf`正确性|
|`named-checkzone jianghome.com db.jianghome.com`|测试`db.jianghome.com`正确性|
|`journalctl -u named -f`|查看日志|
|`sudo rndc reload`|重新加载配置文件|
### 配置文件
|位置|说明|
|:-|:-|
|/etc/bind/named.conf|bind9配置文件|
|/etc/bind/db.*|资源记录文件|
### DNS记录类型
|记录类型|说明|
|:-:|:-|
|SOA|指明该区域的权威，他是负责人！|
|NS|该区域的名称服务器，找他要！|
|A|名称到地址的映射，这是最终答案|
|PTR|地址到名称的映射，这是反向的最终答案|
|CNAME|规范名称，这是真名！白痴！|


## 1. 背景
* DNS：domain name system域名系统，解决域名到IP的映射与反映射问题
* BIND：Berkeley Internet Name Domain是一个域名系统
## 2. DNS的运行机制
* DNS命名空间结构：树形，深度最多127层
* 标签：每个节点有一个最长63字符的标签，根标签为空
* 域名：节点的名称叫域名，从节点开始，标签用`.`分隔。节点的索引。
  * `a.b.com.`叫绝对域名（以`.`结尾即包含根节点）
* 域：是个子树
* 资源记录：域名对应的资源，比如email、www等
* 名称服务器nameserver：存储命名空间信息的程序
* 区域zone：名称服务器拥有的命名空间中某一部分信息
  * 区域与域不一定相同，名称服务器对a.com,b.com两个域有权威
* 权威authority：名称服务器被授权后对区域内的信息具有权威
* 授权：将域的一部分授权出去，分派给其他名称服务器管理
* 解析器resolver：一个工具/函数/模块，负责：发起查询名称、解释响应信息、返回信息给发起查询的程序
* (名称)解析name resolution
  * root名称服务器：包含一级域名的IP
  * 查询方式：递归、迭代
    * 递归：你给我最终答案
    * 迭代：你给我你所知道的最优答案
    * 解析器以递归方式向A名称服务器发起查询<br/>
      A以迭代查root得到下一个名称服务器B<br/>
      A以迭代查B，循环直至得到最终答案<br/>
      A把最终答案给解释器<br/>
* in-addr.arpa域：处理IP到name的映射
  * in-addr.arpa域最多可有256个子域，每个子域可以有256个子域，共四层，即ipv4地址
  * IP127.0.0.1对应域名1.0.0.127.in-addr.arpa
* 缓存
  * 否定缓存，name不存在的信息也能被缓存
  * 生存时间TTL time to live：缓存的过期时间
## 从哪里开始呢
* 怎样获取一个域，暂时不重要
## 建立BIND


