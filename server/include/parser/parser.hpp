#pragma once

#include <map>
#include <string>
#include <typing/type.hpp>

namespace parser {
void ParseFile(std::string path,Script& script);
std::vector<std::string> ParseLine(std::string line);
void ProcessTokens(std::vector<std::string> tokens,Script& script);
void ProcessStep(StepId stepName,Script& script);
void ProcessListen(int beginTimer, int endTimer,Script& script);
void ProcessBranch(Answer answer, StepId nextStepId,Script& script);
void ProcessSilence(StepId nextStepId,Script& script);
void ProcessSpeak(std::vector<std::string> tokens, int start,Script& script);
void ProcessExit(Script& script);
void ProcessDefault(StepId nextStepId,Script& script);
}  // namespace parser