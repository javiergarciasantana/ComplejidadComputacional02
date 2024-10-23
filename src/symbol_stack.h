#include <iostream>
#include <vector>

#include "library.h"

class SymbolStack {
 public:
  // Push a symbol onto the stack
  void push(const Symbol& symbol) {
    stack_.push_back(symbol);
  }

  // Pop the top symbol from the stack
  void pop() {
    if (!stack_.empty()) {
      stack_.pop_back();
    } else {
      std::cerr << "Error: Attempt to pop from an empty stack." << std::endl;
    }
  }

  // Get the top symbol from the stack
  Symbol top() const {
    if (!stack_.empty()) {
      return stack_.back();
    } else {
      std::cerr << "Error: Attempt to access top of an empty stack." << std::endl;
      return Symbol('.'); // Return a default symbol when the stack is empty
    }
  }

  // Check if the stack is empty
  bool empty() const {
    return stack_.empty();
  }

  // Display the contents of the stack (from top to bottom)
  void displayStack() const {
    std::cout << "Stack contents (top to bottom): ";
    if (stack_.empty()) {
      std::cout << "Stack is empty." << std::endl;
      return;
    }

    // Display each element in the stack from top to bottom
    for (auto it = stack_.rbegin(); it != stack_.rend(); ++it) {
      std::cout << it->getValue() << " ";
    }
    std::cout << std::endl;
  }

  // Clear all elements from the stack
  void clear() {
    stack_.clear();
  }

 private:
  std::vector<Symbol> stack_; // Internal storage for the stack
};
