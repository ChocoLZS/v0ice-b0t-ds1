#include <db/sqlite.hpp>
#include <interpreter/interpreter.hpp>
#include <memory>
#include <service/server.hpp>
#include <typing/type.hpp>
#include <utils/logger.hpp>

extern Script script;

namespace service {
void initResponse(int id, service::response &res,
                  std::optional<json> &userInfo) {
  PLOG_DEBUG << "Initializing response...";
  userInfo = sqlgen::getUser(id);
  if (userInfo == std::nullopt) {
    res.type = RES_ERROR;
    res.speak = "用户不存在";
    throw std::runtime_error("用户不存在");
  }
}

service::response hello(rpc_conn conn, int id) {
  PLOG_INFO << "Received a request from client: userId:" << id << "\taddress: "
            << static_cast<std::shared_ptr<connection>>(conn)->remote_address();
  service::response res;
  std::optional<json> userInfo;
  try {
    initResponse(id, res, userInfo);
  } catch (std::runtime_error(e)) {
    PLOG_ERROR << e.what();
    return res;
  }
  res.type = RES_OK;
  Step entry = script.getStep(script.entry);
  res.speak = interpreter::executor::generateSpeak(entry, userInfo);
  res.stepId = entry.stepName;
  res._default_ = entry._default_;
  res.branches = entry.branches;
  PLOG_INFO << "Sending hello and welcome to userId: " << id << "\taddress: "
            << static_cast<std::shared_ptr<connection>>(conn)->remote_address();
  return res;
}

service::response getStepInfo(rpc_conn conn, int id, std::string stepId) {
  PLOG_INFO << "Received a request from client: userId:" << id << "\taddress: "
            << static_cast<std::shared_ptr<connection>>(conn)->remote_address();
  service::response res;
  std::optional<json> userInfo;
  try {
    initResponse(id, res, userInfo);
  } catch (std::runtime_error(e)) {
    PLOG_ERROR << e.what();
    return res;
  }
  PLOG_DEBUG << "Current step: " << stepId;
  res.type = RES_OK;
  Step step = script.getStep(stepId);
  res.type = step.isEndStep ? RES_CLOSE : RES_INFO;
  res.speak = interpreter::executor::generateSpeak(step, userInfo);
  res.stepId = step.stepName;
  res._default_ = step._default_;
  res.branches = step.branches;
  PLOG_INFO << "Sending response to userId: " << id << "\taddress: "
            << static_cast<std::shared_ptr<connection>>(conn)->remote_address();
  return res;
}

void serverStart() {
  try {
    // listen on the port
    rpc_server server(server::config::PORT, std::thread::hardware_concurrency(),
                      (size_t)60 * 5);

    // register the rpc functions
    server.register_handler("hello", service::hello);
    server.register_handler("getStepInfo", service::getStepInfo);

    server.set_network_err_callback(
        [](std::shared_ptr<connection> conn, std::string reason) {
          PLOG_ERROR << "remote client address: " << conn->remote_address()
                     << " networking error, reason: " << reason;
        });

    // start the server
    server.run();
  } catch (std::exception &e) {
    PLOG_ERROR << "Server start failed, reason: " << e.what();
  }
}

}  // namespace service
