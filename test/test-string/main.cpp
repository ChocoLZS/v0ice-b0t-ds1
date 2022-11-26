#include <utils/util.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <string>

TEST(server_string, test_string_split) {
  std::string str = "a,b,c,d";
  std::vector<std::string> result = util::str::split(str, ",");
  EXPECT_EQ("a", result[0]);
  EXPECT_EQ("b", result[1]);
  EXPECT_EQ("c", result[2]);
  EXPECT_EQ("d", result[3]);
  EXPECT_EQ(4, result.size());
}

TEST(server_string, test_string_trim) {
  std::string str = "   a,b,c,d   ";
  std::string result = util::str::trim(str);
  EXPECT_EQ("a,b,c,d", result);
}

TEST(server_string,test_eraseWhitespace){
  std::string str = "a\tb    c   d";
  std::vector<std::string> result = util::str::eraseWhitespace(str);
  EXPECT_EQ("a", result[0]);
  EXPECT_EQ("b", result[1]);
  EXPECT_EQ("c", result[2]);
  EXPECT_EQ("d", result[3]);
  EXPECT_EQ(4, result.size());
}
