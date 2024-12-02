# Git手册
## 目的
记录常用的git技巧

## 故事
### 初始化库并交由github管理
1.  先在`github`上创建仓库拿到地址。
1.  初始化仓库并提交
    ```bash
    git init
    echo "" > README.md
    git add README.md
    git commit -m "init"
    git remote add origin git@github.com:xxx/xxx.git
    git push --set-upstream origin master # 可能是main
    ```
### 补充提交
*   `git commit --amend` 修改上一次提交
#### 向其他计算机分享自己的代码
*   背景：两台计算机A与B，B无法联网，无法向github提交代码。
    *   B是保密本。
*   需求：要将代码库放在B上，做一些修改后，同步到github上。
*   解决方案：
    1.  A上克隆代码：`git clone git@github.com:xxx/proj.git`
    1.  在A上生成一个裸库：`git clone --bare -l ./proj/.git ./bare/proj.git`
    1.  在B上克隆这个裸库：`git clone smb://xxx.xxx.xxx.xxx/bare/proj.git`
    1.  在B上配置：`git config user.name "jiangyx_on_b"`, `git config user.email "xxx@xxx.xxx"`
    1.  在B上修改并提交。
    1.  在B上推送到远程：`git push origin master`
    1.  在A上添加裸仓库：`git remote add bare ../bare/proj.git`
    1.  在A上拉取：`git pull bare master`
*   思路：在A上创建裸仓库，A上的仓库负责更新裸仓库。B从裸仓库获取github上的最新代码。B对代码进行修改，更新到裸仓库上。由A从裸仓库拉取最新代码，并提交到github。