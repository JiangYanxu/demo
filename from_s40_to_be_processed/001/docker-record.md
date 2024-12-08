# [Docker](https://www.docker.com/)相关的操作记录

## [安装](https://docs.docker.com/engine/install/ubuntu/)
1. 安装docker apt仓库
   ```bash
   sudo apt-get update
   sudo apt-get install ca-certificates curl gnupg lsb-release
   sudo mkdir -p /etc/apt/keyrings
   curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg
   echo "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
   ```
2. 安装docker引擎
   ```bash
   sudo apt-get install docker-ce docker-ce-cli containerd.io docker-compose-plugin
   sudo docker run hello-world # 测试是否安装成功
   ```
3. [后续工作](https://docs.docker.com/engine/install/linux-postinstall/)
   1. 不用sudo管理docker
      ```bash
      sudo usermod -aG docker $USER
      newgrp docker # 更新组信息
      docker version # 测试，Server:无错误信息
      ```
   2. 日志增长，可能使得磁盘空间满 - 暂时不会有问题，有空再配置
4. Docker使用详见[docker.md](./docker.md)
***
## 容器创建命令记录
### [portainer.io](https://www.portainer.io/)Docker的Web端
* 创建命令
  ```bash
  sudo docker run -d -p 10.1.0.10:443:9443 \
     --name=portainer --restart=always \
     -v /var/run/docker.sock:/var/run/docker.sock \
     -v /mnt/docker-data/container_data/portainer_data:/data \
     portainer/portainer-ee:latest
  ```
* 单机跑所以不需要8000
### [Aria2 Pro](https://hub.docker.com/r/p3terx/aria2-pro)下载器与web端
```bash
docker run -d \
    --name aria2-pro \
    --log-opt max-size=1m \
    -e PUID=$UID \
    -e PGID=$GID \
    -e UMASK_SET=022 \
    -e RPC_SECRET=940798 \
    -e RPC_PORT=6800 \
    -p 10.1.0.10:6800:6800 \
    -e LISTEN_PORT=6888 \
    -p 10.1.0.10:6888:6888 \
    -p 10.1.0.10:6888:6888/udp \
    -v $PWD/aria2-config:/config \
    -v $PWD/aria2-downloads:/downloads \
    p3terx/aria2-pro

docker run -d \
    --name ariang \
    --log-opt max-size=1m \
    -p 10.1.0.10:6880:6880 \
    p3terx/ariang
```
* 有迅雷，他下课了！
### [xunlei](https://hub.docker.com/r/cnk3x/xunlei)
* [迅雷NAS](https://nas.xunlei.com/install)
```bash
docker run -d \
    --name=xunlei \
    -p 10.1.0.10:2345:2345 \
    -v /mnt/docker-data/container_data/xunlei/downloads:/xunlei/downloads \
    -v /mnt/docker-data/container_data/xunlei/data:/xunlei/data \
    --privileged \
    cnk3x/xunlei:latest
# 内测邀请码：迅雷牛通
```
### [gitlab](https://hub.docker.com/r/gitlab/gitlab-ce) [doc](https://docs.gitlab.com/ee/install/docker.html)
```bash
export GITLAB_HOME=/mnt/docker-data/container_data/gitlab && \
echo $GITLAB_HOME && \
sudo docker run --detach \
  --hostname gitlab.jianghome.com \
  --publish 10.1.0.13:443:443 --publish 10.1.0.13:80:80 \
  --publish 10.1.0.13:22:22 \
  --name gitlab \
  --restart always \
  --volume $GITLAB_HOME/config:/etc/gitlab \
  --volume $GITLAB_HOME/logs:/var/log/gitlab \
  --volume $GITLAB_HOME/data:/var/opt/gitlab \
  --shm-size 256m \
  gitlab/gitlab-ce
```
### [nagios](https://hub.docker.com/r/jasonrivers/nagios)
```bash
docker run \
  --name nagios4 \
  -v $PWD/nagios/etc:/opt/nagios/etc \
  -v $PWD/nagios/var:/opt/nagios/var \
  -v $PWD/Custom-Nagios-Plugins:/opt/Custom-Nagios-Plugins \
  -v $PWD/nagiosgraph/var:/opt/nagiosgraph/var \
  -v $PWD/nagiosgraph/etc:/opt/nagiosgraph/etc \
  -p 10.1.0.10:8080:80 \
  --privileged \
  jasonrivers/nagios:latest
# 不行得自己做应用容器化
```
### [frps内网穿透服务器](https://hub.docker.com/r/snowdreamtech/frps)
```bash
docker run -d \
  --restart=always \
  --name frps_c80_in81 \
  -p 10.1.0.10:24680:24680 \
  -p 10.1.0.10:24681:24681 \
  -v /mnt/docker-data/container_data/frps/frps.ini:/etc/frp/frps.ini \
  snowdreamtech/frps
# --network host \ 直接使用主机
```
### [frpc内网穿透客户端](https://hub.docker.com/r/snowdreamtech/frpc)
```bash
docker run -d \
  --restart=always \
  --name frps_s80_sin81 \
  -p 10.1.0.10:24680:24680 \
  -p 10.1.0.10:24681:24681 \
  -v /mnt/docker-data/container_data/frp/frps_s80_sin81.ini:/etc/frp/frps.ini \
  snowdreamtech/frps
docker run -d \
  --restart=always \
  --name frpc_s80_cin3389 \
  -p 10.1.0.10:3389:3389 \
  -v /mnt/docker-data/container_data/frp/frpc_s80_cin3389.ini:/etc/frp/frpc.ini \
  snowdreamtech/frpc
# --network host \ 直接使用主机
```
### [nagios监控软件](https://hub.docker.com/r/jasonrivers/nagios)
```bash
docker run --name nagios4  \
  -v /mnt/docker-data/container_data/nagios4/nagios/etc/:/opt/nagios/etc/ \
  -v /mnt/docker-data/container_data/nagios4/nagios/var:/opt/nagios/var/ \
  -v /mnt/docker-data/container_data/nagios4/Custom-Nagios-Plugins:/opt/Custom-Nagios-Plugins \
  -v /mnt/docker-data/container_data/nagios4/nagiosgraph/var:/opt/nagiosgraph/var \
  -v /mnt/docker-data/container_data/nagios4/nagiosgraph/etc:/opt/nagiosgraph/etc \
  -p 10.1.0.13:80:80 jasonrivers/nagios:latest
# 不好用，启动后报错
```
### [Zabbix网络监控](https://hub.docker.com/search?q=zabbix)
1. mysql
### `proxychains4`
```bash
sudo apt install proxychains4
dpkg -L proxychains4
sudo vim /etc/proxychains4.conf
proxychains curl cip.cc # 通过代理查看本机公网ip
```

### [jellyfin](https://jellyfin.org/docs/general/installation/container)
```bash
docker run -d --name jellyfin \
  -p 10.1.0.10:8096:8096 \
  -v /mnt/docker-data/container_data/jellyfin/cache:/cache \
  -v /mnt/docker-data/container_data/jellyfin/config:/config \
  --mount type=bind,source=/mnt/docker-data/container_data/xunlei/downloads,target=/media_xunlei_download,readonly \
  jellyfin/jellyfin
``