## Take a Look

```bash
labyrinth [-m|--map FILE] [-p|--player ID] [--move DIRECTION] [--version]
```

## Description

从文件加载迷宫地图，显示和移动指定的玩家。

--map 或 -m: 指定地图文件路径。
--player 或 -p: 指定玩家 ID (0-9)。
--move: 指定移动方向 (up, down, left, right)。
--version: 显示版本信息。
这些参数可以组合使用。

以下对 labyrinth 的一些具体解释：

中括号扩起的参数是可选参数。因此 -m, -p, --move, --version 都是可选的参数。
同一个选项可以有别名。在 labyrinth 中，-m 和 --map 的含义是一样的，-p 和 --player 的含义是一样的。

## Standard

```bash

labyrinth --map map.txt --player id
labyrinth -m map.txt -p id

# 功能：解析地图，并打印 map.txt 中的内容 (原样打印)
# 参数：
# --map 或 -m：指定地图文件路径
# --player 或 -p：指定玩家ID（0-9）
# -m 和 -p 可以互换位置
# 错误处理：
# 如果地图文件不存在或格式不正确，退出并返回错误码 1
# 如果玩家 ID 无效 (不在 0-9 范围内)，退出并返回错误码 1
# 如果缺少任何必需参数，退出并返回错误码 1
# 如果迷宫中的所有空地不连通，退出并返回错误码 1
# 如果迷宫过大，退出并返回错误码 1

labyrinth --map map.txt --player id --move direction
labyrinth -m map.txt -p id --move direction

# 功能：移动指定玩家
# 参数：
# --move：移动方向，可选值为up、down、left、right
# 行为规则：
# 只能移动到空地 (不能是墙壁或其他玩家所在位置)
# 如果移动成功，退出并返回错误码 0
# 果地图中没有该玩家记录，则将玩家放置在第一个空地（从上到下，从左到右查找第一个空地）
# 错误处理：
# 如果移动失败 (目标位置是墙壁或其他玩家)，退出并返回错误码 1

labyrinth --version

# 功能：显示版本信息
# 输出：必须包含 “Labyrinth Game”，其他信息可自定义
# 行为规则：
# 如果命令行参数只有 --version，显示版本信息并返回错误码 0
# 错误处理：
# 如果同时包含 --version 和其他参数，返回错误码 1

# HINT: use getopt_long()!
```
