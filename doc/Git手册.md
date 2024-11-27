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
