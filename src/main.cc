#include "LoadAutomaton.h"

int main(int argc, char* argv[]) {
  Alphabet inputAlphabet, stackAlphabet;
  StackAutomaton automaton(State("q0"), Symbol('Z'));

  loadAutomaton(std::string(argv[1]), automaton, inputAlphabet, stackAlphabet);

  std::string input;
  std::cout << "Enter the input string: ";
  std::cin >> input;

  if (automaton.execute(input)) {
    std::cout << "The input is accepted." << std::endl;
  } else {
    std::cout << "The input is rejected." << std::endl;
  }

  return 0;
}