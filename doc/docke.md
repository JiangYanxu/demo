# 简单的笔记

## 干货

### 修改容器

### 命令
|image相关命令|说明|
|:-|:-|
|`docker search name`|搜索Docker Hub|
|`docker pull [domain_name/][username/]repository[:tag]`|拉取（下载）镜像|
|`docker image ls`|查看镜像列表|
|`docker image inspect ubuntu:latest`|检查镜像|
|`docker image rm <NameOrID>`|删除镜像|
|`docker image prune`|移除（修剪）悬虚镜像，-a：外加未被使用的镜像|

|container相关命令|说明|
|:-|:-|
|`docker version`|查看版本与存活|
|`docker container run <options> <image>:<tag> <app>`|启动容器<br>-it 以交互式打开并连接到终端<br>-d 后台运行<br>--name 指定容器名<br>--restart always 出主动stop外，始终尝试重启容器<br>-p host_port:container_port 端口映射|
|<kbd>Ctrl</kbd>`+`<kbd>P</kbd>`+`<kbd>Q</kbd>|可在陷入容器时，不杀死容器的退出来|
|`ps -elf`|linux 查看进程命令|
|`docker container exec <options> <NameOrID> <app>`|运行中容器执行命令<br>-it 以交互式打开并连接到终端|
|`docker container ls <options>`|查看所有运行的容器<br>-a 所有容器|
|`docker container start\|restart\|stop\|rm <NameOrID>`|控制容器|
|`docker container pause\|unpause <NameOrID>`|暂停\|恢复容器|

|应用容器化相关命令|说明|
|:-|:-|
|`docker image build -t myImage:latest /path/of/Dockerfile`|构建镜像|
|`docker login\|logout`|登入\|出Docker Hub，登录信息存入`~/.docker/config.json`|
|`docker image tag <sources_image>[:<tag>] <image>[:<tag>]`|为以后镜像创建tag（别名）|
|`docker image push [<image_server>/]username/repository_name[:<tag>]`|推送镜像<br>image_server 默认Docker Hub<br>tag 默认latest|
|`docker image history <image>`|查看镜像构建过程中的指令|
|`docker image inspect <image>`|`RootFS.Layers`查看构建过程中创建了哪些镜像层|

|network相关命令|说明|
|:-|:-|
|`docker container run <options> <image>:<tag> <app>`|启动容器<br>-p host_ip:host_port:container_port 端口映射<br>--network `<network>`<br>--name `<name>` 非默认bridge网络时作为DNS服务的host name<br>--net-alias `<name>` 非默认bridge网络时作为DNS服务的host name|
|`docker network ls`|查看网络列表|
|`docker network inspect <network>`|查看网络详情|
|`docker network create -d bridge myBridge`|新建一个名为myBridge的二层交换机|
|`brctl show`|linux命令，查看二层交换机以及接入的接口|
|`docker network prune`|删除Docker上全部未使用的网络|
|`docker network rm <network>`|删除名为`<network>`的网络|

|日志相关命令|说明|
|:-|:-|
|`journalctl -u docker -f`|查看Docker的Journald日志|
|`docker container logs <NameOrID>`|查看容器内PID为1的进程日志|

|volume相关命令|说明|
|:-|:-|
|`docker volume create myVolume`|创建名为myVolume的卷<br>-d string 指定驱动，默认local|
|`docker volume ls`|查看卷列表|
|`docker volume inspect <name>`|查看卷详情|
|`docker volume prune`|删除所有未被容器使用的卷|
|`docker volume rm <name>`|删除指定卷，要求卷未被使用|
|`docker container run <options> <image>:<tag> <app>`|启动容器<br>`--mount source=myVolume,target=/vol` 指定或创建卷并挂在到`/vol`路径<br>`-v /host/path:/vm/path` 路径映射<br>`-v myVolume:/vm/path` 路径映射|



## 深入浅出Docker - 微信读书
### 进度相关 - 方便被打断后下次能续上
#### 进度
|章节|进度|说明|
|:-|:-|:-|
|第一部分 Docker概览 1-4章|100%||
|第五章 纵观Docker|60%|跳过了4.2，Dockerfile的纵览|
|第8章|100%|讲的有点浅，通过官方手册补充|
|第9,10章|0%|不是眼下使用的，跳过了|
|第11章 Docker网络|60%|跳过了11.2.3多机覆盖网络、11.2.4接入现有网络、11.2.5服务发现、11.2.6Ingress网络|
|第12章 Docker覆盖网络|0%|不是眼下使用的，跳过了|
|第13章 卷与持久化数据|70%|跳过了13.2.3在集群节点间共享存储|
|第14章-结尾|0%|未读|

### Docker安装
* Docker安装要参考官方文档
* Docker有两种Docker Engine与Docker Desktop，服务器安装Docker Engine
* Docker Engine分社区版CE与商业版EE
### 纵观Docker
* Play With Docker可在web上玩docker
* docker client与server之间默认使用socket或pipe进行通讯的
### Docker镜像
* 镜像（image）类似虚拟机模板，有点像面向对象中的类
* `alpine`镜像只有不到10MB
* Docker数据位置/var/lib/docker
  * image只找到了sha256，文件不知道在哪
* `docker pull [domain_name/][username/]repository[:tag]`
  * domain_name：第三方服务器域名，默认从Docker Hub中获取
  * username: 仓库账户名，默认从官方仓库拉取
  * tag：标签（版本），默认latest，latest不保证是 最新的镜像
* 悬虚镜像：没有repository和tag的镜像，显示<none>:<none>
* 镜像标签不可信，但是摘要（镜像散列值）唯一<br>查看摘要`docker image ls --digests`<br>根据摘要拉取`docker image pull repository@sha256:xxxxx...`
### Docker容器
* `docker image inspect ubuntu:latest`中`Cmd`是镜像的默认命令(<app>)
### 应用容器化
* Docker的核心思想：应用整合到容器中，且在容器中运行
* 容器化、Docker化：应用整合到容器的过程
* 容器化过程分为：
  1. 构建应用 -- 可以在Dockerfile中做
  2. 创建Dockerfile，描述应用的依赖、应用的执行
  3. `docker image build`命令生成镜像
* Dockerfile的作用：描述应用、指导Docker完成应用容器化
* 镜像层：镜像构建的过程中，命令可能会创建镜像层，镜像层就是镜像内部的文件修改。
  * 判断命令是否创建镜像层：命令是否修改了镜像内部的文件，
  * 镜像层缓存，镜像层的作用：用于缓存，在多个构建镜像过程中，如果本镜像层一直且构建命令一致，就会使用镜像层的缓存加快构建速度
* Dockerfile简介
  * 注释以`#`开头
  * 每行的命令格式：INSTRUCTION argument
  * 命令不分大小写，但是大写是规范
  * 简单的命令
    |命令|说明|
    |:-|:-|
    |FROM|指定基础镜像层|
    |LABEL|镜像的备注信息|
    |RUN|在镜像中执行命令|
    |COPY|复制文件到镜像中|
    |EXPOSE|记录镜像使用的网络端口|
    |ENTRYPOINT|默认运行的程序|
* Dockerfile最佳实践
  * 尽量使用` && `与` \ `将脚本整合成一句，减少RUN命令的数量以减少镜像层
  * 多阶段构造 -- 应用与生产环境
    * Dockerfile包含多个From，即多个镜像构造
    * 前面的构造目的是编译出软件所需的最小部分（编译软件很大）
    * 最后一个构造取其他构造的成果
    * 这种方式也能使用镜像层缓存以加快构造速度
  * apt-get install命令添加no-install-recommends参数，仅安装核心依赖


### Docker网络
* Docker网络架构设计规范是CNM，CNM定义了3个要素
  * 沙盒Sandbox：独立的网络栈，容器与沙盒一对一
  * 终端Endpoint：虚拟的网络接口，容器与终端一对多
  * 网络Network：二层交换机，根据MAC地址决定是否转发，终端与网络多对多
* Libnetwork是被Docker采用的实现了CNM规范的开源软件<br>Libnetwork支持接入多种驱动与各种网络通信
* Docker网络
  * 单机桥接网络
    * 单机表示只能在单个Docker主机上运行，且只能与Docker主机上的容器进行连接<br>
      桥接表示模拟二层交换机（根据MAC地址转发）
    * 每个Docker主机都有一个默认单机桥接网络：bridge；现在好像多了俩<br>
      除非创建容器时指定`--network`，否则默认连接到bridge
    * Docker Bridge驱动底层基于Linux Bridge技术<br>
      Docker的bridge网络映射到Linux内核中名为docker0的网桥（ifconfig查看）<br>
      `docker network inspect bridge | grep bridge.name`查看
* Docker默认的Bridge网络不允许Docker DNS服务，自定义的网桥可以！<br>
  docker container run --name 或 --net-alias 即可指定名称与容器的映射
### 卷与持久化数据
* 数据分两类
  * 持久化的数据：类似日志、用户信息等等。容器删除仍然保留。
  * 非持久化的数据：从属于容器，生命周期与容器相同。容器删除，数据也删除。
* Docker volume卷：相当于虚拟硬盘，挂载到容器里。
* 卷支持多种驱动，即容器数据可以写如本地磁盘、网络存储系统、外设等等。Linux万物皆文件，有驱动就能由容器写入？比如打印机？
* `docker volume inspect <volume>`内容中Mountpoint数据说明卷的位置


## [Dockerfile reference](https://docs.docker.com/engine/reference/builder/)
### 

## [Get started](https://docs.docker.com/get-started/)
**官方的Get started只是操作步骤，太垃圾了。<br>不想跟着操作！**