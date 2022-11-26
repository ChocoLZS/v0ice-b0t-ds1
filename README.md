# 简单的语音客服 dsl

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

## 安装命令

以使用g++ 和 cmake为例

进入项目根目录

`cmake -S . -B build`

进入build目录

`cd build`

`cmake --build .`

进入bin目录

`cd ../bin`

```text
$ tree
.
├── dsl_client
└── dsl_server
```

## 测试安装命令

`cmake -S . -B build -DTESTS=ON`

`cd build`

`cmake --build .`

`cd ../bin`

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
