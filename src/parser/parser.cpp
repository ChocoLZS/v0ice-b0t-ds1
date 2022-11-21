/**
 * @details This function parses the given file and consturcts the global script
 * AST.
 */

#include <fstream>
#include <iostream>
#include <parser/parser.hpp>
#include <typing/type.hpp>
#include <utils/util.hpp>

extern Script script;
namespace parser {
/**
 * @brief Parse the script file
 * @param path The path of the script file
 * @return void
 */
void ParseFile(std::string path) {
  try {
    std::ifstream file(path);
    std::string line;
    while (std::getline(file, line)) {
      line = util::str::trim(line);
      if (line.empty()) {
        continue;
      }
      if (line[0] == '#') {
        continue;
      }
      ParseLine(line);
    }
    file.close();
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}

/**
 * @brief Parse the line into tokens.
 * @param line The line to be parsed
 * @return void
 */
void ParseLine(std::string line) {
  std::vector<std::string> tokens = util::str::eraceWhitespace(line);
  ProcessTokens(tokens);
}

/**
 * @brief Process the tokens
 * @param tokens The tokens to be processed
 * @return void
 */
void ProcessTokens(std::vector<std::string> tokens) {
  std::string command = util::str::getCommand(tokens[0]);
  switch (util::action_mapping[command]) {
    case ActionType::Step:
      ProcessStep(tokens[1]);
      break;
    case ActionType::Listen: {
      // todo: error checking
      std::vector<std::string> strs = util::str::split(tokens[1], ",");
      ProcessListen(std::stoi(strs[0]), std::stoi(strs[1]));
      break;
    }
    case ActionType::Branch: {
      ProcessBranch(tokens[1].substr(1, tokens[1].size() - 2), tokens[3]);
      break;
    }
    case ActionType::Silence:
      ProcessSilence(tokens[1]);
      break;
    case ActionType::Speak:
      ProcessSpeak(tokens, 1);
      break;
    case ActionType::Exit:
      ProcessExit();
      break;
    case ActionType::Default:
      ProcessDefault(tokens[1]);
      break;
    default:
      // error
      break;
  }
}

/**
 * @brief Process the step
 * @param stepName The name of the step
 * @return void
 */
void ProcessStep(StepId stepName) {
  if (script.stepsCount() == 0) {
    script.entry = stepName;
  }
  try {
    script.addStep(stepName);
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
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
void ProcessSpeak(std::vector<std::string> tokens, int start) {
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
void ProcessListen(int beginTimer, int endTimer) {
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
void ProcessBranch(Answer answer, StepId stepName) {
  Step& step = script.getCurStep();
  step.addBranch(answer, stepName);
}
/**
 * @brief Process the silence
 * @param nextStepId The next step id to the silence
 * @return void
 */
void ProcessSilence(StepId nextStepId) {
  Step& step = script.getCurStep();
  step.setSilence(nextStepId);
}
/**
 * @brief Process the default
 * @param nextStepId The next step id to the default
 * @return void
 */
void ProcessDefault(StepId nextStepId) {
  Step& step = script.getCurStep();
  step.setDefault(nextStepId);
}
/**
 * @brief Process the exit, set this step as the exit step
 * @return void
 */
void ProcessExit() {
  Step& step = script.getCurStep();
  step.setEndStep();
}

}  // namespace parser
