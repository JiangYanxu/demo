# 记录与总结

## 目标
|代号|进度|目标|说明|
|:-:|:-|:-|:-|
|dns|99%|提供内网服务的DNS|买了dns解析服务。|
|nginx|100%|web服务+反向代理|要不要放在docker里？|
|samba|0%|共享文件夹|优先|
|docker|80%|容器虚拟化|iperf3 vpn|
|nextcloud|0%|私有云||
|gitlab|0%|玩玩看|https://about.gitlab.com/install/#ubuntu<br>最好用docker玩。nginx做反向代理|
|email|0%|邮件服务器|优先|

### docker容器代办
|目标|说明|
|:-:|:-|
|iperf3|测速|
|v2ray-core|翻墙代理|
|百度网盘|离线下载|
|禅道|玩玩看|
|nextcloud|私有云|
|系统资源监控|jasonrivers/nagios|
|流媒体|NASTool、jellyfin|
## 待看
### 软件
1. dns相关
   * bind9utils
   * bind9-doc
   * dnsutils
2. man命令
   * 怎么查
   * 怎么写
3. conda
4. dpkg
5. webdev
6. ps命令
7. SysVinit和Systemd
8. journald、syslog、json-file、splunk、gelf、daemon
### 知识点
1. 证书ssl相关(自签)
2. linux软件怎么打包
3. ftp相关的传输协议
4. NIS/LDAP/DNS分别解决什么问题的？
### 待完成的模糊目标
1. web能更新这个文档 -- 手机随时随地更新 -- wiki?nextcloud?
   * BookStack、MinDoc、Gitbook、看云
   * GitBook只剩下在线版本了，GitBook+GitHub不好用。
   
2. docker [web管理工具](https://cloud.tencent.com/developer/article/1647274)
3. 云备份移动设备的照片或数据 -- nextcloud?
4. 流媒体服务 -- 与电视联动
5. 系统资源监控https://www.zentao.net/page/80231.html
   https://blog.csdn.net/xingyunguanjia/article/details/124426281
   https://www.bilibili.com/read/cv9739033/
6. docker有趣项目：onlyoffice、outline、https://space.bilibili.com/36074208/article
7. iscsi

## 干货
### 命令
|命令|说明|
|:-|:-|
|`apt policy xxx`|查看xxx是否安装|
|`timedatectl status`|查看系统时间|
|`timedatectl set-timezone Asia/Shanghai`|设置上海时区|
|`journalctl -u nginx`|查看nginx日志|
|`sudo systemctl status\|disable\|enable\|start\|stop nginx`|控制nginx服务|
|`nslookup www.baidu.com. 114.114.114.114`|向IP上的名称服务器查询域名的IP地址|
|`dpkg -L bind9`|查看bind9的详细安装路径|
|`netplan try`|测试`/etc/netplan/*.yaml`正确性，正确则应用|
|`curl cip.cc`|查看本机公网ip|
|`ps -elf`|查看正在运行的进程|
|`scp -r sour_folder dest_folder`|拷贝文件夹|
### 配置文件
|位置|说明|
|:-|:-|
|`/etc/resolv.con`f|系统默认dns服务器|
|`/etc/netplan/`|网络配置文件|


## 操作记录
1. 笔记本合盖休眠
   ```bash
   sudo vim /etc/systemd/logind.conf
   # "#HandleLidSwitch=suspend"->"HandleLidSwitch=ignore"
   sudo service systemd-logind restart
   ```
2. 禁用终端欢迎信息中的广告
   ```bash
   sudo vim /etc/default/motd-news
   # "ENABLED=1"->"ENABLED=0"
   sudo systemctl restart motd-news
   ```
3. 磁盘相关
   ```bash
   lsblk -p
   parted /dev/sdb
   # p # 查看硬盘信息
   # mklabel gpt # 建立gpt分区表
   # mkpart primary 0% 100% # 创建主分区
   lsblk -p
   pvcreate /dev/sdb1 # 分区创建PV
   vgcreate docker-data-vg /dev/sdb1 # 由PV创建VG
   lvcreate -n docker-data-lv0 -l +100%FREE docker-data-vg # 创建LV
   mkfs.ext4 /dev/docker-data-vg/docker-data-lv0 # 格式化
   blkid /dev/docker-data-vg/docker-data-lv0 # 查看信息
   vim /etc/fstab # 自动挂载
   mount -a # 即刻生效
   ```
   * 概念详见[disk.md](./disk.md)

## 软件或服务

### [`bind9`内网域名解析服务](https://blog.csdn.net/fenghaofhyy/article/details/127306193)
```bash
sudo apt install bind9 bind9-doc # 安装
named -v # 测试
cd /etc/bind
sudo vim named.conf.options # 修改监听的IP和端口
sudo cp named.conf.local named.conf.local_old
sudo vim name.conf.local # 添加域
named-checkconf # 检查name.conf正确性
sudo touch db.jianghome.com
sudo vim db.jianghome.com # 添加资源记录
named-checkzone jianghome.com db.jianghome.com # 测试db.jianghome.com正确性
sudo systemctl restart bind9 # 重启服务
journalctl -u named # 查看日志
#sudo rndc reload # 重新加载配置
sudo netstat -ano | grep 53 # 查看端口状态
nslookup jianghome.com 127.0.0.1 # 测试

#sudo vim /etc/resolv.conf # 修改系统默认dns服务器
sudo vim /etc/netplan/00-installer-config.yaml # 修改默认的nameservers为本机
sudo netplan apply
```
**代办：/usr/share/dns/root.hints需要定期通过anonymous@ftp.rs.internic.net/domain/db.cache更新"**

### [`nginx` HTTP服务器]()
```bash
sudo apt install nginx nginx-doc # 安装
nginx -v # 测试
cd /usr/share/nginx/html # 配置
sudo cp index.html index.html.old
sudo vim index.html
cd /etc/nginx
sudo cp nginx.conf nginx.conf.old
sudo vim nginx.conf
sudo systemctl status nginx
sudo nginx -s reload
```
配置详见[nginx.md](./nginx.md)

### 多IP地址
```bash
cd /etc/netplan
sudo vim 00-installer-config.yaml
# - 10.1.0.11/24
# - 10.1.0.12/24
netplan try
netplan apply
```

### 修改sshserver监听的ip
```bash
dpkg -l | grep ssh # 查询ssh包名是openssh-server
dpkg -L openssh-server # 发现/usr/share/openssh/sshd_config文件
cat /usr/share/openssh/sshd_config
# 发现包含：
#       Include /etc/ssh/sshd_config.d/*.conf
#       #ListenAddress 0.0.0.0
cd /etc/ssh/sshd_config.d
sudo touch sshd_local.conf
sudo vim sshd_local.conf # 添加"ListenAddress 10.1.0.10"
sudo systemctl restart sshd # 重启服务
```
### [`samba`共享文件系统](https://www.samba.org/samba/docs/man/)
```bash
sudo apt install samba
```
**卡住了 有点复杂 在docker里弄吧 先卸载了**

