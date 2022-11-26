#include <parser/parser.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <string>
TEST(test_server_parser, test_parser_parseline) {
  //测试是否可以把空白字符串给删除，并返回
  std::vector<std::string> tokens = parser::ParseLine(
      "Speak     $name\n\r\t\f\v +     \"您好，请问有什么可以帮您?\""); 
  EXPECT_EQ("Speak", tokens[0]);
  EXPECT_EQ("$name", tokens[1]);
  EXPECT_EQ("+", tokens[2]);
  EXPECT_EQ("\"您好，请问有什么可以帮您?\"", tokens[3]);
  EXPECT_EQ(4, tokens.size());
}

TEST(test_server_parser, test_parser_branches) {
  //测试整套流程
  std::vector<std::string> lines = {
      "Step welcome",
      "Speak $name + \"您好，请问有什么可以帮您?\"",
      "Listen 5,20",
      "Branch  \"投诉\" , complainProc",
      "Branch  \"账单\" , billProc",
      "Silence silence",
      "Default defaultProc"};
  // 预期token长度
  std::vector<int> parseLen = {2,4,2,4,4,2,2};
  Script script;
  for (int i =0;i < lines.size();i++) {
    std::vector<std::string> tokens = parser::ParseLine(lines[i]);
    EXPECT_EQ(parseLen[i], tokens.size());
    parser::ProcessTokens(tokens, script);
  }
  Step step = script.getStep("welcome");
  EXPECT_EQ(2, step.branches.size());
  EXPECT_EQ("complainProc", step.branches["投诉"]);
  EXPECT_EQ("billProc", step.branches["账单"]);
  EXPECT_EQ("silence", step.silence);
  EXPECT_EQ("defaultProc", step._default_);
  EXPECT_EQ(5, step.listen.beginTimer);
  EXPECT_EQ(20, step.listen.endTimer);
}

//  测试错误的语义
TEST(test_server_parser, text_parser_unexpected) {
  std::vector<std::string> tokens = {"ErrorTest"
                                     "$name",
                                     "+"};
  Script script;
  try {
    parser::ProcessTokens(tokens, script);
  }catch(std::runtime_error& err) {
    EXPECT_EQ("Unknown command: ErrorTest", err.what());
  }
  
}

