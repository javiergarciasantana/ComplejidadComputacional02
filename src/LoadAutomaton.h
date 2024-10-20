#include <fstream>
#include <sstream>
#include <iostream>

#include "Automaton.h"

void loadAutomaton(const std::string &filename, StackAutomaton &automaton, Alphabet &inputAlphabet, Alphabet &stackAlphabet) {
  std::ifstream file(filename);
  std::string line;
  std::vector<State> states;
  Symbol initialStackSymbol(' ');
  State initialState("");

  std::cout << "Loading automaton from file: " << filename << std::endl;

  int section = 0;
  while (std::getline(file, line)) {
    // Skip empty lines and comments
    if (line.empty() || line[0] == '#') continue;
    std::istringstream iss(line);

    // Determine which section of the input we're in
    if (section == 0) { // Reading states
      std::cout << "Reading states..." << std::endl;
      std::string state;
      while (iss >> state) {
        states.push_back(State(state));
        std::cout << "State added: " << state << std::endl;
      }
      section++;
    } else if (section == 1) { // Reading input alphabet
      std::cout << "Reading input alphabet..." << std::endl;
      char symbol;
      while (iss >> symbol) {
        inputAlphabet.addSymbol(symbol);
        std::cout << "Input symbol added: " << symbol << std::endl;
      }
      section++;
    } else if (section == 2) { // Reading stack alphabet
      std::cout << "Reading stack alphabet..." << std::endl;
      char symbol;
      while (iss >> symbol) {
        stackAlphabet.addSymbol(symbol);
        std::cout << "Stack symbol added: " << symbol << std::endl;
      }
      section++;
    } else if (section == 3) { // Reading initial state
      std::string state;
      iss >> state;
      initialState = State(state);
      std::cout << "Initial state set to: " << state << std::endl;
      section++;
    } else if (section == 4) { // Reading initial stack symbol
      char stackSymbol;
      iss >> stackSymbol;
      initialStackSymbol = Symbol(stackSymbol);
      std::cout << "Initial stack symbol set to: " << stackSymbol << std::endl;
      section++;
    } else if (section == 5) { // Reading transitions
      std::cout << "Reading transitions..." << std::endl;
      std::string currentState, nextState, stackOperation;
      char inputSymbol, stackSymbol;
      while (iss >> currentState >> inputSymbol >> stackSymbol >> nextState >> stackOperation) {
        Transition transition(State(currentState), Symbol(inputSymbol), Symbol(stackSymbol), State(nextState), stackOperation);
        automaton.addTransition(transition);
        std::cout << "Transition added: (" << currentState << ", " << inputSymbol << ", " << stackSymbol << ") -> ("
                  << nextState << ", " << stackOperation << ")" << std::endl;
      }
    }
  }

  // Set initial state and stack symbol for the automaton
  automaton = StackAutomaton(initialState, initialStackSymbol);
  std::cout << "Automaton initialization completed." << std::endl;
}
