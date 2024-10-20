#include "Automaton.h"
#include <fstream>
#include <sstream>

void loadAutomaton(const std::string &filename, StackAutomaton &automaton, Alphabet &inputAlphabet, Alphabet &stackAlphabet) {
  std::ifstream file(filename);
  std::string line;
  std::vector<State> states;
  Symbol initialStackSymbol(' ');
  State initialState("");
  
  while (std::getline(file, line)) {
    if (line.empty() || line[0] == '#') continue;
    std::istringstream iss(line);

    if (line.find("initial state") != std::string::npos) {
      std::string state;
      iss >> state;
      initialState = State(state);
    } else if (line.find("initial stack") != std::string::npos) {
      char stackSymbol;
      iss >> stackSymbol;
      initialStackSymbol = Symbol(stackSymbol);
    } else if (line.find("transition") != std::string::npos) {
      std::string currentState, nextState, stackOperation;
      char inputSymbol, stackSymbol;
      iss >> currentState >> inputSymbol >> stackSymbol >> nextState >> stackOperation;
      automaton.addTransition(Transition(State(currentState), Symbol(inputSymbol), Symbol(stackSymbol), State(nextState), stackOperation));
    }
  }
}