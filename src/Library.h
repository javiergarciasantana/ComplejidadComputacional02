#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

#ifndef LIBRARY_H
#define LIBRARY_H

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

#endif