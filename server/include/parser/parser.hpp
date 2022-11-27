#pragma once

#include <map>
#include <string>
#include <typing/type.hpp>

namespace parser {
/**
 * @brief Parse the script file
 * @param path The path of the script file
 * @param script The script object
 * @return void
 */
void ParseFile(std::string path, Script &script);

/**
 * @brief Parse the line
 * @param line The line to be parsed,splited by whitespace
 * @return std::vector<std::string> The tokens of the line
 */
std::vector<std::string> ParseLine(std::string line);

/**
 * @brief Process the tokens
 * @param tokens The tokens to be processed
 * @param script The script object
 * @return void
 */
void ProcessTokens(std::vector<std::string> tokens, Script &script);

/**
 * @brief Process the step
 * @param stepName The name of the step
 * @param script The script object
 * @return void
 */
void ProcessStep(StepId stepName, Script &script);

/**
 * @brief Process the listen
 * @param beginTimer The begin timer
 * @param endTimer The end timer
 * @param script The script object
 * @return void
 */
void ProcessListen(int beginTimer, int endTimer, Script &script);

/**
 * @brief Process the branch
 * @param answer The user input answer
 * @param nextStepId The  next step id to the input answer
 * @param script The script object
 * @return void
 */
void ProcessBranch(Answer answer, StepId nextStepId, Script &script);

/**
 * @brief Process the silence
 * @param nextStepId The next step id to the silence
 * @param script The script object
 * @return void
 */
void ProcessSilence(StepId nextStepId, Script &script);

/**
 * @brief Process the speak
 * @param tokens The tokens to be processed
 * @param start The start index of the tokens
 * @param script The script object
 * @return void
 */
void ProcessSpeak(std::vector<std::string> tokens, int start, Script &script);

/**
 * @brief Process the exit, set this step as the exit step
 * @param script The script object
 * @return void
 */
void ProcessExit(Script &script);

/**
 * @brief Process the default
 * @param nextStepId The next step id to the default
 * @param script The script object
 * @return void
 */
void ProcessDefault(StepId nextStepId, Script &script);
}  // namespace parser