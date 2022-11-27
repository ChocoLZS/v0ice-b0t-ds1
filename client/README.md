# Client端目录介绍

<!--ts-->

* [Client端目录介绍](#client端目录介绍)
   * [文件目录](#文件目录)
   * [Client端函数逻辑](#client端函数逻辑)
   * [主要服务](#主要服务)
   * [定时器实现](#定时器实现)

<!--te-->

## 文件目录

```text

```

## Client端函数逻辑

<img src="https://s3.uuu.ovh/imgs/2022/11/26/84e950dea8244deb.jpg" style="zoom:67%;"/>

## 主要服务

客户端每次向服务端的请求都会携带上自己的user id，如果未找到该用户则关闭连接

客户端向服务端发送一个hello请求，获取入口步骤的response。

然后根据response所提示的步骤进行下一步选择

- 如果为退出步骤，则关闭连接
- 如果有定时器，则在规定时间内输入，否则将跳转为silence分支
- 如果输入未找到分支，则向服务端请求默认分支数据
- 如果找到了分支，则向服务器请求对应的分支数据

## 定时器实现

以Listen 5,20 为例

从用户端接收到服务端的response开始，过5秒再进行20秒的计时

所以总的来说我们只要在5 + 20秒内限时接受用户输入即可

```c++
bool read_input(int beginTimer, int endTimer) {
    std::cout << ">> " << std::flush;
    struct pollfd _poll = {STDIN_FILENO, POLLIN | POLLPRI};
    std::string input;
    if (poll(&_poll, 1, (beginTimer+endTimer) * 1000)) {
      std::cin >> input;
    } else {
      std::cout << "Timeout" << std::endl;
      fflush(stdin);
      PLOG_DEBUG << "Read user input with timeout";
      return true;
    }
    PLOG_DEBUG << "Input: " << input;
    return false;
}
```

