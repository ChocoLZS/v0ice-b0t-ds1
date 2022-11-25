/**
 * @details This function parses the given file and consturcts the global script
 * AST.
 */
#include <fstream>
#include <iostream>
#include <parser/parser.hpp>
#include <typing/type.hpp>
#include <utils/logger.hpp>
#include <utils/util.hpp>

namespace parser {
/**
 * @brief Parse the script file
 * @param path The path of the script file
 * @return void
 */
void ParseFile(std::string path,Script& script) {
  std::ifstream file(path);
  //打开文件
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open the script file: " + path
                        + " ,please check your script file.");
  }
  PLOG_DEBUG << "Parsing file: \"" << path << "\" ...";
  std::string line;
  while (std::getline(file, line)) {
    line = util::str::trim(line);
    if (line.empty()) {
      continue;
    }
    if (line[0] == '#') {
      continue;
    }
    try {
      PLOG_DEBUG << "Parsing line: \"" << line << "\" ...";
      std::vector<std::string> tokens = ParseLine(line);
      ProcessTokens(tokens,script);
    } catch (std::runtime_error& err) {
      PLOG_ERROR << "Failed to parse the file.";
      throw std::runtime_error(err.what());
    }
  }
  file.close();
}

std::vector<std::string> ParseLine(std::string line) {
  return util::str::eraceWhitespace(line);
}

/**
 * @brief Process the tokens
 * @param tokens The tokens to be processed
 * @return void
 */
void ProcessTokens(std::vector<std::string> tokens,Script& script) {
  std::string command = util::str::getCommand(tokens[0]);
  try {
    switch (util::action_mapping[command]) {
      case ActionType::Step:
        ProcessStep(tokens[1],script);
        break;
      case ActionType::Listen: {
        // todo: error checking
        std::vector<std::string> strs = util::str::split(tokens[1], ",");
        ProcessListen(std::stoi(strs[0]), std::stoi(strs[1]),script);
        break;
      }
      case ActionType::Branch: {
        ProcessBranch(tokens[1].substr(1, tokens[1].size() - 2), tokens[3],script);
        break;
      }
      case ActionType::Silence:
        ProcessSilence(tokens[1],script);
        break;
      case ActionType::Speak:
        ProcessSpeak(tokens, 1,script);
        break;
      case ActionType::Exit:
        ProcessExit(script);
        break;
      case ActionType::Default:
        ProcessDefault(tokens[1],script);
        break;
      default:
        // error
        break;
    }
  } catch (std::runtime_error& err) {
    throw std::runtime_error(err.what());
  }
}

/**
 * @brief Process the step
 * @param stepName The name of the step
 * @return void
 */
void ProcessStep(StepId stepName,Script& script) {
  if (script.stepsCount() == 0) {
    script.entry = stepName;
  }
  script.addStep(stepName);
  script.curStep = stepName;
}

/**
 * @brief Process the expression
 * @param tokens The tokens to be processed
 * @param start The start index of the tokens
 * @return Expression – The list of expressions
 */
Expression ProcessExpression(std::vector<std::string> tokens, int start) {
  Expression expression;
  for (int i = start; i < tokens.size(); i++) {
    std::string str = tokens[i];
    if (str == "+") {
      continue;
    }
    if (str.at(0) == '"') {
      if (str.at(str.size() - 1) != '"') {
        throw std::runtime_error("Invalid expression: " + str);
      }
      expression.addTerm(str.substr(1, str.size() - 2));
    }
    if (str.at(0) == '$') {
      expression.addVar(str);
    }
  }
  return expression;
}

/**
 * @brief Process the speak
 * @param tokens The tokens to be processed
 * @param start The start index of the tokens
 * @return void
 */
void ProcessSpeak(std::vector<std::string> tokens, int start,Script& script) {
  Step& step = script.getCurStep();
  std::string expression = "";
  step.setExpression(ProcessExpression(tokens, start));
}
/**
 * @brief Process the listen
 * @param beginTimer The begin timer
 * @param endTimer The end timer
 * @return void
 */
void ProcessListen(int beginTimer, int endTimer,Script& script) {
  Step& step = script.getCurStep();
  Listen listen = Listen(beginTimer, endTimer);
  step.setListen(listen);
}
/**
 * @brief Process the branch
 * @param answer The user input answer
 * @param nextStepId The  next step id to the input answer
 * @return void
 */
void ProcessBranch(Answer answer, StepId stepName,Script& script) {
  Step& step = script.getCurStep();
  step.addBranch(answer, stepName);
}
/**
 * @brief Process the silence
 * @param nextStepId The next step id to the silence
 * @return void
 */
void ProcessSilence(StepId nextStepId,Script& script) {
  Step& step = script.getCurStep();
  step.setSilence(nextStepId);
}
/**
 * @brief Process the default
 * @param nextStepId The next step id to the default
 * @return void
 */
void ProcessDefault(StepId nextStepId,Script& script) {
  Step& step = script.getCurStep();
  script._default_ = nextStepId;
  step.setDefault(nextStepId);
}
/**
 * @brief Process the exit, set this step as the exit step
 * @return void
 */
void ProcessExit(Script& script) {
  Step& step = script.getCurStep();
  step.setEndStep();
}

}  // namespace parser
