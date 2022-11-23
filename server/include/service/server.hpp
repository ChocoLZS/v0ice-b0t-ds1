#pragma once
#include <rest_rpc/rest_rpc.hpp>
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
};  // namespace service
namespace service {
void serverStart();
service::response getStepInfo(rpc_conn conn, int id, std::string stepId);
service::response hello(rpc_conn conn, int id);
void initResponse(int id, service::response &res,
                  std::optional<json> &userInfo);
}  // namespace service