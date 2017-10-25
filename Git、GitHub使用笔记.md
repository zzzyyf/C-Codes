# Git Bash on Windows 使用教程
### 一、基本操作
##### 登录

```
$ git config --global user.name "YourName"
$ git config --global user.email "YourEmail"
```
*注：--global意为全局操作，对这台计算机上的所有仓库使用*
##### 添加版本库、提交文件
```
$ git init //把某个目录变成Git可以管理的仓库
$ git add FileName1 FileName2 ...
$ git commit -m "Why you commit these files"
```
*注：Git的add命令实际上是把文件加入“暂存区”；Git不会提交未添加的修改。*
##### 查看状态、查看文件、比对两版本
```
$ git status
$ cat FileName
$ git diff FileName 
```
##### 查看不同版本、版本间切换
```
$ git log
$ git reset --hard HEAD^//有几个^表示回退几个版本
```
---
###### *git reset参数详解*
- HEAD：当前版本的指针。后面加几个^就回退几个版本，也可以用HEAD~xx表示。
- xxxxxxx：Git的版本号，表示回退到该版本，可以不用写全，Git能自动寻找。
---
##### 历史记录
```
$ git reflog//可以借此查看之前版本的版本号
```
##### 撤销修改
```
$ git checkout -- FileName//用暂存区或版本库里的版本替换工作区里的
$ git reset HEAD FileName//撤销已添加的修改，退回工作区
```
##### 删除文件
```
$ rm FileName//本地的删除操作，可以用checkout撤销
$ git rm FileName//之后别忘了提交删除这个更改
```
##### 推送远程库
- GitHub算是一个面向公众的Git的服务器。
- 创建SSH Key，若用户目录下.ssh目录下有id_rsa和id_rsa.pub可跳过
```
$ ssh-keygen -t rsa -C "YourEmail"
```
- 接下来一路回车即可，id_rsa是私钥，.pub是公钥。
- 登录GitHub,打开"Account Settings"，"SSH Keys"页面，然后点"Add SSH Key",填任意title，在Key文本框里粘贴id-rsa.pub的内容，点"Add Key"完成。
- 接下来把本地的库推送上去。
```
$ git remote add origin git@github.com:YourName/YourRepo//关联远程库
//远程库一般都叫origin
$ git push -u origin master//把master推送至远程库
//-u表示把本机的master和GitHub里的关联起来，以后就不用加了
```