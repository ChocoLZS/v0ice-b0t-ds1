#pragma once

#include <map>
#include <string>
#include <typing/type.hpp>

namespace parser {
void ParseFile(std::string path);
void ParseLine(std::string line);
void ProcessTokens(std::vector<std::string> tokens);
void ProcessStep(StepId stepName);
void ProcessListen(int beginTimer, int endTimer);
void ProcessBranch(Answer answer, StepId nextStepId);
void ProcessSilence(StepId nextStepId);
void ProcessSpeak(std::vector<std::string> tokens, int start);
void ProcessExit();
void ProcessDefault(StepId nextStepId);
}  // namespace parser