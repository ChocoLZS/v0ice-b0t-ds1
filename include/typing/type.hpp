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

#define VAR 0
#define STR 1

class Item {
 public:
  Item(uint8_t type, std::string val) {
    this->type = type;
    this->val = val;
  }
  uint8_t type;
  std::string val;
};

class Expression {
 public:
  std::vector<Item> items;
  Expression(std::vector<Item> items) { this->items = items; }
  Expression() { this->items = std::vector<Item>(); }
  ~Expression() {
    this->items.clear();
    this->items.shrink_to_fit();
  }
  void addTerm(std::string term) { this->items.push_back(Item(STR, term)); }
  void addVar(std::string var) { this->items.push_back(Item(VAR, var)); }
};

class Listen {
 public:
  int beginTimer;
  int endTimer;
  Listen(int beginTimer, int endTimer) {
    this->beginTimer = beginTimer;
    this->endTimer = endTimer;
  }
  Listen() {}
};

class Step {
 public:
  Expression speak;
  Listen listen;
  std::map<Answer, StepId> branches;
  bool isEndStep;
  StepId stepName;
  StepId silence;
  StepId _default_;
  Step() = default;
  Step(StepId name) {
    this->stepName = name;
    this->speak = Expression();
    this->listen = Listen();
    this->branches = std::map<Answer, StepId>();
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

class Script {
 public:
  Script() {
    this->steps = std::map<StepId, Step>();
    this->entry = "";
    this->vars = std::vector<VarName>();
  }
  int addStep(StepId id) {
    if (this->steps.find(id) != this->steps.end()) {
      return 1;
    }
    this->steps[id] = Step(id);
    return 0;
  }
  int stepsCount() { return this->steps.size(); }

  Step& getCurStep() {
    if (this->steps.find(this->curStep) == this->steps.end()) {
      throw std::runtime_error("Step not found");
    }
    return this->steps[curStep];
  }
  Step& getStep(StepId stepId) {
    if (this->steps.find(stepId) == this->steps.end()) {
      throw std::runtime_error("Step not found");
    }
    return this->steps[stepId];
  }
  StepId curStep;
  StepId entry;

 private:
  std::map<StepId, Step> steps;
  std::vector<VarName> vars;
};
