# Learn-Cpp-Compilation-and-Debugging

## 1. 熟悉git的操作

### 1.1 add和commit相关操作

> 注意，此时还没有将代码提交到远程

- `git add filename`: 修改并添加目标文件。避免使用`git add .`，会导致所有未被 Git 忽略的文件添加到暂存区，添加很多不必要的文件。
- `git status`: 查看当前git状态，包括哪些文件被修改但没有被添加到暂存区，哪些文件已经被添加到暂存区但还没有提交，是否与远程分支同步等信息
- `git commit -m "add some docs here"`: 提交当前改动并添加提交信息。
- `git commit --amend --no-edit`: 将本次修改的内容追加到上一次提交中，并覆盖原提交信息，适用于改动较小的情况。
### 1.2 创建分支

- 

