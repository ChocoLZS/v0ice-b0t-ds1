#include <gtest/gtest.h>

#include <interpreter/interpreter.hpp>
#include <string>
#include <vector>

TEST(server_interpreter, test_interpreter_generateSpeak) {
  Step step;
  step.speak.items.push_back({(int)StrType::STR, "Hello"});
  step.speak.items.push_back({(int)StrType::VAR, "$name"});
  step.speak.items.push_back({(int)StrType::STR, "testtesttest"});
  json userInfo;
  userInfo["$name"] = "Jerry";
  std::string result = interpreter::executor::generateSpeak(step, userInfo);
  EXPECT_EQ("Hello Jerry testtesttest", result);
}
