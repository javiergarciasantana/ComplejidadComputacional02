#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <iostream>
#include <stack>
#include <vector>
#include <string>
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
      : initial_state_(initial), initial_stack_symbol_(initialStackSym) {}

  void addTransition(const Transition &transition) {
    transitions_[transition.getCurrentState().getName()].push_back(transition);
  }

  bool execute(const std::string &input) {
    stack_.push(initial_stack_symbol_);
    State current_state = initial_state_;
    size_t inputIndex = 0;

    while (true) {
      char currentInput = inputIndex < input.size() ? input[inputIndex] : '.';
      bool transitionFound = false;

      const auto &transitionsForState = transitions_[current_state.getName()];
      for (const auto &trans : transitionsForState) {
        if ((trans.getInputSymbol().getValue() == currentInput || trans.getInputSymbol().getValue() == '.') &&
            (trans.getStackSymbol().getValue() == stack_.top().getValue())) {
          
          current_state = trans.getNextState();
          stack_.pop();
          for (auto it = trans.getStackOperation().rbegin(); it != trans.getStackOperation().rend(); ++it) {
            if (*it != '.') stack_.push(Symbol(*it));
          }

          if (currentInput != '.') ++inputIndex;
          transitionFound = true;
          break;
        }
      }

      if (!transitionFound) break;
    }

    return stack_.empty();
  }

 private:
  std::unordered_map<std::string, std::vector<Transition> > transitions_;
  Alphabet input_alphabet_;
  Alphabet stack_alphabet_;
  State initial_state_;
  Symbol initial_stack_symbol_;
  std::stack<Symbol> stack_;
};

#endif
