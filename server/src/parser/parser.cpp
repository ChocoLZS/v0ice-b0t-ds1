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
void ParseFile(std::string path, Script& script) {
  std::ifstream file(path);
  //打开文件
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open the script file: " + path +
                             " ,please check your script file.");
  }
  PLOG_DEBUG << "Parsing file: \"" << path << "\" ...";
  // 解析行
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
      ProcessTokens(tokens, script);
    } catch (std::runtime_error& err) {
      PLOG_ERROR << "Failed to parse the file.";
      throw std::runtime_error(err.what());
    }
  }

  // 给未定义的default以及silence的Step设置默认Step
  std::map<StepId, Step> steps = script.getSteps();
  for (std::map<StepId, Step>::iterator it = steps.begin(); it != steps.end();
       it++) {
    Step step = script.getStep(it->first);
    if (step._default_ == "") {
      step._default_ = script._default_;
    }
    if (step.silence == "") {
      step.silence = script._default_;
    }
    // 检查当前步骤所拥有的分支是否存在
    if (steps.count(step.silence) == 0) {
      throw std::runtime_error("The step \"" + step.stepName +
                               "\" has a silence branch \"" + step.silence +
                               "\" which is not defined.");
    }
    if (steps.count(step._default_) == 0) {
      throw std::runtime_error("The step \"" + step.stepName +
                               "\" has a default branch \"" + step._default_ +
                               "\" which is not defined.");
    }
    for (std::map<Answer, StepId>::iterator it = step.branches.begin();
         it != step.branches.end(); it++) {
      if (steps.count(it->second) == 0) {
        throw std::runtime_error("The step \"" + step.stepName +
                                 "\" has a branch \"" + it->second +
                                 "\" which is not defined.");
      }
    }
  }
  file.close();
}

std::vector<std::string> ParseLine(std::string line) {
  return util::str::eraseWhitespace(line);
}

void ProcessTokens(std::vector<std::string> tokens, Script& script) {
  PLOG_DEBUG << "Processing tokens ...";
  std::string command = tokens[0];
  PLOG_DEBUG << "Command: " << command;
  try {
    // 查看当前command
    switch (util::action_mapping.count(command) > 0
                ? util::action_mapping[command]
                : -1) {
      case (int)ActionType::Step:
        stepValidator(tokens);
        ProcessStep(tokens[1], script);
        break;
      case (int)ActionType::Listen: {
        std::pair<int, int> timers = listenValidator(tokens);
        ProcessListen(timers.first, timers.second, script);
        break;
      }
      case (int)ActionType::Branch: {
        branchValidator(tokens);
        ProcessBranch(tokens[1].substr(1, tokens[1].size() - 2), tokens[3],
                      script);
        break;
      }
      case (int)ActionType::Silence:
        silenceValidator(tokens);
        ProcessSilence(tokens[1], script);
        break;
      case (int)ActionType::Speak:
        ProcessSpeak(tokens, 1, script);
        break;
      case (int)ActionType::Exit:
        ProcessExit(script);
        break;
      case (int)ActionType::Default:
        defaultValidator(tokens);
        ProcessDefault(tokens[1], script);
        break;
      default:
        throw std::runtime_error("Unknown command: " + command);
        break;
    }
  } catch (std::runtime_error& err) {
    throw std::runtime_error(err.what());
  }
}

void ProcessStep(StepId stepName, Script& script) {
  if (script.stepsCount() == 0) {
    script.entry = stepName;
  }
  script.addStep(stepName);
  script.curStep = stepName;
  // 保证最后一次的Step为默认Step
  script._default_ = stepName;
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
      continue;
    }
    if (str.at(0) == '$') {
      expression.addVar(str);
      continue;
    }
    throw std::runtime_error("Invalid expression: " + str);
  }
  expression.addTerm("\n");
  return expression;
}

void ProcessSpeak(std::vector<std::string> tokens, int start, Script& script) {
  Step& step = script.getCurStep();
  std::string expression = "";
  try {
    Expression exp = ProcessExpression(tokens, start);
    step.addExpression(exp);
  } catch (std::runtime_error& err) {
    throw std::runtime_error(err.what());
  }
}

void ProcessListen(int beginTimer, int endTimer, Script& script) {
  Step& step = script.getCurStep();
  Listen listen = Listen(beginTimer, endTimer);
  step.setListen(listen);
}

void ProcessBranch(Answer answer, StepId stepName, Script& script) {
  Step& step = script.getCurStep();
  step.addBranch(answer, stepName);
}

void ProcessSilence(StepId nextStepId, Script& script) {
  Step& step = script.getCurStep();
  step.setSilence(nextStepId);
}

void ProcessDefault(StepId nextStepId, Script& script) {
  Step& step = script.getCurStep();
  step.setDefault(nextStepId);
}

void ProcessExit(Script& script) {
  Step& step = script.getCurStep();
  step.setEndStep();
}

void stepValidator(std::vector<std::string> tokens) {
  if (tokens.size() < 2) {
    throw std::runtime_error("Invalid step definition.");
  }
}

std::pair<int, int> listenValidator(std::vector<std::string> tokens) {
  if (tokens.size() < 4) {
    throw std::runtime_error("The number of timer is not correct.");
  }
  int startTimer, endTimer;
  try {
    startTimer = std::stoi(tokens[1]);
    endTimer = std::stoi(tokens[3]);
  } catch (std::invalid_argument& err) {
    throw std::runtime_error("The timer is not a number.");
  }
  if (startTimer > endTimer) {
    throw std::runtime_error("The start timer is larger than the end timer.");
  } else if (startTimer < 0 || endTimer < 0) {
    throw std::runtime_error("The timer is less than 0.");
  }
  return std::make_pair(startTimer, endTimer);
}

void branchValidator(std::vector<std::string> tokens) {
  if (tokens.size() < 4) {
    throw std::runtime_error("The number of tokens is not correct.");
  }
}

void silenceValidator(std::vector<std::string> tokens) {
  if (tokens.size() < 2) {
    throw std::runtime_error("The number of tokens is not correct.");
  }
}
void defaultValidator(std::vector<std::string> tokens) {
  if (tokens.size() < 2) {
    throw std::runtime_error("The number of tokens is not correct.");
  }
}

}  // namespace parser
