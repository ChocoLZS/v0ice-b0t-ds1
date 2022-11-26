#include <service/client.hpp>
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
  std::map<std::string, std::string> branches;
  MSGPACK_DEFINE(type, speak, stepId, _default_, branches);
};


void clientStart() {
  rpc_client client;
  client.connect(client::config::SERVER_ADDRESS, client::config::PORT);
  bool r = client.connect();
  if (!r) {
    std::cout << "connect failed" << std::endl;
    return;
  }
  service::response res =
      client.call<service::response>("hello", client::config::USERID);
  std::cout << res.speak << std::endl;
  if (res.type == RES_CLOSE || res.type == RES_ERROR) {
    goto end;
  }

  std::cout << printBranches(res.branches) << std::endl;
  for (;;) {
    std::string input;
    std::cout << ">> ";
    std::cin >> input;
    std::string nextStep;
    if (res.branches.find(input) != res.branches.end()) {
      nextStep = res.branches[input];
    } else {
      nextStep = res._default_;
    }
    res = client.call<service::response>("getStepInfo", client::config::USERID,
                                         nextStep);
    std::cout << res.speak << std::endl;
    if (res.type == RES_CLOSE || res.type == RES_ERROR) {
      goto end;
    }
    if (res.branches.size() > 0) {
      for (auto &branch : res.branches) {
        std::cout << branch.first << std::endl;
      }
    }
  }
end:
  client.close();
  return;
}
std::string printBranches(std::map<std::string, std::string> branches) {
  std::string result;
  for (auto &branch : branches) {
    result += branch.first + "\n";
  }
  return result.substr(0, result.size() - 1);
}
};  // namespace service