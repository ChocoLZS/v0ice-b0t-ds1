# 简单的语音客服 dsl

<!--ts-->
 * [简单的语音客服 dsl](#简单的语音客服-dsl)
      * [开发环境](#开发环境)
      * [目录结构](#目录结构)
      * [安装方法](#安装方法)
         * [依赖库](#依赖库)
         * [安装命令](#安装命令)
         * [测试安装命令](#测试安装命令)
      * [使用方法](#使用方法)
         * [服务端](#服务端)
         * [客户端](#客户端)
         * [数据库结构](#数据库结构)
      * [服务端详情](#服务端详情)
      * [客户端详情](#客户端详情)

<!-- Created by https://github.com/ekalinin/github-markdown-toc -->
<!-- Added by: chocoie, at: Sun Nov 27 12:53:17 CST 2022 -->

<!--te-->

## 开发环境

- 操作系统：
  - 发行版：Ubuntu 22.04.1
  - 内核：Linux version 5.15.74.2-microsoft-standard-WSL2
- 语言：
  - c++： std 17+
- 编译工具：
  - cmake：3.14+
  - clang or g++
- 数据库：sqlite3

## 目录结构

```text
.
├── CMakeLists.txt			# cmake脚本
├── DslConfig.h.in			# dsl的宏定义
├── README.md				
├── clang_format.bash		# clang-format 脚本
├── client					# 客户端源代码
├── doc						# 文档
├── server					# 服务端源代码
├── test					# 测试脚本源代码
└── thirdparty				# 第三方库
```

## 安装方法

### 依赖库

> 部分已经下载到thirdparty文件夹中，还有一部分需要手动安装

- [nlohmann/json](https://github.com/nlohmann/json)：json库

- [p-ranav/argparse](https://github.com/p-ranav/argparse)：参数解析库
- [SergiusTheBest/plog](https://github.com/SergiusTheBest/plog)：日志库
- [qicosmos/rest_rpc](https://github.com/qicosmos/rest_rpc)：rpc框架

- sqlite3：sqlite3的sdk
  - 需手动安装
  - 比如	`sudo apt install libsqlite3-dev`

### 安装命令

以使用g++ 和 cmake为例

进入项目根目录

`cmake -S . -B build`

进入build目录

`cd build`

`cmake --build .`

进入bin目录

`cd ../bin`

```bash
cmake -S . -B build
cd build
cmake --build .
cd ../bin
```

```text
$ tree
.
├── dsl_client
└── dsl_server
```

### 测试安装命令

`cmake -S . -B build -DTESTS=ON`

`cd build`

`cmake --build .`

`cd ../bin`

```bash
cmake -S . -B build -DTESTS=ON
cd build
cmake --build .
cd ../bin
```

```text
$ tree
.
├── dsl_client
├── dsl_server
└── test
    ├── test_server_interpreter
    ├── test_*
    .
    .
    .
    └── test_string
```

## 使用方法

### 服务端

```bash
./dsl_server --help
Usage: dsl [-h] [--file PATH] [--port PORT] [--log PATH] [--debug] [--database PATH]

Optional arguments:
  -h, --help            shows help message and exits
  -v, --version         prints version information and exits
  -f, --file PATH       path to script file [default: "./script"]
  -p, --port PORT       port to listen [default: 9000]
  -l, --log PATH        path to save log file [default: ""]
  -d, --debug           debug mode
  --database PATH       path to database file [default: "./db/dsl.db"]
```

不指定参数的情况下将以默认路径来执行

### 客户端

```bash
./dsl_client --help
Usage: dsl-client [-h] [--server ADDRESS] [--port PORT] [--debug] [--log PATH] [--uid UID]

Optional arguments:
  -h, --help            shows help message and exits
  -v, --version         prints version information and exits
  -s, --server ADDRESS  server address [default: "127.0.0.1"]
  -p, --port PORT       port to server [default: 9000]
  -d, --debug           show log debug info,if log mode open
  -l, --log PATH        path to save log file, empty for no log [default: ""]
  -u, --uid UID         user id
```

### 数据库结构

**userinfo**

| 名称   | 类型         | 含义                     |
| ------ | ------------ | ------------------------ |
| id     | int          | 用户id，唯一识别用户信息 |
| name   | varchar(64)  | 用户姓名                 |
| amount | int          | 用户帐单                 |
| credit | int          | 用户话费                 |
| data   | varchar(255) | 用户信息                 |

```sql
create table userinfo(
    id int primary key,
    name varchar(64),
    amount int,
    credit int,
    data varchar(255)
)
```

## 服务端详情

可进入[Server](https://github.com/ChocoLZS/voice-bot-dsl/tree/main/server)目录查看README.md

## 客户端详情

可进入[Client](https://github.com/ChocoLZS/voice-bot-dsl/tree/main/client)目录查看README.md
