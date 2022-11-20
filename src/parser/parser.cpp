#include <fstream>
#include <iostream>
#include <parser/parser.hpp>
#include <typing/type.hpp>
#include <utils/util.hpp>

extern Script script;
namespace parser {
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
void ParseLine(std::string line) {
  std::vector<std::string> tokens = util::str::eraceWhitespace(line);
  ProcessTokens(tokens);
}

void ProcessTokens(std::vector<std::string> tokens) {
  std::string command = util::str::getCommand(tokens[0]);
  switch (util::action_mapping[command]) {
    case util::ActionType::Step:
      ProcessStep(tokens[1]);
      break;
    case util::ActionType::Listen: {
      // todo: error checking
      std::vector<std::string> strs = util::str::split(tokens[1], ",");
      ProcessListen(std::stoi(strs[0]), std::stoi(strs[1]));
      break;
    }
    case util::ActionType::Branch: {
      ProcessBranch(tokens[1].substr(1, tokens[1].size() - 2), tokens[3]);
      break;
    }
    case util::ActionType::Silence:
      ProcessSilence(tokens[1]);
      break;
    case util::ActionType::Speak:
      ProcessSpeak(tokens, 1);
      break;
    case util::ActionType::Exit:
      ProcessExit();
      break;
    case util::ActionType::Default:
      ProcessDefault(tokens[1]);
      break;
    default:
      // error
      break;
  }
}

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
Expression ProcessExpression(std::vector<std::string> tokens, int start) {
  Expression expression = Expression();
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
void ProcessSpeak(std::vector<std::string> tokens, int start) {
  Step& step = script.getCurStep();
  std::string expression = "";
  step.setExpression(ProcessExpression(tokens, start));
}
void ProcessListen(int beginTimer, int endTimer) {
  Step& step = script.getCurStep();
  Listen listen = Listen(beginTimer, endTimer);

  step.setListen(listen);
}
void ProcessBranch(Answer answer, StepId stepName) {
  Step& step = script.getCurStep();
  step.addBranch(answer, stepName);
}
void ProcessSilence(StepId nextStepId) {
  Step& step = script.getCurStep();
  step.setSilence(nextStepId);
}
void ProcessDefault(StepId nextStepId) {
  Step& step = script.getCurStep();
  step.setDefault(nextStepId);
}
void ProcessExit() {
  Step& step = script.getCurStep();
  step.setEndStep();
}

}  // namespace parser
