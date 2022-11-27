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
  std::string silence;
  std::map<std::string, std::string> branches;
  std::vector<int> timers;
  MSGPACK_DEFINE(type, speak, stepId, _default_,silence, branches, timers);
};
};  // namespace service
namespace service {

/**
 * @brief Start the rpc server, listen on the config port.
 * @throw std::runtime_error if the server fails to start.
 */
void serverStart();

/**
 * @brief Process the user's input
 * @param conn The connection of the user
 * @param id The id of the user
 * @param stepId The next step for the request, default value is default branch
 * @return service::response The response to the client
 * @throw std::runtime_error If the user id is not found
 */
service::response getStepInfo(rpc_conn conn, int id, std::string stepId);

/**
* @brief Establish the first connection with the client
* @param conn The connection of the user
* @param id The id of the user
* @return service::response The entry step response to the client
* @throw std::runtime_error If the user id is not found
*/
service::response hello(rpc_conn conn, int id);

/**
* @brief Initalize the response with existence of the user
* @param id The id of the user
* @param response The new response to be constructed
* @param userInfo The user's information getting from database
* @throw std::runtime_error If the user doesn't exist
*/
void initResponse(int id, service::response &res,
                  std::optional<json> &userInfo);
}  // namespace service