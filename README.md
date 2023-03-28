# Learn-Cpp-Compilation-and-Debugging

## 1. 熟悉git的操作

### 1.1 add和commit相关操作

> 注意，此时还没有将代码提交到远程

- `git add filename`: 修改并添加目标文件。避免使用`git add .`，会导致所有未被 Git 忽略的文件添加到暂存区，添加很多不必要的文件。
- `git status`: 查看当前git状态，包括哪些文件被修改但没有被添加到暂存区，哪些文件已经被添加到暂存区但还没有提交，是否与远程分支同步等信息
- `git commit -m "add some docs here"`: 提交当前改动并添加提交信息。可以使用`git log`查看提交历史记录
- `git commit --amend --no-edit`: 将本次修改的内容追加到上一次提交中，并覆盖原提交信息，适用于改动较小的情况。

### 1.2 branch相关操作

- `git log --graph --decorate --oneline`: 查看git的可视化时间线

#### 1.2.1 创建新分支

- **直接在新分支开发**
    - `git branch compile-test`：创建新分支`compile-test`
    - `git checkout compile-test`: 切换到分支`compile-test`
    > `git branch -b compile-test`: 创建新分支`compile-test`并且切换到该分支

- **在主分支开发**
    - 在主分支开发后不提交，然后利用`git branch -b compile-test`，这个时候更改都会转移到新分支上

#### 1.2.2 合并分支 (merge)

> 开发结束后测试稳定即可合并到`main`分支,适用于当前分支不落后于主分支的情况。
> 注意，此时是在本地中将分支合并到主分支`main`，还没有提交到远程

- `git checkout main`: 切换到主分支`main`
- `git merge compile-test`: 将`compile-test`合并到主分支`main`

#### 1.2.3 合并分支 (rebase)



#### 1.2.4 解决合并冲突

> 假如你在一个新分支`compile-test`上，这个时候主分支`main`已经被别人修改了，想将`compile-test`合并到`main`分支会出现冲突。

在冲突的位置，会有提示：
- `Accept Current`: 当前`main`分支，即`current`部分。表示保留当前`main`分支的修改而不保留`compile-test`分支的修改
- `Accept Incoming`: 开发`compile-test`分支，即`incoming`部分。表示保留当前`compile-test`分支的修改而不保留`main`分支的修改
- `Ignore`: 表示暂时忽略这一冲突，但是后续仍然需要解决这个冲突
- `Accept Combination`： 将当前分支和被合并分支中的修改都保留下来。这样可以在文件中看到两个分支中的修改，并手动编辑文件来合并这些修改
