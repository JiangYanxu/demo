# 简单的笔记

## 进度相关
* [nginx官网](https://nginx.org/)
* [nginx文档](https://nginx.org/en/docs/)
### 进度记录
|网址|笔记|进度|说明|
|:-|:-|:-|:-|
|[Beginner’s Guide](https://nginx.org/en/docs/beginners_guide.html)|[初学者指南](#初学者指南)|40%|已看完`Serving Static Content`<br/>后面还有俩暂时不需要

## 干货
### 命令总结
|命令|说明|
|:-|:-|
|`nginx -s stop`|紧急停止|
|`nginx -s quit`|平滑关闭，应由启动nginx的用户执行|
|`nginx -s reload`|重新加载配置文件|
|`nginx -s reopen`|重新打开日志文件|
|`journalctl -u nginx -f`|查看日志|
|`sudo systemctl start nginx`|启动|
### 配置命令说明
* http
  * server
    * location [ = | ~ | ~* | ^~ ] uri { ... }<br/>
      location @name { ... }<br/>
      从长度最长的前缀开始匹配，`'/'`是长度最短的前缀，所有都未匹配到时匹配`'/'`
      * root path;<br/>
        http://ip/uri/a/b.html -> path/uri/a/b.html
      * alias path;<br/>
        http://ip/uri/a/b.html -> path/a/b.html


## 初学者指南
* 主进程+多个工作进程的模式
* 配置文件nginx.conf：`/usr/local/nginx/conf`、`/etc/nginx`、`/usr/local/etc/nginx`
* 日志access.log/error.log：`/usr/local/nginx/logs`、`/var/log/nginx`
### 配置文件结构
* nginx由modules组成
  * 包含简单命令（name parameters;）与块命令（name {}）
  * 块命令可包含简单命令
  * 任何块命令之外的命令存在于main上下文中
  * 一行中`#`后面是注释
* 上下文结构：
  * main
    * events
    * http
      * server
        * location
### 静态内容
```ini
http {
	server {
    listen 10.1.0.100:80;
    include mime.types;
    default_type application/octet-stream;
		location /bind9-doc/ {
			alias /usr/share/doc/bind9-doc/arm/;
		}
		location /bind9-doc/_static/ {
			alias /usr/share/doc/bind9-doc/arm/_static/_static/;
		}
	}
}
```