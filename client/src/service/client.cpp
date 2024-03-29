#include <poll.h>
#include <stdio.h>
#include <unistd.h>

#include <exception>
#include <iostream>
#include <service/client.hpp>
#include <utils/logger.hpp>
#include <utils/util.hpp>

using namespace rest_rpc;
using namespace rest_rpc::rpc_service;

#define RES_OK 0
#define RES_ERROR 1
#define RES_INFO 2
#define RES_CLOSE 3
namespace service {
struct response {
  int type;
  std::string speak;
  std::string stepId;
  std::string _default_;
  std::string silence;
  std::map<std::string, std::string> branches;
  std::vector<int> timers;
  MSGPACK_DEFINE(type, speak, stepId, _default_, silence, branches, timers);
};

// global variable to process user input
std::string input;

bool read_input() {
  PLOG_DEBUG << "Read user input without timeout";
  std::cout << ">> ";
  std::cin >> input;
  PLOG_DEBUG << "Input: " << input;
  return true;
}

bool read_input(int beginTimer, int endTimer) {
  std::cout << ">> " << std::flush;
  struct pollfd _poll = {STDIN_FILENO, POLLIN | POLLPRI};
  if (poll(&_poll, 1, (beginTimer + endTimer) * 1000)) {
    std::cin >> input;
  } else {
    PLOG_DEBUG << "Read user input with timeout";
    return true;
  }
  return false;
}

void clientStart() {
  rpc_client client;
  client.connect(client::config::SERVER_ADDRESS, client::config::PORT);
  bool r = client.connect();

  if (!r) {
    PLOG_ERROR << "Connect failed";
    return;
  }
  PLOG_DEBUG << "Client connect server "
             << client::config::SERVER_ADDRESS
             << ":"
            << std::to_string(client::config::PORT);
  // 自动向服务器发送初始连接请求
  service::response res =
      client.call<service::response>("hello", client::config::USER_ID);
  PLOG_DEBUG << "Current step is: " << res.stepId;
  std::cout << res.speak << std::endl;
  if (res.type == RES_CLOSE || res.type == RES_ERROR) {
    // 终止或发生错误
    PLOG_ERROR << "Something wrong.";
    goto end;
  }
  std::cout << printBranches(res.branches) << std::endl;

  // 接受用户输入
  for (;;) {
    bool isTimeout = false;
    if (res.timers.size() == 0) {
      read_input();
    } else {
      PLOG_DEBUG << "BeginTimer: " << res.timers[0] << "s"
                 << " EndTimer: " << res.timers[1] << "s";
      isTimeout = read_input(res.timers[0], res.timers[1]);
    }
    std::string nextStep;
    PLOG_DEBUG << "Timeout flag is " << isTimeout;
    PLOG_DEBUG << "Input is " << input;
    if (isTimeout) {
      // 超时，跳转silence分支
      nextStep = res.silence;
    } else {
      if (res.branches.count(input) != 0) {
        // 输入正确，跳转对应分支
        nextStep = res.branches[input];
      } else {
        // 非法输入，跳转默认分支
        nextStep = res._default_;
      }
    }
    PLOG_DEBUG << "Next step is: " << nextStep;
    res = client.call<service::response>("getStepInfo", client::config::USER_ID,
                                         nextStep);
    PLOG_DEBUG << "Current step is: " << res.stepId;
    std::cout << res.speak << std::endl;
    if (res.type == RES_CLOSE || res.type == RES_ERROR) {
      // 终止或发生错误
      goto end;
    }
    if (res.branches.size() > 0) {
      std::cout << printBranches(res.branches) << std::endl;
    }
  }
end:
  client.close();
  return;
}
std::string printBranches(std::map<std::string, std::string> branches) {
  std::string result;
  std::cout << "------------------------" << std::endl;
  for (auto &branch : branches) {
    result += branch.first + "\n";
    PLOG_DEBUG << "Branch: " << branch.first << " " << branch.second;
    PLOG_DEBUG << branches.count(branch.first);
  }
  return result.substr(0, result.size() - 1);
}

};  // namespace service