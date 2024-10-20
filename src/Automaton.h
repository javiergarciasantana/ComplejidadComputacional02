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
 private:
  char value_;
};

class Alphabet {
 public:
  void addSymbol(char symbol) { symbols_.insert(symbol); }
  bool contains(char symbol) const { return symbols_.find(symbol) != symbols_.end(); }
 private:  
  std::unordered_set<char> symbols_;
};

class State {
 public:
  State(const std::string &st_name_) : st_name_(st_name_) {}
  bool operator==(const State &other) const { return st_name_ == other.st_name_; }
 private:
  std::string st_name_;
};

class Transition {
 public:
  Transition(State curr, Symbol input, Symbol stackSym, State next, const std::string &op)
            : current_state_(curr), input_symbol_(input), stack_symbol_(stackSym), next_state_(next), stack_operation_(op) {}
private:
  State current_state_;
  Symbol input_symbol_;
  Symbol stack_symbol_;
  State next_state_;
  std::string stack_operation_;
};

class StackAutomaton {
private:
  std::unordered_map<std::string, std::vector<Transition>> transitions;
  Alphabet inputAlphabet;
  Alphabet stackAlphabet;
  State initialState;
  Symbol initialstack_symbol_;
  std::stack<Symbol> stack;

public:
  StackAutomaton(const State &initial, const Symbol &initialStackSym) 
      : initialState(initial), initialstack_symbol_(initialStackSym) {}

  void addTransition(const Transition &transition) {
    transitions[transition.current_state_.st_name_].push_back(transition);
  }

  bool execute(const std::string &input) {
    stack.push(initialstack_symbol_);
    State current_state_ = initialState;
    size_t inputIndex = 0;

    while (true) {
      char currentInput = inputIndex < input.size() ? input[inputIndex] : '.';
      bool transitionFound = false;

      for (const auto &trans : transitions[current_state_.st_name_]) {
        if ((trans.input_symbol_.value_ == currentInput || trans.input_symbol_.value_ == '.') &&
            (trans.stack_symbol_.value_ == stack.top().value_)) {
          
          current_state_ = trans.next_state_;
          stack.pop();
          for (auto it = trans.stack_operation_.rbegin(); it != trans.stack_operation_.rend(); ++it) {
            if (*it != '.') stack.push(Symbol(*it));
          }

          if (currentInput != '.') ++inputIndex;
          transitionFound = true;
          break;
        }
      }

      if (!transitionFound) break;
    }

    return stack.empty();
  }
};

#endif
