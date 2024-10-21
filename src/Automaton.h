#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

class Symbol {
 public:
  Symbol(char val) : value_(val) {}
  bool operator==(const Symbol &other) const { return value_ == other.value_; }
  char getValue() const { return value_; }
 private:
  char value_;
};

class Alphabet {
 public:
  void addSymbol(char symbol) { symbols_.insert(symbol); }
  bool contains(char symbol) const { return symbols_.find(symbol) != symbols_.end(); }
  const std::unordered_set<char>& getSymbols() const { return symbols_; }
 private:
  std::unordered_set<char> symbols_;
};

class State {
 public:
  State(const std::string &name) : name_(name) {}
  bool operator==(const State &other) const { return name_ == other.name_; }
  std::string getName() const { return name_; }
 private:
  std::string name_;
};

class Transition {
 public:
  Transition(const State &curr, const Symbol &input, const Symbol &stackSym, const State &next, const std::string &op)
      : current_state_(curr), input_symbol_(input), stack_symbol_(stackSym), next_state_(next), stack_operation_(op) {}
  
  State getCurrentState() const { return current_state_; }
  Symbol getInputSymbol() const { return input_symbol_; }
  Symbol getStackSymbol() const { return stack_symbol_; }
  State getNextState() const { return next_state_; }
  std::string getStackOperation() const { return stack_operation_; }
 private: 
  State current_state_;
  Symbol input_symbol_;
  Symbol stack_symbol_;
  State next_state_;
  std::string stack_operation_;
};

class StackAutomaton {
 public:
  StackAutomaton(const State &initial, const Symbol &initialStackSym) 
      : initial_state_(initial), initial_stack_symbol_(initialStackSym) { transitions_.clear(); }

  void addTransition(const Transition &transition) {
    transitions_.push_back(transition);
            std::cout << transitions_.size() << std::endl;

    std::cout << "Added transition from state " << transition.getCurrentState().getName()
              << " on input " << transition.getInputSymbol().getValue()
              << " and stack symbol " << transition.getStackSymbol().getValue()
              << " to state " << transition.getNextState().getName()
              << " with stack operation " << transition.getStackOperation() << std::endl;
  }

  void loadAutomaton(const std::string &filename, Alphabet &inputAlphabet, Alphabet &stackAlphabet) {
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
          addTransition(transition);
          std::cout << "Transition added: (" << currentState << ", " << inputSymbol << ", " << stackSymbol << ") -> ("
                    << nextState << ", " << stackOperation << ")" << std::endl;
        }
      }
    }

    // Set initial state and stack symbol for the automaton
    initial_state_ = initialState;
    initial_stack_symbol_ = initialStackSymbol;
    std::cout << "Automaton initialization completed." << std::endl;
  }


  bool execute(const std::string &input) {
    stack_.push(initial_stack_symbol_);
    State current_state = initial_state_;
    size_t inputIndex = 0;

    std::cout << "Starting execution with initial state: " << current_state.getName()
              << " and initial stack symbol: " << initial_stack_symbol_.getValue() << std::endl;

    while (true) {
      char currentInput = inputIndex < input.size() ? input[inputIndex] : '.';
      bool transitionFound = false;

      std::cout << "Current state: " << current_state.getName() << ", Current input: " << currentInput
                << ", Stack top: " << stack_.top().getValue() << std::endl;


      for (const auto &trans : transitions_) {
        if ((trans.getCurrentState().getName() == current_state.getName()) && (trans.getInputSymbol().getValue() == currentInput || trans.getInputSymbol().getValue() == '.') &&
            (trans.getStackSymbol().getValue() == stack_.top().getValue())) {
          
          std::cout << "Applying transition to state " << trans.getNextState().getName()
                    << ", Pop stack symbol: " << stack_.top().getValue() << std::endl;

          current_state = trans.getNextState();
          stack_.pop();

          for (auto it = trans.getStackOperation().rbegin(); it != trans.getStackOperation().rend(); ++it) {
            if (*it != '.') {
              stack_.push(Symbol(*it));
              std::cout << "Pushed symbol " << *it << " onto the stack" << std::endl;
            }
          }

          if (currentInput != '.') {
            ++inputIndex;
          }
          transitionFound = true;
          break;
        }
      }

      if (!transitionFound) {
        std::cout << "No valid transition found. Ending execution." << std::endl;
        break;
      }
    }

    bool isAccepted = stack_.empty();
    std::cout << "Execution " << (isAccepted ? "accepted" : "rejected") << ": Stack is "
              << (isAccepted ? "empty" : "not empty") << std::endl;
    return isAccepted;
  }

 private:
  std::vector<Transition> transitions_;
  Alphabet input_alphabet_;
  Alphabet stack_alphabet_;
  State initial_state_;
  Symbol initial_stack_symbol_;
  std::stack<Symbol> stack_;
};

#endif
