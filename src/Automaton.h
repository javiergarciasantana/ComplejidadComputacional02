#include "Library.h"

#ifndef AUTOMATON_H
#define AUTOMATON_H

class StackAutomaton {
 public:
  StackAutomaton(const State &initial, const Symbol &initialStackSym) 
      : initial_state_(initial), initial_stack_symbol_(initialStackSym) { transitions_.clear(); }

  void addTransition(const Transition &transition) {
    transitions_.push_back(transition);

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

  void displayStack() const {
    std::stack<Symbol> tempStack = stack_; // Make a copy of the stack
    std::cout << "Stack contents (top to bottom): ";
    if (tempStack.empty()) {
        std::cout << "Stack is empty." << std::endl;
        return;
    }

    // Iterate through the stack and display each element
    while (!tempStack.empty()) {
        std::cout << tempStack.top().getValue() << " "; // Display the top element
        tempStack.pop(); // Remove the top element
    }
    std::cout << std::endl;
}


  bool execute(const std::string &input) {
    stack_.push(initial_stack_symbol_);
    State current_state = initial_state_;
    return executeRecursive(input, current_state, 0);
  }

  bool executeRecursive(const std::string &input, State &current_state, size_t inputIndex) {
    char currentInput = inputIndex < input.size() ? input[inputIndex] : '.';

    if (!stack_.empty()) {
      std::cout << "\nCurrent state: " << current_state.getName() 
                << ", Current input: " << currentInput 
                << ", Stack top: " << stack_.top().getValue() << std::endl;
      displayStack();
    } else {
      std::cout << "\nCurrent state: " << current_state.getName() 
                << ", Current input: " << currentInput 
                << ", Stack is empty." << std::endl;
    }

    for (const auto &trans : transitions_) {
      if (!stack_.empty() &&
          (trans.getCurrentState().getName() == current_state.getName()) &&
          (trans.getInputSymbol().getValue() == currentInput || trans.getInputSymbol().getValue() == '.') &&
          (trans.getStackSymbol() == stack_.top().getValue())) {

        std::cout << "Applying transition to state " << trans.getNextState().getName()
                  << ", Pop stack symbol: " << stack_.top().getValue() << std::endl;

        current_state = trans.getNextState();
        stack_.pop();

        for (int i = trans.getStackOperation().size() - 1; i >= 0; --i) {
          if (trans.getStackOperation().at(i) != '.') {
            stack_.push(Symbol(trans.getStackOperation().at(i)));
            std::cout << "Pushed symbol " << trans.getStackOperation().at(i) << " onto the stack" << std::endl;
          }
        }

        if (currentInput != '.' && trans.getInputSymbol().getValue() != '.') {
          inputIndex++;
        }

        // Recursive call to continue processing
        if (executeRecursive(input, current_state, inputIndex)) {
          return true; // If the recursive call was successful
        }

        // Backtrack: pop the last pushed symbol if needed
        if (currentInput != '.' && trans.getInputSymbol().getValue() != '.') {
          inputIndex--; // Roll back input index if not epsilon
        }
        //displayStack();
        // Revert state and restore stack for the next transition
        current_state = trans.getCurrentState(); // Revert state to the original for backtrack
        //std::cout << trans.getStackSymbol().getValue() << std::endl;
        for (int i = 0; i < trans.getStackOperation().size(); ++i) {
          if (trans.getStackOperation().at(i) != '.') {
            stack_.pop(); // Remove the symbol we just added back to avoid duplicates
          }
        }
        stack_.push(Symbol(trans.getStackSymbol().getValue())); // Re-add the popped symbol for backtrack
        //displayStack();
      }
    }

    // Check for acceptance
    bool isAccepted = stack_.empty() && currentInput == '.';
    if (isAccepted) {
      std::cout << "Execution accepted: Stack is empty." << std::endl;
    } else {
      std::cout << "Execution rejected: Stack is not empty. Bactrack" << std::endl;
    }
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
