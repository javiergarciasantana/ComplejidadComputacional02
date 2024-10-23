// Library.h
// Author: Javier Garcia Santana
// Date: 17/10/2024
// Email: alu0101391663@ull.edu.es
// Version: 3.0
// Subject: Complejidad Computacional
// Practice No: 2
//
// Compilation: make || g++ -o automata main.cc

#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

// Class representing a symbol in the alphabet
class Symbol {
 public:
  // Constructor to initialize the symbol with a character value
  Symbol(char val) : value_(val) {}

  // Equality operator to compare two symbols
  bool operator==(const Symbol &other) const { return value_ == other.value_; }

  // Getter for the symbol's value
  char getValue() const { return value_; }

 private:
  char value_;  // Character value of the symbol
};

// Class representing an alphabet consisting of multiple symbols
class Alphabet {
 public:
  // Method to add a symbol to the alphabet
  void addSymbol(char symbol) { symbols_.insert(symbol); }

  // Method to check if a symbol is part of the alphabet
  bool contains(char symbol) const { return symbols_.find(symbol) != symbols_.end(); }

  // Getter for the set of symbols in the alphabet
  const std::unordered_set<char>& getSymbols() const { return symbols_; }

 private:
  std::unordered_set<char> symbols_;  // Set of symbols in the alphabet
};

// Class representing a state in the automaton
class State {
 public:
  // Constructor to initialize the state with a name
  State(const std::string &name) : name_(name) {}

  // Equality operator to compare two states
  bool operator==(const State &other) const { return name_ == other.name_; }

  // Getter for the state's name
  std::string getName() const { return name_; }

 private:
  std::string name_;  // Name of the state
};

// Class representing a transition in the automaton
class Transition {
 public:
  // Constructor to initialize the transition with current state, input symbol, stack symbol, next state, and stack operation
  Transition(const State &curr, const Symbol &input, const Symbol &stackSym, const State &next, const std::string &op)
      : current_state_(curr), input_symbol_(input), stack_symbol_(stackSym), next_state_(next), stack_operation_(op) {}

  // Getter for the current state of the transition
  State getCurrentState() const { return current_state_; }

  // Getter for the input symbol of the transition
  Symbol getInputSymbol() const { return input_symbol_; }

  // Getter for the stack symbol of the transition
  Symbol getStackSymbol() const { return stack_symbol_; }

  // Getter for the next state of the transition
  State getNextState() const { return next_state_; }

  // Getter for the stack operation of the transition
  std::string getStackOperation() const { return stack_operation_; }

 private:
  State current_state_;  // Current state of the transition
  Symbol input_symbol_;  // Input symbol of the transition
  Symbol stack_symbol_;  // Stack symbol of the transition
  State next_state_;  // Next state of the transition
  std::string stack_operation_;  // Stack operation of the transition
};

#endif  // LIBRARY_H