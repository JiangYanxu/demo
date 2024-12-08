# 硬盘相关
## 概念
* 硬盘从啥也没有到能读写需要经历：
  1. `lsblk -p`确定硬盘位置，list block disk
  2. `parted /dev/sdb`硬盘管理数据
     1. `help [command]`帮助
     2. `p`查看硬盘信息、分区表、分区信息
     3. `mklabel gpt`建立gpt分区表
     4. `mkpart primary 0% 100%`创建充满磁盘的主分区<br>
        `mkpart primary ext4 0% 100%`创建并格式化
  3. `mkfs.ext4 /dev/sdb1`以ext4格式化/dev/sdb硬盘上第一个分区
  4. `mount /dev/sdb1 /mnt/data`挂载到目录树
  5. `umount /mnt/data`取消挂载
  * `df -h [/home]`查看文件系统、大小、余量、挂载点
  * `du -sh *`查看当前目录下所有内容占用的空间
* Linux一切皆文件，设备也是文件多存放于`/dev`下
* 块设备：一次可读写一个数据块，相对于字符设备来说
* 分区表：建立分区前需要分区表，常见gpt与mbr（淘汰）
* 分区：将磁盘连续的划分几个区域，当作windows盘来理解
* 文件系统：某种格式，操作系统按格式来存取数据，常见ext4与NTFS
* 格式化：动词，将分区格式化为某种文件系统。经过格式化的分区才能被操作系统读写
* 目录树：目录是个树型结构，目录套目录，目录装文件
* 挂载：格式化的分区需要挂载到某个文件夹，向这个文件夹读写，就是再读写这个分区
* 原则上，分区完毕后分区是不可以扩容、压缩（改变分区大小）等操作的。<br>
  LVM Logical Volume Manager 逻辑卷管理就是完成这一任务的。
* LVM的概念
  * PV Physical Volume 物理卷，即分区
  * VG Volume Group 卷组，一个逻辑硬盘，物理空间由组内PV提供
  * LV Logical Volume 逻辑卷，即逻辑分区，在逻辑磁盘VG上的逻辑分区LV
  * LVM将PV（物理分区）重组成VG（逻辑磁盘）进而划分区LV（逻辑分区）
* Linux中
  * 物理磁盘名命：`/dev/sda`、`/dev/sdb`....
  * 虚拟磁盘名命：`/dev/vda`....
  * 分区名命：`/dev/sda1`为sda的首个分区、`/dev/sdb3`为sdb的第三个分区
  * VG卷组名：`/dev/VG-NAME/`（是个文件夹）
  * LV逻辑卷名：`/dev/VG-NAME/LV-NAME`（是个分区）
* LVM相关命令
  |功能|物理卷PV管理|卷组VG管理|逻辑卷LV管理|
  |:-:|:-|:-|:-|
  |扫描|`pvs\|pvscan`|`vgs\|vgscan`|`lvs\|lvscan`|
  |建立|`pvcreate`|`vgcreate`|`lvcreate`|
  |显示|`pvdisplay`|`vgdisplay`|`lvdisplay`|
  |删除|`pvremove`|`vgremove`|`lvremove`|
  |扩展|`—`|`vgextend`|`lvextend`|
  |缩小|`—`|`vgreduce`|`lvreduce`|
  * 说明：
    1. pvcreate的目标是将物理分区格式化成PV
    2. vgcreate的目标是创建VG，将多个PV绑定到VG
    3. lvcreate的目标是从VG中拿出多少空间划分分区，分区在`/dev/VG-NAME/LV-NAME`
* 内心活动：
  1. 担心更换设备或者重装操作系统，VG消失、PV需要重新格式化、LV重新创建。
     * 好像PV、VG、LV数据都存在磁盘里，这也是扫描的目的。
       1. 那同名VG怎么办？
       * 不管了遇到问题再说，最不济备份！
  2. lvcreate有好多模式，还有软raid。会不会影响缩小容量
     * 好像没有缩小容量的场景
  3. 好像还能改名挺好，强迫症福音
