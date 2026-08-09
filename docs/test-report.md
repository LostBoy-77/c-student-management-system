# 测试报告

测试日期：2026-08-09

## 自动化测试范围

| 编号 | 测试内容 | 结果 |
|---|---|---|
| T01 | 添加合法学生 | 通过 |
| T02 | 拦截重复学号 | 通过 |
| T03 | 拦截超过 100 分的成绩 | 通过 |
| T04 | 按学号查询已存在学生 | 通过 |
| T05 | 查询不存在的学号 | 通过 |
| T06 | 修改姓名和成绩 | 通过 |
| T07 | 修改不存在的学生 | 通过 |
| T08 | 按成绩从高到低排序 | 通过 |
| T09 | 计算平均分、最高分、最低分和及格率 | 通过 |
| T10 | 保存数据并重新读取 | 通过 |
| T11 | 删除已存在学生 | 通过 |
| T12 | 删除不存在的学生 | 通过 |

## 验证命令

```powershell
gcc tests\test_student.c src\student.c src\storage.c -Iinclude -Wall -Wextra -Werror -pedantic -std=c11 -o test-student.exe
.\test-student.exe
```

## 测试结果

```text
All student management tests passed.
```

主程序还经过完整交互场景验证：添加两名学生、查询、修改、排序、统计、删除、保存退出，并在第二次启动时成功恢复剩余记录。
