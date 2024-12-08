# samba配置记录

```bash
sudo apt-get install samba smbclient
sudo cp /etc/samba/smb.conf /etc/samba/smb.conf_bak
sudo vim /etc/samba/smb.conf
[mnt]
path = /mnt/docker-data
public = yes
valid user = jiangyx
available = yes
sudo smbpasswd -a jiangyx #创建密码
sudo systemctl restart smb #重启
sumbclient -L /localhost/mnt #查看结果
```
