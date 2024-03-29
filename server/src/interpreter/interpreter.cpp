#include <db/sqlite.hpp>
#include <interpreter/interpreter.hpp>
#include <iostream>
#include <typing/type.hpp>
extern Script script;

namespace interpreter {
namespace executor {
// void Execute(int id) {
//   std::optional<json> userInfo;
//   try {
//     userInfo = sqlgen::getUser(id);
//   } catch (std::runtime_error e) {
//     std::cerr << e.what() << std::endl;
//     throw e;
//   }
//   StepId curStepId;
//   Step curStep;
//   curStepId = script.entry;
//   do {
//     curStep = script.getStep(curStepId);
//     // Speak
//     std::cout << generateSpeak(curStep, userInfo) << std::endl;
//     if (curStep.isEndStep) {
//       break;
//     }
//     // Listen
//     std::string input;
//     std::cin >> input;
//     // Branch
//     curStepId = curStep.getBranch(input);
//     if (curStepId == "") {
//       curStepId = curStep._default_;
//     }
//   } while (true);
// }

std::string generateSpeak(Step step, std::optional<json> userInfo) {
  std::string speak = "";
  Expression expression = step.speak;
  for (Item item : expression.items) {
    switch (item.type) {
      case (int)StrType::STR:
        speak += item.val;
        break;
      case (int)StrType::VAR:
        speak += " ";
        if (userInfo.value().contains(std::string{item.val})) {
          if (userInfo.value()[item.val].is_string()) {
            speak += userInfo.value()[item.val];
          } else {
            speak += std::to_string((int)userInfo.value()[item.val]);
          }
        } else {
          speak += "undefined";
        }
        speak += " ";
        break;
    }
  }
  return speak;
}
}  // namespace executor
}  // namespace interpreter
