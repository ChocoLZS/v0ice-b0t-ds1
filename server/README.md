# Server端目录介绍

<!--ts-->

* [Server端目录介绍](#server端目录介绍)
   * [文件目录](#文件目录)
   * [Server端函数逻辑](#server端函数逻辑)
   * [语法树结构](#语法树结构)
   * [Parser解析器](#parser解析器)
   * [Interpreter解释器](#interpreter解释器)

<!--te-->

## 文件目录

```
.
├── CMakeLists.txt				# cmake脚本
├── README.md					
├── include						# include 头文件
│   ├── db						# 数据库头文件
│   │   └── sqlite.hpp
│   ├── interpreter				# 解释器
│   │   └── interpreter.hpp
│   ├── parser					# 解析器
│   │   └── parser.hpp
│   ├── service					# 服务
│   │   └── server.hpp			# 服务端
│   ├── typing
│   │   └── type.hpp			# 类和类型规定
│   └── utils
│       ├── logger.hpp			# 日志
│       └── util.hpp			# 工具函数
└── src
    ├── db
    │   ├── db.cpp				# db连接与关闭
    │   └── sqlgen.cpp			# sql语句接口
    ├── global.cpp				# 全局变量
    ├── interpreter				
    │   └── interpreter.cpp		# 解释器
    ├── main.cpp				# 主函数
    ├── parser	
    │   └── parser.cpp			# 脚本解析
    ├── service
    │   └── server.cpp			# rpc服务端以及接口定义
    └── utils
        ├── config.cpp			# 参数解析服务和初始化配置
        ├── logger.cpp			# 日志服务初始化
        └── string.cpp			# 处理字符串函数
```

## Server端函数逻辑

<img src="https://s3.uuu.ovh/imgs/2022/11/26/6eaea3e18f76c918.jpg" style="zoom:67%;" />

## 语法树结构

![](https://s3.uuu.ovh/imgs/2022/11/26/c0f36e83cb820d7e.jpg)



## Parser解析器

> 实现细节参考了课件内容

## Interpreter解释器

集合了语法树并封装在了rpc服务中，由服务端与客户端共同完成解释
