#pragma once

#include <map>
#include <nlohmann/json.hpp>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

using json = nlohmann::json;

#define StepId std::string
#define Answer std::string
#define VarName std::string

enum class StrType { VAR, STR };

enum class ActionType { Step, Listen, Branch, Silence, Speak, Exit, Default };

/**
 * @brief The speak item with type string | var
 */
class Item {
 public:
  Item(uint8_t type, std::string val) {
    this->type = type;
    this->val = val;
  }
  uint8_t type;
  std::string val;
};

/**
 * @brief The speak expression with a list of items
 */
class Expression {
 public:
  std::vector<Item> items;
  Expression(std::vector<Item> items) { this->items = items; }
  Expression() {}
  ~Expression() {
    this->items.clear();
    this->items.shrink_to_fit();
  }
  void addTerm(std::string term) {
    this->items.push_back(Item((int)StrType::STR, term));
  }
  void addVar(std::string var) {
    this->items.push_back(Item((int)StrType::VAR, var));
  }
};

/**
 * @brief The listener for the user input
 */
class Listen {
 public:
  int beginTimer = -1;
  int endTimer = -1;
  Listen(int beginTimer, int endTimer) {
    this->beginTimer = beginTimer;
    this->endTimer = endTimer;
  }
  Listen() {}
};

/**
 * @brief The step contains the speak, listen, branches, silence branch and
 * default branch
 */
class Step {
 public:
  Expression speak;
  Listen listen;
  std::map<Answer, StepId> branches;
  bool isEndStep;
  StepId stepName;
  StepId silence;
  StepId _default_;
  Step(){};
  Step(StepId name) {
    this->stepName = name;
    this->silence = "";
    this->_default_ = "";
    this->isEndStep = false;
  }
  void setExpression(Expression expression) { this->speak = expression; }
  void setListen(Listen listen) { this->listen = listen; }
  void addBranch(Answer answer, StepId nextStepId) {
    this->branches[answer] = nextStepId;
  }
  StepId getBranch(Answer answer) {
    if (this->branches.find(answer) != this->branches.end()) {
      return this->branches[answer];
    }
    return "";
  }
  void setSilence(StepId silence) { this->silence = silence; }
  void setDefault(StepId _default_) { this->_default_ = _default_; }
  void setEndStep() { this->isEndStep = true; }
};

/**
 * @brief The script AST contains the steps
 */
class Script {
 public:
  StepId curStep;
  StepId entry;
  StepId _default_;
  Script() { this->entry = ""; }
  // cover
  void addStep(StepId id) { this->steps[id] = Step(id); }
  int stepsCount() { return this->steps.size(); }

  Step& getCurStep() {
    if (this->steps.find(this->curStep) == this->steps.end()) {
      return this->steps[_default_];
    }
    return this->steps[curStep];
  }
  Step& getStep(StepId stepId) {
    if (this->steps.find(stepId) == this->steps.end()) {
      return this->steps[_default_];
    }
    return this->steps[stepId];
  }
  std::map<StepId,Step>& getSteps() { return this->steps; }
 private:
  std::map<StepId, Step> steps;
  std::vector<VarName> vars;
};
