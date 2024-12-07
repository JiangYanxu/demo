# vscode 使用手册
## todo
* 研究研究tasks.json
* 有空补充补充代码片段
## 快捷键
|快捷键|功能|
|:-:|:-:|
|<kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>P</kbd>|命令|
|<kbd>Ctrl</kbd>+<kbd>`</kbd>|打开控制台|
|<kbd>Alt</kbd>|多光标|
## 配置
### 设置配置
```json
{
    "files.exclude": { //排除文件
        "**/.build" : true,
        "lib/*.dll" : true,
        "library/QxOrm/{[!t]*,?[!e]*}" : true, // 第一位不是t，第二位不是e
    },
    "markdown-preview-enhanced.plantumlServer": "http://localhost:8989/plantuml/svg",
}
```
### 任务配置`tasks.json`
## 有用的插件
|插件名称|功能|
|:-:|----|
|`Compare Folders`|比较文件夹(左边的是打开的文件夹,右边是对比)|
|`Fitten Code`|AI|
|`Git Graph`|Git 图形化工具|
|`GitLens`|为了代码有上次修改人的提示|
|`GitHub Codespaces`|云端开发环境|
|`Markdown Preview Enhanced`|Markdown 预览插件|
|`vscode-pdf`|PDF 阅读器|
|`vim`|Vim 编辑器|
### 插件使用技巧
#### vim
* 点击`--INSERT--`临时禁用Vim模式
#### cmake
* `kit`:工具包
* `reconfig`:重新配置
## 代码片段
### `cpp.json`
```json
{
    "header file": { // 标题
        "prefix": "template-hpp", // 起手式
        "body": [
			"#ifndef ${1:${TM_FILENAME/([^.]*)([.]{1})(.*)/${1:/upcase}_${3:/upcase}/}}",
			"#define ${1}",
			"$0",
			"#endif // ${1}"
        ],
        "description": "包含一次",
        "isFileTemplate" : true // 是否为文件模板
    }
}
```