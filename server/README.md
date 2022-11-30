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

### Script

| \<类型\> 名字                | 变量/函数 | 作用                                               |
| ---------------------------- | --------- | -------------------------------------------------- |
| StepId curStep               | 成员变量  | script当前步骤，用于解析语法树初始化使用           |
| StepId entry                 | 成员变量  | script入口步骤，用于与客户端初始化连接使用         |
| StepId _default\_            | 成员变量  | script的默认步骤，每个脚本的最后一个step为默认步骤 |
| std::map<StepId, Step> steps | 成员变量  | stepId 与 Step实例的hashtable                      |
| void addStep(StepId id)      | 成员函数  | 向hashtable中添加步骤                              |
| int stepsCount()             | 成员函数  | 返回步骤数量                                       |
| Step& getCurStep()           | 成员函数  | 获取script当前加载初始化的步骤                     |
| Step& getStep(StepId stepId) | 成员函数  | 获取特定步骤                                       |

### Step

| \<类型\> 名字                                    | 变量/函数 | 作用                                              |
| ------------------------------------------------ | --------- | ------------------------------------------------- |
| Expression speak                                 | 成员变量  | Step的speak列表，用于后续解析变量，字符串拼接等等 |
| Listen listen                                    | 成员变量  | Listen 语句的开始时间和结束时间                   |
| std::map<Answer, StepId> branches                | 成员变量  | branches分支的用户输入与对应StepId的hashtable     |
| bool isEndStep                                   | 成员变量  | 是否为终结步骤                                    |
| StepId stepName                                  | 成员变量  | 当前步骤的变量名                                  |
| StepId silence                                   | 成员变量  | silence步骤的变量名                               |
| StepId \_default_                                | 成员变量  | 默认步骤的变量名                                  |
| void addExpression(Expression expression)        | 成员函数  | 添加表达式                                        |
| void setListen(Listen listen)                    | 成员函数  | set Listen                                        |
| void addBranch(Answer answer, StepId nextStepId) | 成员函数  | 添加分支                                          |
| StepId getBranch(Answer answer)                  | 成员函数  | 获取分支                                          |
| void setSilence(StepId silence)                  | 成员函数  | set Silence                                       |
| void setDefault(StepId _default_)                | 成员函数  | set Default                                       |
| void setEndStep()                                | 成员函数  | 设置当前步骤为终结步骤                            |
### Listen

| \<类型\> 名字  | 变量/函数 | 作用           |
| -------------- | --------- | -------------- |
| int beginTimer | 成员变量  | 计时器开始时间 |
| int endTimer   | 成员变量  | 计时器结束时间 |

### Expression
| \<类型\> 名字                  | 变量/函数 | 作用           |
| ------------------------------ | --------- | -------------- |
| std::vector\<Item> items       | 成员变量  | Items动态数组  |
| void addTerm(std::string term) | 成员函数  | 添加描述性语句 |
| void addVar(std::string var)   | 成员函数  | 添加变量       |

### Item
| \<类型\> 名字   | 变量/函数 | 作用     |
| --------------- | --------- | -------- |
| int type        | 成员变量  | Item类型 |
| std::string val | 成员变量  | 字符串   |

---

### 别名

|         |             |
| ------- | ----------- |
| StepId  | std::string |
| Answer  | std::string |
| VarName | std::string |






## Parser解析器

> 实现细节参考了课件内容

### ParseFile:

```text
ParseFile(fileName,script):
	打开文件
	读取文件每一行line:
		line.trim()删除首尾空白
		忽略空行
		忽略注释
		ParseLine(line)处理一行
	给每个步骤的默认和沉默分支添加跳转步骤
	检查每个跳转分支是否存在	
```

### ParseLine:

```text
ParseLine(line):
	读取一行中空白分割的每一个token：
		遇到'#'开头的token则处理结束（忽略行尾注释）
		获得标识符，字符串或者操作符几类token
		将token加入到vector中
	ProcessTokens(token[])
```

### ProcessTokens:

```text
ProcessTokens(token[],script):
	对List中的每一个token进行处理
	根据token[0]分情况处理并且预先检查参数有效性：
		Step：ProcessStep(token[1],script)
		Listen：ProcessListen(startTimer,endTimer,script)
		Branch：ProcessBranch(token[1],token[3],script)
		Silence：ProcessSilence(token[1],script)
		Speak：ProcessSpeak(token,startIndex,script)
		Exit：ProcessExit(script)
		Default：ProcessDefault(token[1], script)
		如果不是上述token则报错
```

### ProcessStep(stepId):

```text
ProcessStep(stepId,script):
	如果这是第一个Step，则设置当前Step为Script的entry
	Script创建一个新的Step，标识为stepId
	设置当前Step为新创建的Step
	设置默认分支为当前分支(保证最后一个Step为默认分支)
```

### ProcessExpression(token[]):

```text
ProcessSpeak(token[]):
	这么简单的表达式...
	忽略掉加号
	判断字符串的合法性
	根据字符串类型来构造Item，追加到Expression中的Vector<Item>
```

### ProcessSpeak(token[]):

```text
ProcessSpeak(token[]):
	ProcessExpression(token[])得到Expression
	将Speak以及对应的表达式模板存入当前的Step
```

### ProcessListen(startTimer,stopTimer):

```text
ProcessListen(startTimer,stopTimer):
	构造Listen(startTimer,stopTimer)存入当前Step
```

### ProcessBranch(answer,nextStepId):

```text
ProcessBranch(answer,nextStepId):
	将answer和nextStepId插入当前Step的HashTable
```

### ProcessSilence(nextStepId):

```text
ProcessSilence(nextStepId):
	将当前Step的silence变量设置成nextStepId中的值
```

### ProcessDefault(nextStepId):

```
ProcessDefault(nextStepId):
	将当前Step的default变量设置成nextStepId中的值
```

### ProcessExit():

```
ProcessExit():
	将当前Step设置为终结Step
```

## Interpreter解释器

集合了语法树并封装在了rpc服务中，由服务端与客户端共同完成解释

### 初始连接请求：hello(id)

服务端构造基于客户端提供的id

获取userinfo的数据结构

构造相应的初始step的response，返回客户端

### 任意连接请求：getStepInfo(id,stepId)

服务端构造基于客户端提供的id

获取userinfo的数据结构

构造相应stepId的response，返回客户端
