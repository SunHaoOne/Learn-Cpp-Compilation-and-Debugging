# Learn-Cpp-Compilation-and-Debugging

## 1. 熟悉git的操作

### 1.1 add和commit相关操作

> 注意，此时还没有将代码提交到远程

- `git add filename`: 修改并添加目标文件。避免使用`git add .`，会导致所有未被 Git 忽略的文件添加到暂存区，添加很多不必要的文件。
- `git status`: 查看当前git状态，包括哪些文件被修改但没有被添加到暂存区，哪些文件已经被添加到暂存区但还没有提交，是否与远程分支同步等信息
- `git commit -m "add some docs here"`: 提交当前改动并添加提交信息。可以使用`git log`查看提交历史记录
- `git commit --amend --no-edit`: 将本次修改的内容追加到上一次提交中，并覆盖原提交信息，适用于改动较小的情况。

### 1.2 branch相关操作

#### 1.2.1 创建新分支

- **直接在新分支开发**
    - `git branch compile-test`：创建新分支`compile-test`
    - `git checkout compile-test`: 切换到分支`compile-test`
    > `git branch -b compile-test`: 创建新分支`compile-test`并且切换到该分支

- **在主分支开发**
    - 在主分支开发后不提交，然后利用`git branch -b compile-test`，这个时候更改都会转移到新分支上

#### 1.2.2 合并分支

> 开发结束后测试稳定即可合并到main分支,适用于当前分支不落后于主分支的情况。

- `git checkout main`: 切换到主分支
- `git merge compile-test`: 将`compile-test`合并到主分支
