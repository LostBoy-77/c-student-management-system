# C语言学生信息管理系统

## 项目简介

本项目是一个使用 C11 编写的控制台学生信息管理系统，用于软件工程专业 C 语言课程实践。项目采用模块化结构，将交互界面、学生业务逻辑、文件存储和测试代码分离。

## 功能模块

- 添加学生：录入学号、姓名和成绩
- 显示学生：表格形式显示全部记录
- 查询学生：根据学号精确查询
- 修改学生：根据学号修改姓名和成绩
- 删除学生：根据学号删除记录
- 成绩排序：按成绩从高到低排序
- 成绩统计：计算平均分、最高分、最低分和及格率
- 文件存储：退出时自动保存，启动时自动读取
- 输入校验：拦截重复学号、空姓名、非数字输入和 0～100 之外的成绩

## 项目结构

```text
c-student-management-system/
├─ include/
│  ├─ student.h          学生业务模块接口
│  └─ storage.h          文件存储模块接口
├─ src/
│  ├─ main.c             菜单与输入交互
│  ├─ student.c          增删改查、排序和统计
│  └─ storage.c          二进制文件读取与保存
├─ tests/
│  └─ test_student.c     自动化测试
├─ data/
│  └─ README.md          数据目录说明
├─ docs/
│  ├─ design.md          设计说明
│  └─ test-report.md     测试报告
├─ build.ps1             Windows 一键构建与测试脚本
├─ .gitignore
└─ README.md
```

## 开发环境

- Windows 10/11
- GCC（MinGW-w64）
- C11 标准
- Visual Studio Code
- Git

## 编译与运行

在项目根目录打开 PowerShell，执行：

```powershell
gcc src\main.c src\student.c src\storage.c -Iinclude -Wall -Wextra -pedantic -std=c11 -o student-system.exe
.\student-system.exe
```

也可以运行一键脚本：

```powershell
powershell -ExecutionPolicy Bypass -File .\build.ps1
```

## 测试方法

手动编译并运行测试：

```powershell
gcc tests\test_student.c src\student.c src\storage.c -Iinclude -Wall -Wextra -pedantic -std=c11 -o test-student.exe
.\test-student.exe
```

测试成功时显示：

```text
All student management tests passed.
```

## 数据文件

程序把学生记录保存在 `data/students.dat`。该文件是运行时数据，已被 `.gitignore` 排除，不会上传个人学生信息。

## 使用示例

```text
Please enter your choice: 1
Enter student ID: 1001
Enter student name: Alice Zhang
Enter score (0-100): 88
Student added successfully.
```

## 已知限制

- 最多保存 100 名学生
- 成绩使用 0～100 分制
- 数据文件为本机二进制格式，不用于跨平台数据交换

## 作者

GitHub：[@LostBoy-77](https://github.com/LostBoy-77)
