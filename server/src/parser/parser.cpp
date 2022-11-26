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
  return util::str::eraseWhitespace(line);
}

void ProcessTokens(std::vector<std::string> tokens,Script& script) {
  std::string command = tokens[0];
  try {
    switch (util::action_mapping[command]) {
      case ActionType::Step:
        ProcessStep(tokens[1],script);
        break;
      case ActionType::Listen: {
        // todo: error checking
        std::vector<std::string> strs = util::str::split(tokens[1], ",");
        if(strs.size() != 2){
          throw std::runtime_error("The number of timer is not correct.");
        }
        try {
          ProcessListen(std::stoi(strs[0]), std::stoi(strs[1]),script);
        }catch(std::invalid_argument& err){
          throw std::runtime_error("The timer is not a number.");
        }
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
        throw std::runtime_error("Unknown command: " + command);
        break;
    }
  } catch (std::runtime_error& err) {
    throw std::runtime_error(err.what());
  }
}

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


void ProcessSpeak(std::vector<std::string> tokens, int start,Script& script) {
  Step& step = script.getCurStep();
  std::string expression = "";
  try {
    Expression exp = ProcessExpression(tokens, start);
    step.setExpression(exp);
  }catch(std::runtime_error& err){
    throw std::runtime_error(err.what());
  }
}

void ProcessListen(int beginTimer, int endTimer,Script& script) {
  Step& step = script.getCurStep();
  Listen listen = Listen(beginTimer, endTimer);
  step.setListen(listen);
}

void ProcessBranch(Answer answer, StepId stepName,Script& script) {
  Step& step = script.getCurStep();
  step.addBranch(answer, stepName);
}

void ProcessSilence(StepId nextStepId,Script& script) {
  Step& step = script.getCurStep();
  step.setSilence(nextStepId);
}

void ProcessDefault(StepId nextStepId,Script& script) {
  Step& step = script.getCurStep();
  script._default_ = nextStepId;
  step.setDefault(nextStepId);
}

void ProcessExit(Script& script) {
  Step& step = script.getCurStep();
  step.setEndStep();
}

}  // namespace parser
